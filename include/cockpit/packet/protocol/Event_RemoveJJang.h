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

// Remove JJang mark from a Player
class Event_RemoveJJang : public Packet
{
private:
	packet::string strTargetName;

public:
	enum { packetID = 612 };

	Event_RemoveJJang(packet::string strTargetName);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Event_RemoveJJang()
	{
	}

};

}
}
}