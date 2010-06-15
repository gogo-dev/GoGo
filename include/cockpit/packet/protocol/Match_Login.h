/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <boost/cstdint.hpp>
#include <cockpit/packet/Packet.h>
#include <cockpit/packet/Parameters.h>

namespace cockpit {
namespace packet {
namespace protocol {

// Login Match Server
class Match_Login : public Packet
{
private:
	packet::string UserID;
	packet::string Password;
	packet::int32 CommandVersion;
	packet::uint32 nChecksumPack;

public:
	enum { packetID = 994 };

	Match_Login(packet::string UserID, packet::string Password, packet::int32 CommandVersion, packet::uint32 nChecksumPack);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Login()
	{
	}

};

}
}
}
