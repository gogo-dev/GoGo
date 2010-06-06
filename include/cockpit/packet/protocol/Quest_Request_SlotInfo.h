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

// Request slot info
class Quest_Request_SlotInfo : public Packet
{
private:
	packet::MUID Sender;

public:
	enum { packetID = 21011 };

	Quest_Request_SlotInfo(packet::MUID Sender);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Request_SlotInfo()
	{
	}

};

}
}
}