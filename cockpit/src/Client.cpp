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
}

string Client::get_ip() const
{
	try {
		return socket.local_endpoint().address().to_string();
	} catch(system::error_code ec) {
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
static void decrypt_header(Client::PacketHeader* p)
{
	// TODO: Decrypt the "fullSize" member.
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
		decrypt_header(p.get());
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

static Client::Payload extract_payload(shared_array<uint8_t> p, bool encrypted)
{
	uint8_t* ptr = p.get();
	Client::Payload payload;

	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.dataSize, ptr, sizeof(payload.dataSize)));
	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.commandID, ptr, sizeof(payload.commandID)));
	ptr = reinterpret_cast<uint8_t*>(memory::pcopy(&payload.packetID, ptr, sizeof(payload.packetID)));

	if(encrypted)
	{
		// TODO: Decrypt the payload.
	}

	return payload;
}

static void decrypt_params(uint8_t* params, uint16_t paramLength)
{
	// TODO: Decrypt the packet's parameters.
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

	Payload payload = extract_payload(p, encrypted);
	uint16_t paramLength = payloadSize - sizeof(Payload);	// LOL.
	uint8_t* params = p.get() + sizeof(Payload);

	if(encrypted)
		decrypt_params(params, paramLength);

	registry.dispatch(payload.commandID, params, paramLength);

	// This begins the recieving loop again!
	recieve_packet_header();
}

void Client::on_send(system::error_code err, size_t bytesTransferred, shared_ptr<Buffer> buf)
{
	if(err)
	{
		logger->info(format("Sending to %1% failed (%2%).") % get_ip() % err.message());
		disconnect();
		return;
	}

	assert(bytesTransferred == buf->length());
}

void Client::send(const packet::Packet* packet)
{
	send(packet->serialize());
}

void Client::send(const Buffer& _buf)
{
	shared_ptr<Buffer> buf = make_shared<Buffer>(_buf);

	socket.async_send(
		buffer(buf->data(), buf->length()),
		bind(
			&Client::on_send,
			shared_from_this(),
			_1,
			_2,
			buf
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
