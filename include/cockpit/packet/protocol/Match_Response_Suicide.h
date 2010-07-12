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

// Response Suicide
class Match_Response_Suicide : public Packet
{
private:
	packet::int32 Result;
	packet::MUID uidChar;

public:
	enum { packetID = 1532 };

	Match_Response_Suicide(const packet::int32& Result, const packet::MUID& uidChar);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Response_Suicide()
	{
	}

};

}
}
}
