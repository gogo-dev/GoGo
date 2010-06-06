#include <cockpit/MatchServer.h>
#include "ClientConnection.h"

#include <cockpit/Logger.h>
#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>
#include <cockpit/Socket.h>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace cockpit {

MatchServer::MatchServer(Logger* _logger,
                         ClientHandlerFactory* _factory,
                         io_service* _io,
                         uint16_t port)
	: logger(_logger),
	  factory(_factory),
	  io(_io),

	  // If we ever have more than one dynamically allocated member,
	  // consider using the d-pointer idiom instead.
	  acceptor(new tcp::acceptor(*_io, tcp::endpoint(tcp::v4(), port)))
{
}

void MatchServer::run()
{
	accept_new_client();
}

MatchServer::~MatchServer()
{
	delete acceptor;
}

}