#pragma once
#include <boost/cstdint.hpp>
#include <string>

struct CharacterEntry
{
	std::string name;
	boost::uint8_t index;
	boost::uint8_t level;
};
