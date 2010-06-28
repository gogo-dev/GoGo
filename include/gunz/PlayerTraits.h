#pragma once
#include <string>

#include <boost/cstdint.hpp>

#include <gunz/simple_types.h>

namespace gunz {

struct PlayerTraits
{
	enum PlayerLocation
	{
		PL_OUTSIDE,
		PL_LOBBY,
		PL_STAGE,
		PL_BATTLE
	};

	MUID muid;
	std::string name;
	std::string clanName;
	boost::uint8_t level;
	PlayerLocation location;
	boost::uint8_t ugradeid;
	boost::int32_t clanid;

	PlayerTraits();

	PlayerTraits(
		MUID muid,
		const std::string& name,
		const std::string& clanName,
		boost::uint8_t level,
		PlayerLocation location,
		boost::uint8_t ugradeid,
		boost::int32_t clanid
	);

	~PlayerTraits();
};

}
