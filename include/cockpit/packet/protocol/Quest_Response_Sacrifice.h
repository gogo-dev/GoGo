/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <boost/cstdint.hpp>
#include <cockpit/packet/Packet.h>
#include <cockpit/packet/Parameters.h>

namespace cockpit {
namespace packet {
namespace protocol {

// Response drop sacrifice item
class Quest_Response_Sacrifice : public Packet
{
private:
	packet::int32 Result;
	packet::MUID requesterofdropsacrificeitem_;
	packet::int32 Slotindex;
	packet::int32 ItemID;

public:
	enum { packetID = 21008 };

	Quest_Response_Sacrifice(packet::int32 Result, packet::MUID requesterofdropsacrificeitem_, packet::int32 Slotindex, packet::int32 ItemID);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Response_Sacrifice()
	{
	}

};

}
}
}