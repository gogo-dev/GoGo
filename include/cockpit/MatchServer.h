#pragma once
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>

namespace cockpit {

class Logger;
class ClientHandlerFactory;

class MatchServer : boost::noncopyable
{
private:
	Logger* logger;
	ClientHandlerFactory* factory;
	boost::asio::io_service* io;
	boost::asio::ip::tcp::acceptor* acceptor;

public: // Lol don't use this. Not part of the real public API.
	struct ClientConnection;

private:
	void accept_new_client();
	void handle_new_client(boost::shared_ptr<ClientConnection> client, boost::system::error_code error);

public:
	MatchServer(Logger* logger,
	            ClientHandlerFactory* factory,
	            boost::asio::io_service* io,
	            boost::uint16_t port);

	void run();

	~MatchServer();
};

}