/**
	http://code.google.com/p/gunzemulator/wiki/RawPacketStructure

	Before reading through this file, you have required reading! You MUST
	read that document, or you can't complain about this file. There's no
	need for more levels of abstraction at this point. Just RTFM.
*/

#include "Client.h"
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
	assert(handler);
	assert(io);

	currentPacketID = 0;

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
	shared_ptr<PacketHeader> p = make_shared<PacketHeader>();

	async_read(socket,
		// Instead of doing sizeof(RawPacket), we just get the packet header so
		// we can drop the payload into an appropriately sized buffer.
		buffer(p.get(), PacketHeader::SIZE),
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
	packet::decrypt(reinterpret_cast<uint8_t*>(&(p->fullSize)), sizeof(p->fullSize), 2, cryptoKey);
}

void Client::on_packet_header(
	shared_ptr<PacketHeader> p,
	system::error_code err,
	size_t bytesTransferred)
{
	if(err)
	{
		logger->info(format("[%1%] Failure in recv(Header).") % get_ip());
		disconnect();
		return;
	}

	assert(bytesTransferred == PacketHeader::SIZE);

	if(p->version == 0x65)
	{
		logger->debug(format("[%1%] Packet encrypted. Decrypting...") % get_ip());
		decrypt_header(p.get(), cryptoKey.c_array());
	}

	else if(p->version != 0x64)
		logger->info(format("[%1%] Unknown protocol version %2% recieved.") % get_ip() % p->version);

	recieve_payload(p->fullSize, p->version == 0x65);
}

void Client::recieve_payload(uint16_t fullSize, bool encrypted)
{
	uint16_t payloadSize = fullSize - PacketHeader::SIZE;
	shared_array<uint8_t> payload(new uint8_t[payloadSize]);

	async_read(socket,
		buffer(payload.get(), payloadSize),
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

static Client::PayloadHeader extract_payload(shared_array<uint8_t> p, bool encrypted, const uint8_t* cryptoKey)
{
	uint8_t* ptr = p.get();
	Client::PayloadHeader payload;

	if(encrypted)
		packet::decrypt(ptr, Client::PayloadHeader::SIZE, 6, cryptoKey);

	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.dataSize, ptr, sizeof(payload.dataSize)));
	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.commandID, ptr, sizeof(payload.commandID)));
	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.packetID, ptr, sizeof(payload.packetID)));

	return payload;
}

static void decrypt_params(uint8_t* params, uint16_t paramLength, const uint8_t* cryptoKey)
{
	packet::decrypt(params, paramLength, SendablePacket::SIZE, cryptoKey);
}

void Client::on_payload(shared_array<uint8_t> p, uint16_t payloadSize, bool encrypted, system::error_code err, size_t bytesTransferred)
{
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
	uint16_t paramLength = payloadSize - PayloadHeader::SIZE;
	uint8_t* params = p.get() + PayloadHeader::SIZE;

	if(encrypted)
		decrypt_params(params, paramLength, cryptoKey.c_array());

	registry.dispatch(payload.commandID, params, paramLength);

	// This begins the recieving loop again!
	recieve_packet_header();
}

void Client::on_send(system::error_code err, size_t bytesTransferred, shared_array<uint8_t>, size_t packetLength)
{
	if(err)
	{
		logger->info(format("Sending to %1% failed (%2%).") % get_ip() % err.message());
		disconnect();
		return;
	}

	assert(bytesTransferred == packetLength);
}



void Client::send(const packet::Packet* p)
{
	Buffer params = p->serialize();
	size_t packetLength = SendablePacket::SIZE + params.length();

	shared_array<uint8_t> raw(new uint8_t[packetLength]);

	SendablePacket* header = reinterpret_cast<SendablePacket*>(raw.get());

	header->packetHeader.version = 0x65;
	assert(packetLength <= 0xFFFF);
	header->packetHeader.fullSize = static_cast<uint16_t>(packetLength);
	header->packetHeader.checksum = 0;

	assert((params.length() + PayloadHeader::SIZE) <= 0xFFFF);
	header->payloadHeader.dataSize = static_cast<uint16_t>(params.length() + PayloadHeader::SIZE);
	header->payloadHeader.commandID = p->id();
	memory::copy(raw.get() + SendablePacket::SIZE, params.data(), params.length());

	packet::encrypt(raw.get() + 2, 2, 2, cryptoKey.c_array());	// fullSize
	packet::encrypt(raw.get() + 6, 4, 6, cryptoKey.c_array());	// Data header sans packetID.
	packet::encrypt(raw.get() + 11, packetLength - PacketHeader::SIZE, SendablePacket::SIZE, cryptoKey.c_array());	// Parameters.

	header->payloadHeader.packetID = currentPacketID++;
	packet::encrypt(raw.get() + 10, 1, 10, cryptoKey.c_array());	// packetID.

	header->packetHeader.checksum = packet::checksum(raw.get(), packetLength);

	socket.async_send(
		buffer(raw.get(), packetLength),
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

void Client::disconnect()
{
	if(!connected)
		return;

	logger->debug(format("Disconnecting %1%.") % get_ip());

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

	delete handler;
}

}
