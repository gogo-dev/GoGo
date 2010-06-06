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

// Ready to Handle stage
class Agent_StageReady : public Packet
{
private:
	packet::MUID StageUID;

public:
	enum { packetID = 5053 };

	Agent_StageReady(packet::MUID StageUID);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Agent_StageReady()
	{
	}

};

}
}
}