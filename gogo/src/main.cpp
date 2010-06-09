#include "ConsoleLogger.h"
#include <exception>
#include <boost/asio/io_service.hpp>

using namespace boost;

int main()
{
	ConsoleLogger loggerImpl;
	cockpit::Logger* logger = &loggerImpl;
	asio::io_service ioService;

	try {
		// IMPLEMENTATION HERE.

	} catch(const std::exception& ex) {
		logger->error(format("Fatal error: %1%") % ex.what());
		return 1;
	} catch(...) {
		logger->error("Unknown exception encountered. This is a programming error. Report this message to the bugtracker.");
		return 2;
	}

	return 0;
}
