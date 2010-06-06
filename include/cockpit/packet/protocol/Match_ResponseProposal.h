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

// Response Proposal
class Match_ResponseProposal : public Packet
{
private:
	packet::int32 Result;
	packet::int32 ProposalMode;
	packet::int32 RequestID;

public:
	enum { packetID = 1562 };

	Match_ResponseProposal(packet::int32 Result, packet::int32 ProposalMode, packet::int32 RequestID);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_ResponseProposal()
	{
	}

};

}
}
}