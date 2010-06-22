#pragma once
#include <cockpit/Logger.h>
#include "GunzDB.h"
#include <typeinfo>	// Fixes a bug in mysql on clang++.
#include <mystring.h> // yet another bug in mysql + clang++.
#include <mysql++.h>

class MySQLGunzDB : public GunzDB
{
private:
	mysqlpp::Connection gunzconn;
	cockpit::Logger* logger;

private:
	static std::vector<Item> GetItemsFromRow(const mysqlpp::Row& row);

public:
	MySQLGunzDB(cockpit::Logger* _logger, const char* dbname, const char* host, const char* user, const char* password, unsigned int port = 3306);
	~MySQLGunzDB();

	//Login Process related function
	AccountInfo GetAccountInfo(const std::string& user, const std::string& password);

	//Character process related function
	std::vector<Item> GetEquipment (boost::uint32_t cid);
	std::vector<Item> GetInventory (boost::uint32_t cid);
	std::vector<CharacterEntry> GetCharacterList(boost::uint32_t aid);
	CharacterInfo GetCharacterInfo(boost::uint32_t cid, boost::uint8_t slot);
};
