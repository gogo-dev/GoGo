#include <boost/asio/io_service.hpp>	// Fixes a bug on VS.

#include "ChannelLoader.h"
#include "Configuration.h"
#include "ConsoleLogger.h"
#include "GoGoFactory.h"

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

static string load_file(const char* filename)
{
	ifstream f(filename);

	string out;
	string line;

	while(getline(f, line))
		out += line;

	return out;
}

static void add_all_channels(gunz::ChannelList* channelList, gunz::MUIDSanta* santa)
{
	typedef vector<gunz::Channel::Traits> TraitList;
	TraitList traits = parse_channel_list(load_file("channel.xml"), santa);

	for(TraitList::iterator current = traits.begin(), end = traits.end(); current != end; ++current)
		channelList->Add(*current);
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
