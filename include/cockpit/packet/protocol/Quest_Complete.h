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

// Complete Quest
class Quest_Complete : public Packet
{
private:
	packet::blob RewardInfo;

public:
	enum { packetID = 6054 };

	Quest_Complete(const packet::blob& RewardInfo);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Complete()
	{
	}

};

}
}
}
