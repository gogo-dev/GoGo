#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/asio.hpp>

#include <util/Logger.h>

#include "Client.h"

class Server
{
private:
	Logger* logger;
	boost::asio::ip::tcp::acceptor acceptor;
	boost::uint64_t clientID;

private:
	void handle_accept(
		boost::shared_ptr<Client> client,
		const boost::system::error_code& error
	);

	void start_accept();

public:
	Server(
		Logger* logger,
		boost::asio::io_service& serivce,
		const boost::asio::ip::tcp::endpoint& endpoint
	);
};
