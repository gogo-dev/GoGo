#pragma once
#include <boost/asio.hpp>
#include <util/Logger.h>

class Client
{
public:
	boost::asio::ip::tcp::socket socket;
	Logger* logger;

public:
	Client(Logger* logger, boost::asio::io_service& service);
	void start();
};
