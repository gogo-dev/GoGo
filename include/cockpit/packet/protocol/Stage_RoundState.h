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

// Sync State of a StageRound
class Stage_RoundState : public Packet
{
private:
	packet::MUID uidStage;
	packet::int32 nRound;
	packet::int32 nState;
	packet::int32 nArg;

public:
	enum { packetID = 1501 };

	Stage_RoundState(packet::MUID uidStage, packet::int32 nRound, packet::int32 nState, packet::int32 nArg);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Stage_RoundState()
	{
	}

};

}
}
}