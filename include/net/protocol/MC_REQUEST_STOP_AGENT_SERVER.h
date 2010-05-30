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

// request stop agent
class MC_REQUEST_STOP_AGENT_SERVER : public Packet
{

public:
	enum { packetID = 33034 };

	MC_REQUEST_STOP_AGENT_SERVER();

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}