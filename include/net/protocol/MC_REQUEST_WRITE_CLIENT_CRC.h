/*
 * NOTICE: Do not manually edit this file. It has been autogenerated by
 * protocol/parse.py. Any changes should me made there, instead of here.
 */
#pragma once
#include <net/packet.h>
#include <boost/cstdint.hpp>
#include <net/PacketParameters.h>

namespace packet {
namespace protocol {

// request gunz client file crc32 checksum write on server.ini.
class MC_REQUEST_WRITE_CLIENT_CRC : public Packet
{
private:
	packet::uint32 gunzclientfilecrc32checksum;

public:
	enum { packetID = 31029 };

	MC_REQUEST_WRITE_CLIENT_CRC(packet::uint32 gunzclientfilecrc32checksum);

	const char* name() const;
	const char* doc() const;
	boost::uint16_t id() const;
	Buffer serialize() const;
};

}
}