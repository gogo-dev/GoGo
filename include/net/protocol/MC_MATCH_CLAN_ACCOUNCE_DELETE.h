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

// delete clan info announce to clan member
class MC_MATCH_CLAN_ACCOUNCE_DELETE : public Packet
{
private:
	packet::string deleteinfo;

public:
	enum { packetID = 2056 };

	MC_MATCH_CLAN_ACCOUNCE_DELETE(packet::string deleteinfo);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}