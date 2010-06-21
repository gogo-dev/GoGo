#pragma once
#include <boost/cstdint.hpp>
#include <util/buffer.h>

namespace cockpit {
namespace packet {

/**
	The base class of all sendable gunz packets.
*/
class Packet
{
public:
	/**
		@return The name of the packet.
	*/
	virtual const char* name() const = 0;

	/**
		@return MAIET's help string for the packet.
	*/
	virtual const char* doc() const = 0;

	/**
		@return The command ID that the packet responds to.
	*/
	virtual boost::uint16_t id() const = 0;

	/**
		@return The serialized packet parameters.
	*/
	virtual Buffer serialize() const = 0;

	virtual ~Packet()
	{
	}
};

}
}
