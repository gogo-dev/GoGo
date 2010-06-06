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

// Request Spawn WorldItem
class Match_Request_Spawn_WorldItem_UID : public Packet
{
private:
	packet::int32 nWorldItemUID;

public:
	enum { packetID = 1545 };

	Match_Request_Spawn_WorldItem_UID(packet::int32 nWorldItemUID);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_Request_Spawn_WorldItem_UID()
	{
	}

};

}
}
}