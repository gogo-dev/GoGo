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

// Notify Emblem Ready
class Match_Clan_Local_EmblemReady : public Packet
{
private:
	packet::int32 ClanCLID;
	packet::string EmblemURL;

public:
	enum { packetID = 2055 };

	Match_Clan_Local_EmblemReady(packet::int32 ClanCLID, packet::string EmblemURL);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Clan_Local_EmblemReady()
	{
	}

};

}
}
}