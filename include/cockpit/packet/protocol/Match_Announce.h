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

// Announce Server Message
class Match_Announce : public Packet
{
private:
	packet::uint32 Type;
	packet::string Msg;

public:
	enum { packetID = 402 };

	Match_Announce(const packet::uint32& Type, const packet::string& Msg);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Announce()
	{
	}

};

}
}
}
