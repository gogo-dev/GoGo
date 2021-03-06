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

// Change Password on Stage
class Event_ChangePassword : public Packet
{
private:
	packet::string strPassword;

public:
	enum { packetID = 602 };

	Event_ChangePassword(const packet::string& strPassword);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;

	~Event_ChangePassword()
	{
	}

};

}
}
}
