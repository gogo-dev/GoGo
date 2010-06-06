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

// Request Join Clan
class Match_Clan_RequestJoinClan : public Packet
{
private:
	packet::MUID uidChar;
	packet::string ClanName;
	packet::string szJoiner;

public:
	enum { packetID = 2008 };

	Match_Clan_RequestJoinClan(packet::MUID uidChar, packet::string ClanName, packet::string szJoiner);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Clan_RequestJoinClan()
	{
	}

};

}
}
}