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

// Request Equip Item
class MatchRequestEquipItem : public Packet
{
private:
	packet::MUID uidChar;
	packet::MUID uidItem;
	packet::uint32 EquipmentSlot;

public:
	enum { packetID = 1823 };

	MatchRequestEquipItem(const packet::MUID& uidChar, const packet::MUID& uidItem, const packet::uint32& EquipmentSlot);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~MatchRequestEquipItem()
	{
	}

};

}
}
}
