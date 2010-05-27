#include "Server.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost;

Server::Server(
	Logger* _logger,
	asio::io_service& service,
	const asio::ip::tcp::endpoint& endpoint
)
	: logger(_logger), acceptor(service, endpoint)
{
	start_accept();

	logger->info(format("GoGo has initialized and is running on port %1%!") % endpoint.port());
}

void Server::start_accept()
{
	shared_ptr<Client> client(new Client(logger, acceptor.io_service(), &santa));

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
	else
	{
		logger->warning("New connection could not be made.");
	}
}
