#pragma once
#include <string>

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#include <util/SmallVector.h>

#include "AccountInfo.h"
#include "CharacterInfo.h"
#include "CharacterEntry.h"

/**
	This is the only interface to the database that each client will have.
	Any actions that need to be persistent between GoGo invocations should
	probably be handled inside this class.
*/
class GunzDB : boost::noncopyable
{
public:
	/**
		Gets the account info from a username and password, throwing
		InvalidAccountInfo if the information is invalid.

		@param  user      The account's username.
		@param  password  The account's password.

		@return The fully enumerated account info.

		@throws InvalidAccountInfo If the login information cannot be processed.
		@throws BannedUser         If the account has been banned.
	*/
	virtual AccountInfo GetAccountInfo(const std::string& user,
	                                   const std::string& password) = 0;

	/**
		Deletes a character from the database. FOREVAR!

		@param  aid    The account ID of the owning player.
		@param  marker Where in the character list (0-3) the character to be deleted is.
	*/
	virtual void DeleteCharacter(boost::uint32_t aid, boost::uint32_t marker) = 0;

	/**
		Gets the character info from an account identifier.

		@param  aid The account identifier to get the character list for. This
		            can be found inside AccountInfo.

		@return Information about each and every character the account owns.
		        This can be anywhere from 0-4 items.
	*/
	virtual SmallVector<CharacterEntry, 4> GetCharacterList(boost::uint32_t aid) = 0;

	/**
		Creates a character.

		@param  aid      The account ID of the parent player we will create the
		                 character for.
		@param  name     The name of the new character.
		@param  marker   TODO: USELESS. REMOVE THIS.
		@param  sex      The gender of the character we will create.
		@param  hair     The hair style of the character. Generally between 1 and 4 (inclusive).
		@param  face     The face style of the character. Generally between 1 and 4 (inclusive).
		@param  constume The default inventory layout for the character. Again, a number
		                 between 1 and 4 (inclusive).

		@throws NameInUse            If the character name has already been taken.
		@throws InvalidCharacterName If the character name isn't valid.
	*/
	virtual void CreateCharacter(
		boost::uint32_t aid,
		std::string name,
		boost::uint32_t marker,
		boost::uint32_t sex,
		boost::uint32_t hair,
		boost::uint32_t face,
		boost::uint32_t costume
	) = 0;

	/**
		Gets the associated info for a character represented by the ID.

		@param  aid    The ID for the account we'll look for the character info in.
		@param  marker The position (0-3) of the character in the character list.

		@return The character's full info.

		@throws InvalidCharacterInfo If there's no such AID, the marker is bad, etc.
	*/
	virtual CharacterInfo GetCharacterInfo(boost::uint32_t aid, boost::uint8_t marker) = 0;

	/**
		Gets all the equipment currently equipped on the character specified by
		a character ID.

		@param  cid  The character's unique identification number. This can be
		             retrieved from the CharacterInfo struct.

		@return All items currently equipped onto the character.

		@throws InvalidCID When the CID is invalid, of course!
	*/
	virtual SmallVector<Item, 12> GetEquipment(boost::uint32_t cid) = 0;

	/**
		Gets the full inventory for the character represented by the ID.

		@param  cid The character's unique identification number retrieved from
		            the CharacterInfo struct.

		@return The contents of the character's inventory.

		@throws InvalidCID When the CID is invalid, of course!
	*/
	virtual std::vector<Item> GetInventory(boost::uint32_t cid) = 0;

	virtual ~GunzDB()
	{
	}
};
