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

// Select ChatRoom to Write
class ChatRoom_SelectWrite : public Packet
{
private:
	packet::string ChatRoomName;

public:
	enum { packetID = 1665 };

	ChatRoom_SelectWrite(packet::string ChatRoomName);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~ChatRoom_SelectWrite()
	{
	}

};

}
}
}