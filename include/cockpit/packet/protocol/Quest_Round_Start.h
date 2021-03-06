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

// Quest Start Round
class Quest_Round_Start : public Packet
{
private:
	packet::uint8 round;

public:
	enum { packetID = 6100 };

	Quest_Round_Start(const packet::uint8& round);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Round_Start()
	{
	}

};

}
}
}
