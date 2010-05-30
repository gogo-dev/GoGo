#include <util/ConsoleLogger.h>

#include <cstdlib>
#include <exception>
#include <boost/asio.hpp>
#include "Structures.h"
#include "Server.h"

#include <database/MySQLGunzDB.h>

#include <boost/thread.hpp>

using namespace boost;
using namespace boost::asio;

static void run_server_on(uint16_t port, Logger* logger)
{
	io_service service(thread::hardware_concurrency());
	ip::tcp::endpoint endpoint(ip::tcp::v4(), port);

	Server server(logger, service, endpoint);

	// This loop ensures that the server is restarted if we get any shenanigans
	// happening. Hopefully, we won't make segfaulting a regular problem =/
	for(;;)
	{
		try
		{
			service.run();
			break;	// If this is hit, the IO service exited without a hitch.
		}
		catch(const std::exception& ex)
		{
			logger->error(format("Fatal error, server restarting: %1%") % ex.what());
		}
	}
}

int main()
{
	ConsoleLogger logger;
	MySQLGunzDB db("", "", "", "");

	run_server_on(6000, &logger);

	return 0;
}
