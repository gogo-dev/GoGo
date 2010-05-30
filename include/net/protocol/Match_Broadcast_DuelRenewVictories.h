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

// Broadcast Duel Renew Victories
class Match_Broadcast_DuelRenewVictories : public Packet
{
private:
	packet::string strChampionName;
	packet::string strChannelName;
	packet::int32 nRoomNumber;
	packet::int32 nVictories;

public:
	enum { packetID = 2202 };

	Match_Broadcast_DuelRenewVictories(packet::string strChampionName, packet::string strChannelName, packet::int32 nRoomNumber, packet::int32 nVictories);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}