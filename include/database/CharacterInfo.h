#pragma once
#include <boost/cstdint.hpp>
#include <util/SmallVector.h>

#include <vector>
#include <string>

#include "Item.h"

struct CharacterInfo
{
    boost::uint32_t CharacterId;
	std::string CharacterName; //32 = size
	std::string ClanName; //16 = size
	boost::uint32_t CharacterGrade;
    boost::uint16_t ClanPoints;
    boost::uint8_t CharacterMarker;
    boost::uint16_t CharacterLevel;
    boost::uint8_t CharacterSex;
    boost::uint8_t CharacterHair;
    boost::uint8_t CharacterFace;
    boost::uint32_t CharacterXP;
    boost::uint32_t CharacterBP;
	SmallVector<Item, 12> Equipment;
	boost::uint32_t CharacterAccess;
    boost::uint32_t ClanId;
    std::vector<Item> Inventory;
};
