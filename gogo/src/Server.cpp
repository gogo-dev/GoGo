#include "Server.h"
#include <boost/shared_array.hpp>
#include <boost/cstdint.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

Server::Server(boost::asio::io_service& service, const boost::asio::ip::tcp::endpoint& endpoint)
	: mAcceptor (service, endpoint)
{
	mClientId = 0;
	start_accept();
}

void Server::start_accept()
{
	ClientPtr Client (new Client (mAcceptor.io_service()));
	printf ("Starting to accept.\n");
	mAcceptor.async_accept (Client->socket(), 
		boost::bind (&Server::handle_accept, this, Client, 
			boost::asio::placeholders::error));
}

void Server::handle_accept(ClientPtr Client, const boost::system::error_code& error)
{
	if (!error)
	{
		Client->start();
		start_accept();
	}
}