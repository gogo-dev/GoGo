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

// Response Select Character
class Match_ResponseSelectChar : public Packet
{
private:
	packet::int32 Result;
	packet::blob CharInfo;
	packet::blob MyExtraCharInfo;

public:
	enum { packetID = 1704 };

	Match_ResponseSelectChar(packet::int32 Result, packet::blob CharInfo, packet::blob MyExtraCharInfo);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_ResponseSelectChar()
	{
	}

};

}
}
}