#include "GoGoFactory.h"
#include "GoGoClient.h"

#include <cassert>

using namespace std;
using namespace boost;
using namespace cockpit;

GoGoFactory::GoGoFactory(Logger* _logger, GunzDB* _database, const function<void (gunz::ChannelList*)>& initChannelList)
	: channelList(&santa)
{
	assert(_logger);
	logger = _logger;

	assert(_database);
	database = _database;

	initChannelList(&channelList);
}

auto_ptr<ClientHandler> GoGoFactory::create_client_handler()
{
	return auto_ptr<ClientHandler>(
		new GoGoClient(
			logger, &channelList, &santa, database
		)
	);
}
