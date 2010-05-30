/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <net/packet.h>
#include <boost/cstdint.hpp>
#include <net/PacketParameters.h>

namespace packet {
namespace protocol {

// Request Switch LadderGame
class Admin_RequestSwitchLadderGame : public Packet
{
private:
	packet::MUID uidAdmin;
	packet::boolean IsEnabled;

public:
	enum { packetID = 522 };

	Admin_RequestSwitchLadderGame(packet::MUID uidAdmin, packet::boolean IsEnabled);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}