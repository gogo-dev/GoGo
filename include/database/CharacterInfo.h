#pragma once
#include <boost/cstdint.hpp>
#include <util/SmallVector.h>

#include <vector>
#include <string>

#include "Item.h"

struct CharacterInfo
{
    boost::uint32_t id;
	std::string name;
	std::string clanName;
	boost::uint32_t grade;
    boost::uint16_t clanScore;
    boost::uint8_t marker;
    boost::uint8_t level;
    boost::uint8_t gender;
    boost::uint8_t hairstyle;
    boost::uint8_t facestyle;
    boost::uint32_t experience;
    boost::uint32_t bounty;
	SmallVector<Item, 12> equipment;
	boost::uint32_t access;
    boost::uint32_t clanid;
    std::vector<Item> inventory;
};
