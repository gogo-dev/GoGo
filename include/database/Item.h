#pragma once
#include <boost/cstdint.hpp>

struct Item
{
    boost::uint32_t cid;
    boost::uint32_t itemid;
    boost::uint32_t rentHour;
    boost::uint32_t price;
    boost::uint8_t  gender;
    boost::uint8_t  minLevel;
    boost::uint32_t weight;
    boost::uint32_t maxWeightChange;	// How much item modifies the user's max weight by.

	Item() { rentHour = 0x20050800; }
};
