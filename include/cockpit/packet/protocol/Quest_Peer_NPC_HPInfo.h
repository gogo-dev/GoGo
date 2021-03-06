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

// NPC HPInfo
class Quest_Peer_NPC_HPInfo : public Packet
{
private:
	packet::int32 nNPCCount;
	packet::blob HPTable;

public:
	enum { packetID = 6041 };

	Quest_Peer_NPC_HPInfo(const packet::int32& nNPCCount, const packet::blob& HPTable);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Peer_NPC_HPInfo()
	{
	}

};

}
}
}
