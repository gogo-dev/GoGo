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

// Ask Sponsor's Agreement
class Match_Clan_AskSponsorAgreement : public Packet
{
private:
	packet::int32 RequestID;
	packet::string ClanName;
	packet::MUID uidClanMaster;
	packet::string szClanMaster;

public:
	enum { packetID = 2002 };

	Match_Clan_AskSponsorAgreement(const packet::int32& RequestID, const packet::string& ClanName, const packet::MUID& uidClanMaster, const packet::string& szClanMaster);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Clan_AskSponsorAgreement()
	{
	}

};

}
}
}
