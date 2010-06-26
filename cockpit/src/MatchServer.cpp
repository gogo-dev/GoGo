#include <cockpit/MatchServer.h>

#include "Client.h"

#include <cockpit/Logger.h>
#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>

#include <cassert>
#include <cstddef>

#include <algorithm>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace cockpit {

struct MatchServer::Data : boost::noncopyable
{
	Logger* logger;
	ClientHandlerFactory* factory;

	io_service io;
	tcp::acceptor acceptor;

	thread* threadPool;
	size_t threadPoolLength;

	bool isServerRunning;

	Data(Logger* logger, ClientHandlerFactory* factory, uint16_t port, size_t threadCount);
	~Data();
};

MatchServer::Data::Data(Logger* _logger, ClientHandlerFactory* _factory, uint16_t port, size_t threadCount)
	: logger(_logger), factory(_factory), acceptor(io, tcp::endpoint(tcp::v4(), port))
{
	assert(_logger);
	assert(_factory);

	threadPoolLength = threadCount;
	threadPool = new thread[threadPoolLength];

	isServerRunning = false;
}

MatchServer::Data::~Data()
{
	delete[] threadPool;
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

	if(!err)
		client->start();
}

MatchServer::MatchServer(Logger* logger,
                         ClientHandlerFactory* factory,
                         uint16_t port)
	: d(new Data(logger, factory, port, thread::hardware_concurrency() * 2))
{
	assert(d);
}

MatchServer::MatchServer(Logger* logger,
                         ClientHandlerFactory* factory,
                         uint16_t port,
                         size_t threadCount)
	: d(new Data(logger, factory, port, threadCount))
{
	assert(d);
}

static void spawn_thread(thread& t, io_service* io)
{
	t = thread(bind(&io_service::run, io));
}

void MatchServer::start()
{
	if(d->isServerRunning)
		return;

	d->isServerRunning = true;

	asynchronously_accept_new_client(d);
	std::for_each(d->threadPool, d->threadPool + d->threadPoolLength, bind(spawn_thread, _1, &(d->io)));
}

void MatchServer::stop()
{
	if(!d->isServerRunning)
		return;

	d->isServerRunning = false;

	d->io.stop();
}

void MatchServer::wait()
{
	if(!d->isServerRunning)
		return;

	std::for_each(d->threadPool, d->threadPool + d->threadPoolLength, bind(&thread::join, _1));
}

MatchServer::~MatchServer()
{
	stop();
	delete d;
}

}
