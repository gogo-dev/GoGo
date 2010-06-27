#include "GoGoClient.h"

#include <cockpit/Transmitter.h>
#include <cockpit/packet/Registry.h>
#include <cockpit/packet/Lookup.h>

#include <gunz/MUIDSanta.h>

#include <boost/bind.hpp>

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

	assert(_database);
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
	registry->OnUnimplementedPacket = bind(&GoGoClient::OnUnimplementedPacket, this, _1);

	registry->Match_Login = bind(&GoGoClient::OnMatchLogin, this, _1, _2, _3, _4);
	registry->Match_RequestAccountCharList = bind(&GoGoClient::OnCharList, this);
	registry->Match_RequestCreateChar = bind(&GoGoClient::OnCharCreate, this, _1, _2, _3, _4, _5, _6, _7);
	registry->Match_RequestAccountCharInfo = bind(&GoGoClient::OnCharInfo, this, _1);
	registry->Match_RequestDeleteChar = bind(&GoGoClient::OnCharDelete, this, _1, _2, _3);
	registry->Match_RequestSelectChar = bind(&GoGoClient::OnCharSelect, this, _1, _2);
}

GoGoClient::~GoGoClient()
{
	santa->give_back(myMUID);
}
