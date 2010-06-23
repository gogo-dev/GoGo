#include "ConsoleLogger.h"
#include "GoGoFactory.h"
#include "Configuration.h"

#include <database/GunzDB.h>

#include <cockpit/MatchServer.h>

#include <exception>
#include <fstream>
#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>
#include <database/MySQLGunzDB.h>

using namespace std;
using namespace boost;

Configuration get_config(const char* filename)
{
	std::ifstream is(filename);
	return Configuration(is);
}

int main()
{
	ConsoleLogger loggerImpl;
	cockpit::Logger* logger = &loggerImpl;

	try {
		Configuration conf = get_config("gogo.conf");

		MySQLGunzDB database(
			logger,
			conf.get_value<string>("database.dbname", "GunzDB").c_str(),
			conf.get_value<string>("database.host", "localhost").c_str(),
			conf.get_value<string>("database.user", "root").c_str(),
			conf.get_value<string>("database.password", "password").c_str()
		);

		GoGoFactory factory(logger, &database);

		cockpit::MatchServer server(logger, &factory, conf.get_value<uint16_t>("server.port", 6000));

		server.start();
		server.wait();

	} catch(const SyntaxError& ex) {
		logger->warning(format("Syntax Error on line %1%: %2%") % ex.lineNumber % ex.what());
	} catch(const std::runtime_error& ex) {
		logger->warning(format("Runtime error: %1%") % ex.what());
	} catch(const std::logic_error& ex) {
		logger->error(format("Logic error! Please report this: %1%") % ex.what());
	} catch(const std::exception& ex) {
		logger->error(format("Fatal error: %1%") % ex.what());
	} catch(...) {
		logger->error("Unknown exception encountered. This is a programming error. Report this message to the bugtracker.");
		return 1;
	}

	return 0;
}
