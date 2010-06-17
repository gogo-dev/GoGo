#include "ConsoleLogger.h"
#include "GoGoFactory.h"

#include <cockpit/MatchServer.h>

#include <exception>
#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>

using namespace boost;

int main()
{
	ConsoleLogger loggerImpl;
	cockpit::Logger* logger = &loggerImpl;

	GoGoFactory factory(logger);

	try {
		// TODO: Configuration loading for the port number.
		cockpit::MatchServer server(logger, &factory, 6000);

		server.start();
		server.wait();

	} catch(const std::exception& ex) {
		logger->error(format("Fatal error: %1%") % ex.what());
		return 1;
	} catch(...) {
		logger->error("Unknown exception encountered. This is a programming error. Report this message to the bugtracker.");
		return 2;
	}

	return 0;
}
