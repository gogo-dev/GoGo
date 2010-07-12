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

// Response Join Clan
class Match_Clan_ResponseJoinClan : public Packet
{
private:
	packet::int32 Result;

public:
	enum { packetID = 2009 };

	Match_Clan_ResponseJoinClan(const packet::int32& Result);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Clan_ResponseJoinClan()
	{
	}

};

}
}
}
