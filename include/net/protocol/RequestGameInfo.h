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

// Request Game Info
class RequestGameInfo : public Packet
{
private:
	packet::MUID uidChar;
	packet::MUID uidStage;

public:
	enum { packetID = 1451 };

	RequestGameInfo(packet::MUID uidChar, packet::MUID uidStage);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}