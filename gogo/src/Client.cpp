#include "Client.h"

Client::Client(boost::asio::io_service &service) : mSocket (service)
{
}

void Client::start()
{
	printf ("Connection from: %s\n", mSocket.remote_endpoint().address().to_string().c_str());
}