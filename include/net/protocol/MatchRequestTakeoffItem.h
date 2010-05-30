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

// Request Takeoff Item
class MatchRequestTakeoffItem : public Packet
{
private:
	packet::MUID uid;
	packet::uint32 EquipmentSlot;
	packet::int32 one;

public:
	enum { packetID = 1825 };

	MatchRequestTakeoffItem(packet::MUID uid, packet::uint32 EquipmentSlot, packet::int32 one);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}