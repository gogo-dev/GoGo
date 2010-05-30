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

// Response Account Character List
class Match_ResponseAccountCharList : public Packet
{
private:
	packet::blob CharList;

public:
	enum { packetID = 1702 };

	Match_ResponseAccountCharList(packet::blob CharList);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}