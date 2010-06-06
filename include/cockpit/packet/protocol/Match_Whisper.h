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

// Whisper Message to a User
class Match_Whisper : public Packet
{
private:
	packet::string SenderName;
	packet::string TargetName;
	packet::string Message;

public:
	enum { packetID = 1601 };

	Match_Whisper(packet::string SenderName, packet::string TargetName, packet::string Message);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Whisper()
	{
	}

};

}
}
}