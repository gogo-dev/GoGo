#pragma once
#include <boost/cstdint.hpp>

struct Item
{
    boost::uint32_t ItemCID;
    boost::uint32_t ItemID;
    boost::uint32_t RentHour;
    boost::uint32_t Price;
    boost::uint8_t  Sex;
    boost::uint8_t  Level;
    boost::uint32_t Weight;
    boost::uint32_t MaxWT;

	Item() { RentHour = 0x20050800; }
};
