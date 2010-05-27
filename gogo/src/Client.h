#pragma once
#include <boost/asio.hpp>
#include <util/Logger.h>
#include "Structures.h"

class Client
{
public:
	boost::asio::ip::tcp::socket socket;
	Logger* logger;

public:
	Client(Logger* logger, boost::asio::io_service& service);
	void start();

private:
	void send_handshake();
	boost::uint8_t cryptkey[32];
	MUID clientid;
};
