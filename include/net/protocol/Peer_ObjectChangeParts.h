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

// Change Object Parts
class Peer_ObjectChangeParts : public Packet
{
private:
	packet::int32 PartsType;
	packet::int32 PartsID;

public:
	enum { packetID = 10023 };

	Peer_ObjectChangeParts(packet::int32 PartsType, packet::int32 PartsID);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}