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

// Response Account Character Info
class Match_ResponseAccountCharInfo : public Packet
{
private:
	packet::int8 CharNum;
	packet::blob CharInfo;

public:
	enum { packetID = 1720 };

	Match_ResponseAccountCharInfo(packet::int8 CharNum, packet::blob CharInfo);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_ResponseAccountCharInfo()
	{
	}

};

}
}
}
