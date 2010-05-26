#include "Server.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost;

Server::Server(
	Logger* _logger,
	boost::asio::io_service& service,
	const boost::asio::ip::tcp::endpoint& endpoint
)
	: logger(_logger), acceptor(service, endpoint)
{
	clientID = 0;
	start_accept();
}

void Server::start_accept()
{
	shared_ptr<Client> client(new Client(logger, acceptor.io_service()));

	logger->print("Starting to accept...");

	acceptor.async_accept(
		client->socket,
		bind(&Server::handle_accept, this, client, asio::placeholders::error)
	);
}

void Server::handle_accept(shared_ptr<Client> client, const boost::system::error_code& error)
{
	if(!error)
	{
		client->start();
		start_accept();
	}
}
