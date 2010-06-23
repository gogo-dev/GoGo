#pragma once
#include <string>

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#include "AccountInfo.h"
#include "CharacterInfo.h"
#include "CharacterEntry.h"

class GunzDB : boost::noncopyable
{
public:
	// Gets the account info from a username and password, throwing
	// InvalidAccountInfo if the information is invalid.
	virtual AccountInfo GetAccountInfo(const std::string& user,
	                                   const std::string& password) = 0;
	
	// Gets the character info from an account ID
	virtual std::vector<CharacterEntry> GetCharacterList (boost::uint32_t aid) = 0;

	// Creates a character from an account ID, character marker, sex, hair, face, and costume
	virtual bool CreateCharacter(boost::uint32_t aid, std::string name, boost::uint32_t marker, boost::uint32_t sex, boost::uint32_t hair, boost::uint32_t face, boost::uint32_t costume) = 0;
	
	// Deletes a character from an account ID, marker, and name.
	virtual bool DeleteCharacter(boost::uint32_t aid, boost::uint32_t marker, std::string name) = 0;

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
