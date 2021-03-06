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

// give oneself up
class MC_REQUEST_GIVE_ONESELF_UP : public Packet
{

public:
	enum { packetID = 9101 };

	MC_REQUEST_GIVE_ONESELF_UP();

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~MC_REQUEST_GIVE_ONESELF_UP()
	{
	}

};

}
}
}
