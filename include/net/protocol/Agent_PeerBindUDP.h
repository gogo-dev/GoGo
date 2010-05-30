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

// Bind Client to Peer by UDP
class Agent_PeerBindUDP : public Packet
{
private:
	packet::MUID CharUID;
	packet::string strLocalIP;
	packet::uint32 nLocalPort;
	packet::string strIP;
	packet::uint32 nPort;

public:
	enum { packetID = 5072 };

	Agent_PeerBindUDP(packet::MUID CharUID, packet::string strLocalIP, packet::uint32 nLocalPort, packet::string strIP, packet::uint32 nPort);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}