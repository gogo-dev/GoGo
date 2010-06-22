#include "GoGoFactory.h"
#include "GoGoClient.h"

#include <cassert>

using namespace std;
using namespace cockpit;

GoGoFactory::GoGoFactory(Logger* _logger, GunzDB* _database)
{
	assert(_logger);
	logger = _logger;

	assert(_database);
	database = _database;
}

auto_ptr<ClientHandler> GoGoFactory::create_client_handler()
{
	return auto_ptr<ClientHandler>(new GoGoClient(logger, &santa, database));
}
