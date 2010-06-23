#pragma once
#include <cockpit/Logger.h>
#include "GunzDB.h"
#include <typeinfo>	// Fixes a bug in mysql on clang++.
#include <mystring.h> // yet another bug in mysql + clang++.
#include <mysql++.h>
#include <boost/thread/mutex.hpp> // don't we love mutexs?

class MySQLGunzDB : public GunzDB
{
private:
	mysqlpp::Connection gunzconn;
	cockpit::Logger* logger;
	boost::mutex gunzMutex;
private:
	static std::vector<Item> GetItemsFromRow(const mysqlpp::Row& row);
	boost::uint32_t GetCID (boost::uint32_t aid, boost::uint32_t marker);

public:
	MySQLGunzDB(cockpit::Logger* _logger, const char* dbname, const char* host, const char* user, const char* password, unsigned int port = 3306);
	~MySQLGunzDB();

	//Login Process related function
	AccountInfo GetAccountInfo(const std::string& user, const std::string& password);

	//Character process related function
	std::vector<Item> GetEquipment (boost::uint32_t cid);
	std::vector<Item> GetInventory (boost::uint32_t cid);
	std::vector<CharacterEntry> GetCharacterList(boost::uint32_t aid);
	bool DoesNameExist(std::string name);
	bool CreateCharacter(boost::uint32_t aid, std::string name, boost::uint32_t marker, boost::uint32_t sex, boost::uint32_t hair, boost::uint32_t face, boost::uint32_t costume);
	CharacterInfo GetCharacterInfo(boost::uint32_t cid, boost::uint8_t slot);
};
