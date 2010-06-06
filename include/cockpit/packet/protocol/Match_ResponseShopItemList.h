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

// Response Shop Item List
class Match_ResponseShopItemList : public Packet
{
private:
	packet::blob GambleItemList;
	packet::blob ItemList;

public:
	enum { packetID = 1816 };

	Match_ResponseShopItemList(packet::blob GambleItemList, packet::blob ItemList);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Match_ResponseShopItemList()
	{
	}

};

}
}
}