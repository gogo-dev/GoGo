#pragma once
#include <util/ConsoleLogger.h>
#include "GunzDB.h"
#include <typeinfo>	// Fixes a bug in mysql on clang++.
#include <mysql++.h>

class MySQLGunzDB : public GunzDB
{
private:
	mysqlpp::Connection gunzconn;
	Logger* logger;

private:
	static std::vector<Item> GetItemsFromRow(const mysqlpp::Row& row);

public:
	MySQLGunzDB(Logger* _logger, const char* dbname, const char* host, const char* user, const char* password, unsigned int port = 3306);
	~MySQLGunzDB();

	//Login Process related function
	AccountInfo GetAccountInfo(const std::string& user, const std::string& password);

	//Character process related function
	std::vector<Item> GetEquipment (boost::uint32_t cid);
	std::vector<Item> GetInventory (boost::uint32_t cid);
	CharacterInfo GetCharacterInfo(boost::uint32_t cid, boost::uint8_t slot);
};
