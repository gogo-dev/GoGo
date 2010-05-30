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

// request server hearbeat check
class MC_REQUEST_SERVER_HEARBEAT : public Packet
{

public:
	enum { packetID = 31009 };

	MC_REQUEST_SERVER_HEARBEAT();

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}