#include <boost/asio/io_service.hpp>	// Fixes a bug on VS.

#include "ConsoleLogger.h"
#include "GoGoFactory.h"
#include "Configuration.h"

#include <cockpit/MatchServer.h>
#include <database/GunzDB.h>
#include <database/MySQLGunzDB.h>
#include <gunz/Channel.h>

#include <version.h>

#include <algorithm>
#include <boost/thread.hpp>
#include <cctype>
#include <cstdio>
#include <exception>
#include <fstream>
#include <map>

using namespace std;
using namespace boost;

static Configuration get_config(const char* filename)
{
	ifstream is(filename);
	return Configuration(is);
}

static void add_all_channels(gunz::ChannelList* channelList)
{
	channelList->Add(
		gunz::Channel::Traits()
		//gunz::ChannelTraits(
		//	0,
		//	conf->get_value<string>(channelPrefix + "name"),
		//	conf->get_value<uint32_t>(channelPrefix + "maxPlayers"),
		//	get_rule(conf->get_value<string>(channelPrefix + "rule")),
		//	get_type(conf->get_value<string>(channelPrefix + "type")),
		//	conf->get_value<uint8_t>(channelPrefix + "minLevel"),
		//	conf->get_value<uint8_t>(channelPrefix + "maxLevel")
		//)
	);
}

int main()
{
	printf("%s", "GoGo " GOGO_VERSION " is starting...\n");

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

		GoGoFactory factory(logger, &database, add_all_channels);

		uint16_t port = conf.get_value<uint16_t>("server.port", 6000);

		cockpit::MatchServer server(logger, &factory, port);

		logger->info(format("Now listening on port %1%. Let's rock!") % port);

		server.start();
		server.wait();

	} catch(const SyntaxError& ex) {
		logger->warning(format("Syntax Error on line %1%: %2%") % ex.lineNumber % ex.what());
	} catch(const runtime_error& ex) {
		logger->warning(format("Runtime error: %1%") % ex.what());
	} catch(const logic_error& ex) {
		logger->error(format("Logic error! Please report this: %1%") % ex.what());
	} catch(const std::exception& ex) {
		logger->error(format("Fatal error: %1%") % ex.what());
	} catch(...) {
		logger->error("Unknown exception encountered. This is a programming error. Report this message to the bugtracker.");
		return 1;
	}

	return 0;
}
