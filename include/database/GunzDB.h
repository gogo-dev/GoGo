#pragma once
#include <string>
#include "AccountInfo.h"
#include "CharacterInfo.h"

class GunzDB
{
	public:
		AccountInfo GetAccountInfo(const std::string& user, const std::string& password);
		CharacterInfo GetCharacterInfo(boost::uint32_t cid, boost::uint8_t marker);
		std::vector<Item> GetEquipment (boost::uint32_t cid);
		std::list<Item> GetInventory (boost::uint32_t cid);
};
