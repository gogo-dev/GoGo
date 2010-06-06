#pragma once
#include <cockpit/MatchServer.h>
#include <cockpit/Socket.h>
#include <boost/asio/io_service.hpp>

namespace cockpit {

class ClientHandler;
class ClientHandlerFactory;

struct MatchServer::ClientConnection
{
	ClientHandler* handler;
	Socket s;

	ClientConnection(boost::asio::io_service* io, ClientHandlerFactory* factory);

	~ClientConnection();
};

}