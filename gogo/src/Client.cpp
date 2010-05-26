#include "Client.h"
#include <boost/format.hpp>

using namespace boost;

Client::Client(Logger* _logger, asio::io_service &service)
	: socket(service), logger(_logger)
{
}

void Client::start()
{
	logger->info(
		format("Connection from [%1%]") % socket.remote_endpoint().address().to_string()
	);
}
