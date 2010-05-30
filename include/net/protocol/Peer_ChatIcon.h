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

// ChatIcon
class Peer_ChatIcon : public Packet
{
private:
	packet::boolean bStart;

public:
	enum { packetID = 10053 };

	Peer_ChatIcon(packet::boolean bStart);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}