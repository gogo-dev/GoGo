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

// Response Create Character
class Match_ResponseCreateChar : public Packet
{
private:
	packet::int32 Result;
	packet::string CharName;

public:
	enum { packetID = 1712 };

	Match_ResponseCreateChar(packet::int32 Result, packet::string CharName);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_ResponseCreateChar()
	{
	}

};

}
}
}