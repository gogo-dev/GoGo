#include "../GoGoClient.h"

#include <cockpit/Transmitter.h>
#include <cockpit/packet/Lookup.h>
#include <cockpit/Logger.h>

#include <boost/format.hpp>

#include <cassert>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace cockpit::packet;

void GoGoClient::OnFailedParse(uint16_t commandID, const uint8_t* /* parameters */, uint16_t /* length */)
{
	try {
		PacketInfo info = lookup(commandID);
		logger->info(format("[%1%] Packet parsing failed for %2% (doc=\"%3%\", id=%4%)") % transmitter->get_ip() % info.name % info.doc % info.commandId);

	} catch(const packet::BadCommandId&) {
		assert(0 && "If this happens, it means cockpit is fucking up. Please investigate.");
	}
}

void GoGoClient::OnInvalidPacketType(uint16_t commandID)
{
	logger->info(format("[%1%] Nonpresent commandID [%2%] detected. This is not part of the protocol!") % transmitter->get_ip() % commandID);
}

void GoGoClient::OnUnimplementedPacket(uint16_t commandID)
{
	PacketInfo info = lookup(commandID);
	logger->debug(format("[%1%] Unhandled packet: %2% (doc=\"%3%\", id=%4%)") % transmitter->get_ip() % info.name % info.doc % info.commandId);
}

void GoGoClient::OnFuckUp(uint16_t commandID, const uint8_t*, uint16_t)
{
	try {
		PacketInfo info = lookup(commandID);
		logger->info(format("[%1%] There was an unhandled exception in the handler for %2% (doc=\"%3%\", id=%4%)") % transmitter->get_ip() % info.name % info.doc % info.commandId);

	} catch(const packet::BadCommandId&) {
		assert(0 && "If this happens, it means cockpit is fucking up. Please investigate.");
	}
}

void GoGoClient::OnExceptionalFuckUp(const char* what, uint16_t commandID, const uint8_t*, uint16_t)
{
	assert(what && "Wait, what? If this happens, it means cockpit is fucking up. Please investigate.");

	try {
		PacketInfo info = lookup(commandID);
		logger->info(format("[%1%] There was an unhandled exception (%2%) in the handler for %3% (doc=\"%4%\", id=%5%)") % what % info.name % info.doc % info.commandId);

	} catch(const packet::BadCommandId&) {
		assert(0 && "If this happens, it means cockpit is fucking up. Please investigate.");
	}
}
