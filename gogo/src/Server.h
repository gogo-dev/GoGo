#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/asio.hpp>
#include "Client.h"
 
class Server
{
public:
	Server(boost::asio::io_service& serivce, const boost::asio::ip::tcp::endpoint& endpoint);
	void start_accept();

private:
	void handle_accept(boost::shared_ptr<Client> client, const boost::system::error_code& error);

	boost::asio::ip::tcp::acceptor acceptor;
	boost::uint64_t clientId;
};
