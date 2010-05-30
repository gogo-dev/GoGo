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

// Request Expel ClanMember
class Match_Clan_Admin_RequestExpelMember : public Packet
{
private:
	packet::MUID uidClanAdmin;
	packet::string szMember;

public:
	enum { packetID = 2019 };

	Match_Clan_Admin_RequestExpelMember(packet::MUID uidClanAdmin, packet::string szMember);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}