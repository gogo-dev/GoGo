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

// Request callback sacrifice item
class Quest_Callback_Result : public Packet
{
private:
	packet::int32 Result;
	packet::MUID requesterofcallbacksacrificeitem_;
	packet::int32 Slotindex;
	packet::int32 ItemID;

public:
	enum { packetID = 21010 };

	Quest_Callback_Result(packet::int32 Result, packet::MUID requesterofcallbacksacrificeitem_, packet::int32 Slotindex, packet::int32 ItemID);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}