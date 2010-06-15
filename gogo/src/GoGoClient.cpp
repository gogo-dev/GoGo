#include "GoGoClient.h"

#include <cockpit/Transmitter.h>
#include <cockpit/packet/Registry.h>

#include "MUIDSanta.h"

#include <cassert>

using namespace boost;
using namespace cockpit;

GoGoClient::GoGoClient(Logger* _logger, MUIDSanta* _santa)
{
	assert(_logger);
	logger = _logger;

	assert(_santa);
	santa = _santa;
	myMUID = santa->get();
}

void GoGoClient::initialize(Transmitter* _transmitter, packet::Registry* _registry)
{
	transmitter = _transmitter;
	registry = _registry;

	// TODO: Register all necessary handlers.
}

GoGoClient::~GoGoClient()
{
	santa->give_back(myMUID);
}
