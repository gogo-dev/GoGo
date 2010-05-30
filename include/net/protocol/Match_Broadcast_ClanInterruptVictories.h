/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <net/packet.h>
#include <boost/cstdint.hpp>
#include <net/PacketParameters.h>

namespace packet {
namespace protocol {

// Broadcast Clan Interrupt Victories
class Match_Broadcast_ClanInterruptVictories : public Packet
{
private:
	packet::string strWinnerClanName;
	packet::string strLoserClanName;
	packet::int32 nVictories;

public:
	enum { packetID = 2201 };

	Match_Broadcast_ClanInterruptVictories(packet::string strWinnerClanName, packet::string strLoserClanName, packet::int32 nVictories);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}