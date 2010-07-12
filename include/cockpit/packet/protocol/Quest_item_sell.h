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

// Request sell quest item
class Quest_item_sell : public Packet
{
private:
	packet::MUID uidChar;
	packet::int32 QuestItemID;
	packet::int32 Count;

public:
	enum { packetID = 21004 };

	Quest_item_sell(const packet::MUID& uidChar, const packet::int32& QuestItemID, const packet::int32& Count);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_item_sell()
	{
	}

};

}
}
}
