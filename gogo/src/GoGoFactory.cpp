#include "GoGoFactory.h"

#include "GoGoClient.h"

#include <cassert>

GoGoFactory::GoGoFactory(cockpit::Logger* _logger, GunzDB* _database)
{
	assert(_logger);
	logger = _logger;

	assert(_database);
	database = _database;
}

cockpit::ClientHandler* GoGoFactory::create_client_handler()
{
	return new GoGoClient(logger, &santa, database);
}
