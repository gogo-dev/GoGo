#include <cstdlib>
#include <boost/asio.hpp>
#include "Structures.h"
#include "Server.h"

using namespace boost;

int main()
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint (boost::asio::ip::tcp::v4(), 6000);
	Server *server = new Server(io_service, endpoint);
	io_service.run();
	return 0;
}
