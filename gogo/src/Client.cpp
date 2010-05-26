#include "Client.h"

Client::Client(boost::asio::io_service &service)
	: socket (service)
{
}

void Client::start()
{
	printf ("Connection from: %s\n", socket.remote_endpoint().address().to_string().c_str());
}
