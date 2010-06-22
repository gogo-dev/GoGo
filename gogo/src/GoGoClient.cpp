#include "GoGoClient.h"

#include <cockpit/Transmitter.h>
#include <cockpit/packet/Registry.h>
#include <cockpit/packet/Lookup.h>

#include "MUIDSanta.h"

#include <cassert>

using namespace std;
using namespace boost;
using namespace cockpit;

GoGoClient::GoGoClient(Logger* _logger, MUIDSanta* _santa, GunzDB* _database)
{
	assert(_logger);
	logger = _logger;

	assert(_santa);
	santa = _santa;
	myMUID = santa->get();

	assert (database);
	database = _database;
}

void GoGoClient::initialize(Transmitter* _transmitter, packet::Registry* _registry)
{
	assert(_transmitter);
	assert(_registry);

	transmitter = _transmitter;
	registry = _registry;

	registry->OnFailedParse = bind(&GoGoClient::OnFailedParse, this, _1, _2, _3);
	registry->OnInvalidPacketType = bind(&GoGoClient::OnInvalidPacketType, this, _1);

	registry->Match_Login = bind(&GoGoClient::OnMatchLogin, this, _1, _2, _3, _4);
	registry->Match_RequestAccountCharList = bind(&GoGoClient::OnCharList, this);
}

void GoGoClient::OnFailedParse(boost::uint16_t commandID, const boost::uint8_t* /* parameters */, boost::uint16_t /* length */)
{
	try {
		packet::PacketInfo info = packet::lookup(commandID);
		logger->info(format("[%1%] Parsing failed for %2% (doc=\"%3%\", id=%4%)") % transmitter->get_ip() % info.name % info.doc % info.commandId);

	} catch(const packet::BadCommandId&) {
		logger->error("Cockpit tried to parse a commandID that isn't valid. It will be dropped. Please report this error.");
	}
}

void GoGoClient::OnInvalidPacketType(boost::uint16_t commandID)
{
	logger->info(format("[%1%] Nonpresent commandID [%2%] detected. This is not part of the protocol!") % transmitter->get_ip() % commandID);
}

GoGoClient::~GoGoClient()
{
	santa->give_back(myMUID);
}
