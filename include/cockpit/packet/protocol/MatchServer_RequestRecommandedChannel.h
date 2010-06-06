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

// Request recommanded channel
class MatchServer_RequestRecommandedChannel : public Packet
{

public:
	enum { packetID = 1201 };

	MatchServer_RequestRecommandedChannel();

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~MatchServer_RequestRecommandedChannel()
	{
	}

};

}
}
}