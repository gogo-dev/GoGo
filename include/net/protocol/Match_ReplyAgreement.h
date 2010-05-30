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

// Reply Agreement
class Match_ReplyAgreement : public Packet
{
private:
	packet::MUID uidProposer;
	packet::MUID uidChar;
	packet::string Replier;
	packet::int32 ProposalMode;
	packet::int32 RequestID;
	packet::boolean Agreement;

public:
	enum { packetID = 1564 };

	Match_ReplyAgreement(packet::MUID uidProposer, packet::MUID uidChar, packet::string Replier, packet::int32 ProposalMode, packet::int32 RequestID, packet::boolean Agreement);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}