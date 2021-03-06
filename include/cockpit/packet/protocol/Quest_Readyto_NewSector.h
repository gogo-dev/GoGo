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

// Ready To New Sector
class Quest_Readyto_NewSector : public Packet
{
private:
	packet::MUID uidPlayer;

public:
	enum { packetID = 6059 };

	Quest_Readyto_NewSector(const packet::MUID& uidPlayer);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Readyto_NewSector()
	{
	}

};

}
}
}
