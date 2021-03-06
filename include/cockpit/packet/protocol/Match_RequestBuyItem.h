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

// Request Buy Item
class Match_RequestBuyItem : public Packet
{
private:
	packet::MUID uidChar;
	packet::uint32 ItemID;

public:
	enum { packetID = 1811 };

	Match_RequestBuyItem(const packet::MUID& uidChar, const packet::uint32& ItemID);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_RequestBuyItem()
	{
	}

};

}
}
}
