/**
	http://code.google.com/p/gunzemulator/wiki/RawPacketStructure

	Before reading through this file, you have required reading! You MUST
	read that document, or you can't complain about this file. There's no
	need for more levels of abstraction at this point. Just RTFM.
*/

#include "Client.h"
#include "packet/crypto.h"

#include <cassert>

#include <boost/asio/read.hpp>
#include <boost/scoped_array.hpp>
#include <boost/make_shared.hpp>

#include <util/memory.h>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace cockpit {

struct Client::PacketHeader
{
	uint16_t version;
	uint16_t fullSize;
	uint16_t checksum;
};

struct Client::Payload
{
	uint16_t dataSize;
	uint16_t commandID;
	uint8_t packetID;

	// We don't care about the parameters.
};

Client::Client(Logger* _logger, ClientHandlerFactory* factory, io_service* io)
	: logger(_logger), handler(factory->create_client_handler()), socket(*io)
{
	assert(_logger);
	assert(factory);
	assert(handler);
	assert(io);

	currentPacketID = 0;
}

string Client::get_ip() const
{
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

		recieve_packet_header();
	} catch(const std::exception& ex) {
		logger->info(format("[%1%] Connection terminated (%2%).") % get_ip() % ex.what());
	} catch(...) {
		logger->error("Fatal error initializing the ClientHandler.");
	}
}

void Client::recieve_packet_header()
{
	shared_ptr<PacketHeader> p = make_shared<PacketHeader>();

	async_read(socket,
		// Instead of doing sizeof(RawPacket), we just get the packet header so
		// we can drop the payload into an appropriately sized buffer.
		buffer(p.get(), sizeof(PacketHeader)),
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

	assert(bytesTransferred == sizeof(PacketHeader));

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
	uint16_t payloadSize = fullSize - sizeof(PacketHeader);
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

static Client::Payload extract_payload(shared_array<uint8_t> p, bool encrypted, const uint8_t* cryptoKey)
{
	uint8_t* ptr = p.get();
	Client::Payload payload;

	if(encrypted)
		packet::decrypt(ptr, sizeof(payload), 6, cryptoKey);

	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.dataSize, ptr, sizeof(payload.dataSize)));
	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.commandID, ptr, sizeof(payload.commandID)));
	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.packetID, ptr, sizeof(payload.packetID)));

	return payload;
}

static void decrypt_params(uint8_t* params, uint16_t paramLength, const uint8_t* cryptoKey)
{
	packet::decrypt(params, paramLength, 11, cryptoKey);
}

void Client::on_payload(shared_array<uint8_t> p, uint16_t payloadSize, bool encrypted, system::error_code err, size_t bytesTransferred)
{
	if(err)
	{
		logger->debug(format("[%1%] Failure in recv(Payload).") % get_ip());
		disconnect();
		return;
	}

	if(payloadSize < sizeof(Payload))
	{
		logger->info(
			format("[%1%] Invalid payload size of %2% bytes detected.") % get_ip() % payloadSize
		);

		disconnect();
		return;
	}

	// If this gets triggered, boost is fucking up and we need to read the docs some more.
	assert(bytesTransferred == payloadSize);

	Payload payload = extract_payload(p, encrypted, cryptoKey.c_array());
	uint16_t paramLength = payloadSize - sizeof(Payload);	// LOL.
	uint8_t* params = p.get() + sizeof(Payload);

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

namespace {

struct SendablePacket
{
	uint16_t version;
	uint16_t fullSize;
	uint16_t checksum;

	uint16_t dataSize;
	uint16_t commandID;
	uint8_t  packetID;
};

}

void Client::send(const packet::Packet* p)
{
	Buffer params = p->serialize();
	size_t packetLength = sizeof(SendablePacket) + params.length();

	shared_array<uint8_t> raw(new uint8_t[packetLength]);

	SendablePacket* packetHeader = reinterpret_cast<SendablePacket*>(raw.get());

	packetHeader->version = 0x65;
	assert(packetLength <= 0xFFFF);
	packetHeader->fullSize = static_cast<uint16_t>(packetLength);
	packetHeader->checksum = 0;

	assert(params.length() + sizeof(Client::Payload) <= 0xFFFF);
	packetHeader->dataSize = static_cast<uint16_t>(params.length() + sizeof(Client::Payload));
	packetHeader->commandID = p->id();
	memory::copy(raw.get() + sizeof(packetHeader), params.data(), params.length());

	mutex::scoped_lock lock(packetSendingLock);
	packetHeader->packetID = currentPacketID++;

	packet::encrypt(raw.get() + 2, 2, 2, cryptoKey.c_array());
	packet::encrypt(raw.get() + 6, packetLength - sizeof(Client::PacketHeader), 6, cryptoKey.c_array());

	packetHeader->checksum = packet::checksum(raw.get(), packetLength);

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
	logger->debug(format("Disconnecting %1%.") % get_ip());

	socket.shutdown(socket_base::shutdown_both);
	socket.close();
}

Client::~Client()
{
	delete handler;
}

}
