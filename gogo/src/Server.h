#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/asio.hpp>

#include <cockpit/Logger.h>

#include "Client.h"
#include "MUIDSanta.h"

class Server
{
private:
	cockpit::Logger* logger;
	boost::asio::ip::tcp::acceptor acceptor;
	MUIDSanta santa;

private:
	void handle_accept(
		boost::shared_ptr<Client> client,
		const boost::system::error_code& error
	);

	void start_accept();

public:
	Server(
		cockpit::Logger* logger,
		boost::asio::io_service& serivce,
		const boost::asio::ip::tcp::endpoint& endpoint
	);
};
