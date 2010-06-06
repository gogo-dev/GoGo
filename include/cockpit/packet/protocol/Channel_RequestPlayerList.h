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

// Request Channel Player List
class Channel_RequestPlayerList : public Packet
{
private:
	packet::MUID uidPlayer;
	packet::MUID uidChannel;
	packet::int32 PlayerListPage;

public:
	enum { packetID = 1221 };

	Channel_RequestPlayerList(packet::MUID uidPlayer, packet::MUID uidChannel, packet::int32 PlayerListPage);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Channel_RequestPlayerList()
	{
	}

};

}
}
}