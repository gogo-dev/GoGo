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

// Leave Stage
class Stage_Leave : public Packet
{
private:
	packet::MUID uidPlayer;

public:
	enum { packetID = 1307 };

	Stage_Leave(packet::MUID uidPlayer);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Stage_Leave()
	{
	}

};

}
}
}