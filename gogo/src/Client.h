#pragma once
#include <boost/asio.hpp>

class Client
{
public:
	Client (boost::asio::io_service& service);
	boost::asio::ip::tcp::socket& socket() { return mSocket; }
	void start();

private:
	boost::asio::ip::tcp::socket mSocket;

};
typedef boost::shared_ptr<Client> ClientPtr;
