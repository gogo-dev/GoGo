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

// Send survival private ranking
class Quest_Survuval_PrivateRanking : public Packet
{
private:
	packet::uint32 Rank;
	packet::uint32 Point;

public:
	enum { packetID = 6105 };

	Quest_Survuval_PrivateRanking(packet::uint32 Rank, packet::uint32 Point);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Survuval_PrivateRanking()
	{
	}

};

}
}
}