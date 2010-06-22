#pragma once
#include <boost/cstdint.hpp>
#include <stdexcept>

namespace cockpit {
namespace packet {

struct PacketInfo
{
	const char* name;
	const char* doc;
	boost::uint16_t commandId;

	PacketInfo(const char* name, const char* doc, boost::uint16_t commandId);
	~PacketInfo();
};

struct BadCommandId : public std::runtime_error
{
	boost::uint16_t commandId;

	BadCommandId(boost::uint16_t commandId);
	~BadCommandId();
};

/**
 * Looks up a packet, and returns the associated info for it. If the commandID
 * is invalid, BadCommandId is thrown.
 */
PacketInfo lookup(boost::uint16_t commandId);

}
}
