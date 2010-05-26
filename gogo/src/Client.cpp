#include "Client.h"
#include <boost/format.hpp>

Client::Client(Logger* _logger, boost::asio::io_service &service)
	: socket(service), logger(_logger)
{
}

void Client::start()
{
	logger->print(
		(boost::format("Connection from \"%1%\".") %
			socket.remote_endpoint().address().to_string()
		).str()
	);
}
