#pragma once
#include <string>

#include <boost/noncopyable.hpp>

#include "AccountInfo.h"
#include "CharacterInfo.h"

class GunzDB : boost::noncopyable
{
public:
	// Gets the account info from a username and password, throwing
	// InvalidAccountInfo if the information is invalid.
	virtual AccountInfo GetAccountInfo(const std::string& user,
	                                   const std::string& password) = 0;

	// Gets the character info from a character ID and slot in the character
	// select screen, throwing InvalidCharacterInfo if any information is
	// invalid.
	virtual CharacterInfo GetCharacterInfo(boost::uint32_t cid, boost::uint8_t slot) = 0;

	// Gets all the equipment currently equipped on the character specified
	// by "cid", throwing InvalidCID if necessary.
	virtual std::vector<Item> GetEquipment(boost::uint32_t cid) = 0;
	virtual std::vector<Item> GetInventory(boost::uint32_t cid) = 0;

	virtual ~GunzDB()
	{
	}
};
