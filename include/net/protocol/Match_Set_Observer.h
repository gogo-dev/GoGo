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

// Set Observer
class Match_Set_Observer : public Packet
{
private:
	packet::MUID uidChar;

public:
	enum { packetID = 1553 };

	Match_Set_Observer(packet::MUID uidChar);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}