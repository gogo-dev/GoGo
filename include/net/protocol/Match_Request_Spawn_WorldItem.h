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

// Request Spawn WorldItem
class Match_Request_Spawn_WorldItem : public Packet
{
private:
	packet::MUID uidChar;
	packet::int32 ItemID;
	packet::position ItemPos;
	packet::floating_point ItemDropDelayTime;

public:
	enum { packetID = 1544 };

	Match_Request_Spawn_WorldItem(packet::MUID uidChar, packet::int32 ItemID, packet::position ItemPos, packet::floating_point ItemDropDelayTime);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}