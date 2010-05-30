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

// Tunneling UDP
class Agent_TunnelingUDP : public Packet
{
private:
	packet::MUID SendUID;
	packet::MUID RecvUID;
	packet::blob Data;

public:
	enum { packetID = 5082 };

	Agent_TunnelingUDP(packet::MUID SendUID, packet::MUID RecvUID, packet::blob Data);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}