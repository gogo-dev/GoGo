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

// reload gamble item info
class MC_ADMIN_RELOAD_GAMBLEITEM : public Packet
{

public:
	enum { packetID = 534 };

	MC_ADMIN_RELOAD_GAMBLEITEM();

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~MC_ADMIN_RELOAD_GAMBLEITEM()
	{
	}

};

}
}
}