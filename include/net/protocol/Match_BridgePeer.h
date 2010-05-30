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

// Match BridgePeer
class Match_BridgePeer : public Packet
{
private:
	packet::MUID uidPlayer;
	packet::uint32 dwIP;
	packet::uint32 nPort;

public:
	enum { packetID = 1006 };

	Match_BridgePeer(packet::MUID uidPlayer, packet::uint32 dwIP, packet::uint32 nPort);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}