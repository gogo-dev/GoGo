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

// Request LiveCheck for Agent
class Match_Agent_RequestLiveCheck : public Packet
{
private:
	packet::uint32 TimeStamp;
	packet::uint32 StageCount;
	packet::uint32 UserCount;

public:
	enum { packetID = 5011 };

	Match_Agent_RequestLiveCheck(packet::uint32 TimeStamp, packet::uint32 StageCount, packet::uint32 UserCount);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}