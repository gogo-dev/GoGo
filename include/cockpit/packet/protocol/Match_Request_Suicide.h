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

// Request Suicide
class Match_Request_Suicide : public Packet
{
private:
	packet::MUID uidChar;

public:
	enum { packetID = 1531 };

	Match_Request_Suicide(packet::MUID uidChar);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Request_Suicide()
	{
	}

};

}
}
}