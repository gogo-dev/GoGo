/**
	http://code.google.com/p/gunzemulator/wiki/RawPacketStructure

	Before reading through this file, you have required reading! You MUST
	read that document, or you can't complain about this file. There's no
	need for more levels of abstraction at this point. Just RTFM.
*/

#include "Client.h"

#include <cockpit/packet/Packet.h>
#include <cockpit/Logger.h>

#include "packet/crypto.h"

#include <cassert>
#include <cstddef>

#include <boost/asio/read.hpp>
#include <boost/scoped_array.hpp>
#include <boost/make_shared.hpp>
#include <boost/static_assert.hpp>
#include <boost/bind.hpp>

#include <util/memory.h>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

/*
	So what's up with the X::SIZE enum, anyhow? Simple. If we take sizeof(X),
	it takes padding into account. We don't want to be sending padding over
	the wire, so we never copy it. To get the real size, we define it manually
	with X::SIZE. Oh yeah, and if you change the actual size of X, please
	update it's SIZE enum. Thanks.
*/

namespace cockpit {

struct Client::PacketHeader
{
	uint16_t version;
	uint16_t fullSize;
	uint16_t checksum;

	enum
	{
		SIZE = 6
	};
};

struct Client::PayloadHeader
{
	uint16_t dataSize;
	uint16_t commandID;
	uint8_t packetID;

	// We don't care about the parameters.

	enum
	{
		SIZE = 5
	};
};

namespace {

struct SendablePacket
{
	Client::PacketHeader  packetHeader;
	Client::PayloadHeader payloadHeader;

	enum
	{
		SIZE = Client::PacketHeader::SIZE + Client::PayloadHeader::SIZE
	};
};

}

Client::Client(Logger* _logger, ClientHandlerFactory* factory, io_service* io)
	: logger(_logger), handler(factory->create_client_handler()), socket(*io)
{
	assert(_logger);
	assert(factory);
	assert(handler.get());
	assert(io);

	sending_currentPacketID = 0;
	recieving_currentPacketID = 3;	// I don't know why, it just is. Ask MAIET :(

	connected = false;
}

string Client::get_ip() const
{
	if(!connected)
		return "Not connected";

	try {
		return socket.local_endpoint().address().to_string();
	} catch(system::error_code) {
		return "Unknown IP";
	}
}

void Client::start()
{
	try {
		handler->initialize(this, &registry);
		cryptoKey = handler->handshake(socket);

	} catch(const std::exception& ex) {
		logger->info(format("[%1%] Connection terminated (%2%).") % get_ip() % ex.what());
	} catch(...) {
		logger->error("Fatal error initializing the ClientHandler. Dropping client.");
	}

	connected = true;

	recieve_packet_header();
}

void Client::recieve_packet_header()
{
	packetPool.purge();

	PacketHeader* p = packetPool.allocate<PacketHeader>();

	async_read(socket,
		// Instead of doing sizeof(RawPacket), we just get the packet header so
		// we can drop the payload into an appropriately sized buffer.
		buffer(p, PacketHeader::SIZE),
		bind(
			&Client::on_packet_header,
			shared_from_this(),
			p,
			_1,
			_2
		)
	);
}

// http://code.google.com/p/gunzemulator/wiki/RawPacketStructure
static void decrypt_header(Client::PacketHeader* p, const uint8_t* cryptoKey)
{
	packet::decrypt(reinterpret_cast<uint8_t*>(&(p->fullSize)), sizeof(p->fullSize), 0, cryptoKey);
}

void Client::on_packet_header(
	PacketHeader* p,
	system::error_code err,
	size_t bytesTransferred)
{
	assert(p);
	PacketAllocator::auto_free f(packetPool, reinterpret_cast<uint8_t*>(p));

	if(err)
	{
		logger->info(format("[%1%] Failure in recv(Header).") % get_ip());
		disconnect();
		return;
	}

	assert(bytesTransferred == PacketHeader::SIZE);

	if(p->version == 0x65)
	{
		decrypt_header(p, cryptoKey.c_array());
	}

	else if(p->version != 0x64)
		logger->info(format("[%1%] Unknown protocol version %2% recieved.") % get_ip() % p->version);

	recieve_payload(p->fullSize, p->version == 0x65);
}

void Client::recieve_payload(uint16_t fullSize, bool encrypted)
{
	uint16_t payloadSize = fullSize - PacketHeader::SIZE;

	packetPool.purge();
	uint8_t* payload = packetPool.allocate(payloadSize);

	async_read(socket,
		buffer(payload, payloadSize),
		bind(
			&Client::on_payload,
			shared_from_this(),
			payload,
			payloadSize,
			encrypted,
			_1,
			_2
		)
	);
}

static Client::PayloadHeader extract_payload(uint8_t* p, bool encrypted, const uint8_t* cryptoKey);
static void decrypt_params(uint8_t* params, uint16_t paramLength, const uint8_t* cryptoKey);

void Client::on_payload(uint8_t* p, uint16_t payloadSize, bool encrypted, system::error_code err, size_t bytesTransferred)
{
	PacketAllocator::auto_free f(packetPool, p);

	if(err)
	{
		logger->debug(format("[%1%] Failure in recv(Payload).") % get_ip());
		disconnect();
		return;
	}

	if(payloadSize < PayloadHeader::SIZE)
	{
		logger->info(
			format("[%1%] Invalid payload size of %2% bytes detected.") % get_ip() % payloadSize
		);

		disconnect();
		return;
	}

	// If this gets triggered, boost is fucking up and we need to read the docs some more.
	assert(bytesTransferred == payloadSize);

	PayloadHeader payload = extract_payload(p, encrypted, cryptoKey.c_array());
	uint16_t paramLength = payloadSize - Client::PayloadHeader::SIZE;	// LOL.
	uint8_t* params = p + Client::PayloadHeader::SIZE;

	if(payload.packetID != recieving_currentPacketID++)
	{
		logger->info(
			format("[%1%] Invalid packetID (%2% instead of %3%) recieved. Disconnecting.")
				% get_ip() % static_cast<int>(payload.packetID) % static_cast<int>(recieving_currentPacketID - 1)
		);
	}

	if(encrypted)
		decrypt_params(params, paramLength, cryptoKey.c_array());

	registry.dispatch(payload.commandID, params, paramLength);

	// This begins the recieving loop again!
	recieve_packet_header();
}

static Client::PayloadHeader extract_payload(uint8_t* packit, bool encrypted, const uint8_t* cryptoKey)
{
	uint16_t counter = 0;
	Client::PayloadHeader payload;

	if(encrypted)
		packet::decrypt(packit, Client::PayloadHeader::SIZE, 0, cryptoKey);

	memory::copy(&payload.dataSize, packit+counter, sizeof(payload.dataSize));
	counter += sizeof(payload.dataSize);

	memory::copy(&payload.commandID, packit+counter, sizeof(payload.commandID));
	counter += sizeof(payload.commandID);

	memory::copy(&payload.packetID, packit+counter, sizeof(payload.packetID));
	counter += sizeof(payload.packetID);

	return payload;
}

static void decrypt_params(uint8_t* params, uint16_t paramLength, const uint8_t* cryptoKey)
{
	packet::decrypt(params, paramLength, Client::PayloadHeader::SIZE, cryptoKey);
}

void Client::send(const packet::Packet& p, bool encrypted)
{
	Buffer params = p.serialize();
	size_t packetLength = SendablePacket::SIZE + params.length();

	// This cannot use the allocator, since send must be re-entrant and I would
	// like to keep the allocator as fast as humanly possible. Therefore, we
	// pay the price of this lone allocation to avoid the greater cost of
	// wrapping the allocator in a mutex.
	uint8_t* raw = new uint8_t[packetLength];

	SendablePacket* header = reinterpret_cast<SendablePacket*>(raw);

	header->packetHeader.version = encrypted ? 0x65 : 0x64;
	assert(packetLength <= 0xFFFF);
	header->packetHeader.fullSize = static_cast<uint16_t>(packetLength);
	header->packetHeader.checksum = 0;

	assert((params.length() + PayloadHeader::SIZE) <= 0xFFFF);
	header->payloadHeader.dataSize = static_cast<uint16_t>(params.length() + PayloadHeader::SIZE);
	header->payloadHeader.commandID = p.id();
	memory::copy(raw + SendablePacket::SIZE, params.data(), params.length());

	mutex::scoped_lock l(sendingLock);
	header->payloadHeader.packetID = sending_currentPacketID++;

	if(encrypted)
	{
		packet::encrypt(raw + 2, 2, 0, cryptoKey.c_array());	// fullSize
		packet::encrypt(raw + 6, packetLength - PacketHeader::SIZE, 0, cryptoKey.c_array());	//CommandId + PacketId + Parameters.
	}

	header->packetHeader.checksum = packet::checksum(raw, packetLength);

	socket.async_send(
		buffer(raw, packetLength),
		bind(
			&Client::on_send,
			shared_from_this(),
			_1,
			_2,
			raw,
			packetLength
		)
	);
}

void Client::on_send(system::error_code err, size_t bytesTransferred, uint8_t* p, size_t packetLength)
{
	delete[] p;

	if(err)
	{
		logger->info(format("Sending to %1% failed (%2%).") % get_ip() % err.message());
		disconnect();
		return;
	}

	assert(bytesTransferred == packetLength);
}

void Client::disconnect()
{
	if(!connected)
		return;

	logger->debug(format("[%1%] Disconnecting.") % get_ip());

	try {
		socket.shutdown(socket_base::shutdown_both);
		socket.close();
	} catch(system::system_error& e) {
		// This might be totally okay. Depends on the error.
		logger->warning(format("Failed to shut down the socket. This shouldn't happen! (%1%)") % e.what());
	}

	connected = false;
}

Client::~Client()
{
	disconnect();
}

}
