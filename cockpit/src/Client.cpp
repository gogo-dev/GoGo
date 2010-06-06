/**
	http://code.google.com/p/gunzemulator/wiki/RawPacketStructure

	Before reading through this file, you have required reading! You MUST
	read that document, or you can't complain about this file. There's no
	need for more levels of abstraction at this point. Just RTFM.
*/

#include "Client.h"
#include "packet/crypto.h"

#include <boost/asio/read.hpp>
#include <boost/make_shared.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace cockpit {

struct Client::RawPacket
{
	uint16_t version;
	uint16_t fullSize;
	uint16_t checksum;

	uint16_t dataSize;
	uint16_t commandID;
	uint8_t  packetID;

	// We don't care about the parameters.
};

Client::Client(Logger* _logger, ClientHandlerFactory* factory, io_service* io)
	: logger(_logger), handler(factory->create_client_handler()), socket(*io)
{
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

		recieve_new_packet();
	} catch(const std::exception& ex) {
		logger->info(format("[%1%] Connection terminated (%2%).") % get_ip() % ex.what());
	}
}

void Client::recieve_new_packet()
{
	shared_ptr<RawPacket> p = make_shared<RawPacket>();

	async_read(socket,
		// Instead of doing sizeof(RawPacket), we just get the packet header so
		// we can drop the payload into an appropriately sized buffer.
		buffer(p.get(), sizeof(uint16_t) * 3),
		bind(
			&Client::on_packet_header,
			shared_from_this(),
			p,
			_1,
			_2
		)
	);
}

void Client::on_packet_header(
	shared_ptr<RawPacket> p,	// NOTE: This only fills in the packet header.
	system::error_code err,
	size_t bytesTransferred)
{
	if(err || (bytesTransferred != (sizeof(uint16_t) * 3)))
	{
		logger->info(format("[%1] Failure in recv(). Terminating the connection.") % get_ip());
		return;
	}

	uint16_t packetSize;

	if(p->version == 0x64)
		packetSize = p->fullSize;
	else if(p->version == 0x65)
		packetSize = 0;		// TODO: Decrypt the packet size.
	else
		logger->warning(format("[%1%] Unknown protocol version recieved.") % get_ip());

	recieve_new_packet();
}

void Client::send(const packet::Packet* packet)
{
	send(packet->serialize());
}

void Client::send(const Buffer& buf)
{
	try {
		socket.send(buffer(buf.data(), buf.length()));
	} catch(system::error_code ec) {
		logger->info(format("Sending to %1% failed (%2%).") % get_ip() % ec.message());
	}
}

Client::~Client()
{
	delete handler;
}

}