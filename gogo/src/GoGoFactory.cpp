#include "GoGoFactory.h"

#include "GoGoClient.h"

#include <cassert>

GoGoFactory::GoGoFactory(cockpit::Logger* _logger)
{
	assert(_logger);
	logger = _logger;
}

cockpit::ClientHandler* GoGoFactory::create_client_handler()
{
	return new GoGoClient(logger, &santa);
}
