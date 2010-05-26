#pragma once
#include <boost/asio.hpp>

class Client
{
public:
	boost::asio::ip::tcp::socket socket;

public:
	Client (boost::asio::io_service& service);
	void start();
};
