#pragma once
#include <boost/cstdint.hpp>
#include <util/buffer.h>

namespace cockpit {
namespace packet {

class Packet
{
	using boost::uint16_t;
public:
	virtual const char* name() const = 0;
	virtual const char* docstring() const = 0;
	virtual uint16_t id() const = 0;
	virtual Buffer serialize() const = 0;

	virtual ~Packet()
	{
	}
};

}
}