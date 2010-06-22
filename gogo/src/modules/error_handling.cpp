#include "../GoGoClient.h"

#include <cockpit/Transmitter.h>
#include <cockpit/packet/Lookup.h>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace cockpit::packet;

void GoGoClient::OnFailedParse(uint16_t commandID, const uint8_t* /* parameters */, uint16_t /* length */)
{
	try {
		PacketInfo info = lookup(commandID);
		logger->info(format("[%1%] Parsing failed for %2% (doc=\"%3%\", id=%4%)") % transmitter->get_ip() % info.name % info.doc % info.commandId);

	} catch(const packet::BadCommandId&) {
		logger->error("Cockpit tried to parse a commandID that isn't valid. It will be dropped. Please report this error.");
	}
}

void GoGoClient::OnInvalidPacketType(uint16_t commandID)
{
	logger->info(format("[%1%] Nonpresent commandID [%2%] detected. This is not part of the protocol!") % transmitter->get_ip() % commandID);
}
