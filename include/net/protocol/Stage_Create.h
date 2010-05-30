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

// Create a Stage
class Stage_Create : public Packet
{
private:
	packet::MUID uidChar;
	packet::string StageName;
	packet::boolean IsPrivate;
	packet::string Password;

public:
	enum { packetID = 1301 };

	Stage_Create(packet::MUID uidChar, packet::string StageName, packet::boolean IsPrivate, packet::string Password);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}