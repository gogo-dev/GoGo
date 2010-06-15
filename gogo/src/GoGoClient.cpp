#include "GoGoClient.h"

#include <cockpit/Transmitter.h>
#include <cockpit/packet/Registry.h>

#include "MUIDSanta.h"

#include <cassert>

using namespace std;
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

void GoGoClient::register_handler(const signals2::connection& connection)
{
	activeHandlers.push_back(connection);
}

void GoGoClient::initialize(Transmitter* _transmitter, packet::Registry* _registry)
{
	assert(_transmitter);
	assert(_registry);

	transmitter = _transmitter;
	registry = _registry;

	// TODO: Register all necessary handlers.
	// Ex: register_handler(Net_OnConnect.connect(&GoGoClient::OnConnect, this));
	// Remove the sample code when we have live, production code to use as a sample.
	register_handler(registry->Match_Login.connect(bind(&GoGoClient::OnMatchLogin, this, _1, _2, _3, _4)));
}

GoGoClient::~GoGoClient()
{
	santa->give_back(myMUID);

	// Disconnect all active signals.
	for(vector<signals2::connection>::iterator i = activeHandlers.begin(); i != activeHandlers.end(); ++i)
		i->disconnect();
}
