#include <cockpit/MatchServer.h>

#include "Client.h"

#include <cockpit/Logger.h>
#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>

#include <cassert>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace cockpit {

struct MatchServer::Data : boost::noncopyable
{
	Logger* logger;
	ClientHandlerFactory* factory;
	tcp::acceptor acceptor;

	Data(Logger* logger, ClientHandlerFactory* factory, io_service* io, uint16_t port);
	~Data();
};

MatchServer::Data::Data(Logger* _logger, ClientHandlerFactory* _factory, io_service* io, uint16_t port)
	: logger(_logger), factory(_factory), acceptor(*io, tcp::endpoint(tcp::v4(), port))
{
	assert(_logger);
	assert(_factory);
	assert(io);
}

MatchServer::Data::~Data()
{
}

static void handle_accepted_client(MatchServer::Data* d,
                                   shared_ptr<Client> client,
                                   system::error_code err);

static void asynchronously_accept_new_client(MatchServer::Data* d)
{
	assert(d);

	shared_ptr<Client> client = make_shared<Client>(d->logger, d->factory, &d->acceptor.io_service());

	d->acceptor.async_accept(
		client->socket,
		bind(
			&handle_accepted_client,
			d, client, _1
		)
	);
}

static void handle_accepted_client(MatchServer::Data* d,
                                   shared_ptr<Client> client,
                                   system::error_code err)
{
	assert(d);
	asynchronously_accept_new_client(d);

	if(err)
		d->logger->info(format("[%1%] Chickened out: %2%") % client->get_ip() % err.message());
	else
	{
		d->logger->debug(format("[%1%] Connected!") % client->get_ip());
		client->start();
	}
}

MatchServer::MatchServer(Logger* logger,
                         ClientHandlerFactory* factory,
                         io_service* io,
                         uint16_t port)
	: d(new Data(logger, factory, io, port))
{
	assert(d);
	assert(d->logger);
	assert(d->factory);
}

void MatchServer::run()
{
	asynchronously_accept_new_client(d);
}

MatchServer::~MatchServer()
{
	delete d;
}

}
