#pragma once
#include <cockpit/Logger.h>
#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/Packet.h>
#include <cockpit/packet/Registry.h>

#include <util/buffer.h>

#include <string>

#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/cstdint.hpp>

namespace cockpit {

class Client : public Transmitter, public boost::enable_shared_from_this<Client>
{
private:
	Logger* logger;
	ClientHandler* handler;
	packet::Registry registry;
	boost::array<boost::uint8_t, 26> cryptoKey;

public:
	boost::asio::ip::tcp::socket socket;

	void recieve_new_packet();

	void on_packet_header(
		boost::shared_ptr<boost::asio::mutable_buffer> rawPacket,
		boost::system::error_code err,
		size_t bytesTransferred
	);

public:
	Client(Logger* logger, ClientHandlerFactory* factory, boost::asio::io_service* io);

	void start();

	void send(const packet::Packet* packet);
	void send(const Buffer& buf);

	std::string get_ip() const;

	~Client();
};

}