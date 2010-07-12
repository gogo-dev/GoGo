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

// Quest Game Info
class Quest_GameInfo : public Packet
{
private:
	packet::blob Info;

public:
	enum { packetID = 6051 };

	Quest_GameInfo(const packet::blob& Info);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_GameInfo()
	{
	}

};

}
}
}
