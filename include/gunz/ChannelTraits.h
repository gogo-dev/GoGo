#pragma once
#include <gunz/simple_types.h>

#include <string>

#include <boost/cstdint.hpp>

namespace gunz {

struct ChannelTraits
{
	MUID uid;
	std::string name;
	boost::uint32_t maxPlayers;
	boost::uint32_t playerCount;
	ChannelRule rule;
	ChannelType type;
	boost::uint8_t minLevel;
	boost::uint8_t maxLevel;

	ChannelTraits();
	ChannelTraits(const ChannelTraits& other);

	// Doesn't do anything fancy, it only exists for convenience.
	ChannelTraits(MUID uid,
				  const std::string& name,
				  boost::uint32_t maxPlayers,
				  ChannelRule rule,
				  ChannelType type,
				  boost::uint8_t minLevel,
				  boost::uint8_t maxLevel);

	ChannelTraits& operator=(ChannelTraits other);

	bool operator<(const ChannelTraits& other) const;
	bool operator==(const ChannelTraits& other) const;

	~ChannelTraits();
};

}
