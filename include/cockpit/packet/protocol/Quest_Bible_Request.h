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

// request monster bible info
class Quest_Bible_Request : public Packet
{
private:
	packet::MUID requester;

public:
	enum { packetID = 21014 };

	Quest_Bible_Request(const packet::MUID& requester);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Quest_Bible_Request()
	{
	}

};

}
}
}
