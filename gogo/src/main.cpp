#include <boost/asio/io_service.hpp>	// Fixes a bug on VS.

#include "ConsoleLogger.h"
#include "GoGoFactory.h"
#include "Configuration.h"
#include "ChannelLoader.h"

#include <database/GunzDB.h>
#include <database/MySQLGunzDB.h>

#include <cockpit/MatchServer.h>

#include <algorithm>
#include <boost/thread.hpp>
#include <cctype>
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

static gunz::ChannelRule get_rule(const string& stringRep)
{
	return get_channel_attrib(stringRep, get_channel_rules());
}
static gunz::ChannelType get_type(const string& stringRep)
{
	return get_channel_attrib(stringRep, get_channel_types());
}

static void add_all_channels(const Configuration* conf, gunz::ChannelList* channelList)
{
	try {

		for(size_t num = 1;; ++num)
		{
			string channelPrefix = string("channel") + lexical_cast<string>(num) + string(".");

			channelList->AddChannel(
				gunz::ChannelTraits(
					0,
					conf->get_value<string>(channelPrefix + "name"),
					conf->get_value<uint32_t>(channelPrefix + "maxPlayers"),
					get_rule(conf->get_value<string>(channelPrefix + "rule")),
					get_type(conf->get_value<string>(channelPrefix + "type")),
					conf->get_value<uint8_t>(channelPrefix + "minLevel"),
					conf->get_value<uint8_t>(channelPrefix + "maxLevel")
				)
			);
		}

	} catch(SyntaxError) {
	}
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

		GoGoFactory factory(logger, &database, bind(add_all_channels, &conf, _1));

		uint16_t port = conf.get_value<uint16_t>("server.port", 6000);

		cockpit::MatchServer server(logger, &factory, port);

		logger->info(format("GoGo is listening on port %1%. Let's rock!") % port);

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
