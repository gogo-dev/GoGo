#pragma once
#include <boost/shared_array.hpp>
#include <boost/cstdint.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Client.h"
 
class Server
{
public:
	Server(boost::asio::io_service& serivce, const boost::asio::ip::tcp::endpoint& endpoint);
	void start_accept();

private:
	void handle_accept(ClientPtr, const boost::system::error_code&);

	boost::asio::ip::tcp::acceptor mAcceptor;
	boost::uint64_t mClientId;
};