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

// Moveto Portal
class Quest_Moveto_Portal : public Packet
{
private:
	packet::vector SectorIndex;
	packet::uint8 RepeatIndex;
	packet::MUID uidPlayer;

public:
	enum { packetID = 6058 };

	Quest_Moveto_Portal(packet::vector SectorIndex, packet::uint8 RepeatIndex, packet::MUID uidPlayer);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}