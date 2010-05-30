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

// Chat to Stage
class Stage_Chat : public Packet
{
private:
	packet::MUID uidPlayer;
	packet::MUID uidStage;
	packet::string Chat;

public:
	enum { packetID = 1321 };

	Stage_Chat(packet::MUID uidPlayer, packet::MUID uidStage, packet::string Chat);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}