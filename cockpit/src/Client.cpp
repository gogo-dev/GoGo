#include "Client.h"

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace cockpit {

Client::Client(Logger* _logger, ClientHandlerFactory* factory, io_service* io)
	: logger(_logger), handler(factory->create_client_handler()), socket(*io)
{
}

string Client::get_ip() const
{
	return socket.local_endpoint().address().to_string();
}

void Client::send_handshake()
{
}

Client::~Client()
{
	delete handler;
}

}