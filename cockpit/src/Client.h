#pragma once
#include <cockpit/Logger.h>
#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>

#include <string>

#include <boost/asio/ip/tcp.hpp>

namespace cockpit {

class Client
{
private:
	Logger* logger;
	ClientHandler* handler;

public:
	boost::asio::ip::tcp::socket socket;

public:
	Client(Logger* logger, ClientHandlerFactory* factory, boost::asio::io_service* io);

	void send_handshake();

	std::string get_ip() const;

	~Client();
};

}