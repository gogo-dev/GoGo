#include "GoGoClient.h"

#include <cockpit/Transmitter.h>
#include <cockpit/packet/Registry.h>

#include <cassert>

using namespace boost;
using namespace cockpit;

GoGoClient::GoGoClient(Logger* _logger)
{
	assert(_logger);
	logger = _logger;
}

void GoGoClient::initialize(Transmitter* _transmitter, packet::Registry* _registry)
{
	transmitter = _transmitter;
	registry = _registry;

	// TODO: Register all necessary handlers.
}

array<uint8_t, 26> GoGoClient::handshake(const asio::ip::tcp::socket& s) const
{
	// TODO: A synchronous handshake. <- Don't say that out loud, it's misleading =P
	return array<uint8_t, 26>();
}

GoGoClient::~GoGoClient()
{
}
