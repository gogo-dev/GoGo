#include "ClientConnection.h"

#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>

using namespace boost::asio;

namespace cockpit {

MatchServer::ClientConnection::ClientConnection(io_service* io,
                                                ClientHandlerFactory* factory)
	: handler(factory->create_client_handler()), s(io)
{
}

MatchServer::ClientConnection::~ClientConnection()
{
	delete handler;
}

}