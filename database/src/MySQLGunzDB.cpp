#include <database/MySQLGunzDB.h>

using namespace std;

MySQLGunzDB::MySQLGunzDB(Logger* log, const char* dbname, const char* host, const char* user, const char* password, unsigned int port)
	: logger(log)
{
	if (!gunzconn.connect(dbname, host, user, password, port))
	{
		logger->error(boost::format("Unable to connect to database: %1%") % gunzconn.error());
		throw("Error connect to database.");
		return;
	}
	
	logger->info("Successfully connected to database.");
}

MySQLGunzDB::~MySQLGunzDB()
{
}

AccountInfo MySQLGunzDB::GetAccountInfo (const std::string& user, const std::string& password)
{
	AccountInfo accountInfo;

	try
	{
		mysqlpp::Query query = gunzconn.query();
		query << "SELECT aid,ugradeid,pgradeid FROM account WHERE username=" << mysqlpp::quote << user.c_str() << " AND password=md5(" << mysqlpp::quote << password.c_str() << ") LIMIT 1";
		mysqlpp::Row row = query.use().fetch_row();

		if (!row)
		{
			accountInfo.AccountId = -1;
			return accountInfo;
		}
		
		accountInfo.AccountId = row["aid"];
		accountInfo.AccountAccess = row["ugradeid"];
		accountInfo.AccountPremium = row["ugradeid"];
		accountInfo.AccountName = user;
		
		logger->info(boost::format("Account Id: %1%. Access: %2%. Premium: %3%. Name: %4%.") % accountInfo.AccountId % (boost::uint32_t)accountInfo.AccountAccess % (boost::uint32_t)accountInfo.AccountPremium % accountInfo.AccountName);
		return accountInfo;
	}
	catch (mysqlpp::Exception& ex)
	{
		logger->error (boost::format("Error getting account information: %1%") % ex.what());
	}

	accountInfo.AccountId = -1;
	return accountInfo;
}

std::vector<Item> MySQLGunzDB::GetEquipment (boost::uint32_t cid)
{
	std::vector<Item> items;
	mysqlpp::Query query = gunzconn.query();
	query << "SELECT * from character_equip where charid=" << cid;
	mysqlpp::Row row = query.use().fetch_row();

	if (row)
	{
		for (boost::uint32_t i = 1; i < row.size(); ++i)
		{
			Item item;
			item.ItemCID = row[i];
			items.push_back (item);
		}
	}
	
	return items;
}

std::list<Item> MySQLGunzDB::GetInventory (boost::uint32_t cid)
{
	std::list<Item> items;
	mysqlpp::Query query = gunzconn.query();
	query << "SELECT * FROM character_inventory where charid=" << cid;
	
	mysqlpp::UseQueryResult res = query.use();
	mysqlpp::Row row;

	while (row = res.fetch_row())
	{
		Item item;
		item.ItemCID = row["id"];
		item.ItemID = row["itemid"];
		bool rental = row["rental"];

		if (rental)
		{
			//TODO: Add the time shit.
		}
		items.push_back(item);
	}

	return items;
}

CharacterInfo MySQLGunzDB::GetCharacterInfo (boost::uint32_t cid, boost::uint8_t marker)
{
	CharacterInfo charInfo;

	try
	{
		mysqlpp::Query query = gunzconn.query();
		query << "SELECT * FROM character WHERE id=" << cid << " AND marker=" << marker <<" LIMIT 1";
		mysqlpp::Row row = query.use().fetch_row();

		if (!row)
		{
			charInfo.CharacterId = -1;
			return charInfo;
		}

		charInfo.CharacterId = cid;
		charInfo.CharacterMarker = marker;
		charInfo.CharacterName = row["name"];
		charInfo.ClanId = row["clanid"];
		charInfo.CharacterLevel = row["level"];
		charInfo.CharacterSex = row["sex"];
		charInfo.CharacterHair = row["hair"];
		charInfo.CharacterFace = row["face"];
		charInfo.CharacterXP = row["xp"];
		charInfo.CharacterBP = row["bp"];
		
		query.reset();

		if (charInfo.ClanId > 0)
		{
			query << "SELECT * FROM clan WHERE cid=" << cid;
			row = query.use().fetch_row();

			if (row)
			{
				charInfo.ClanName = row["name"];
				charInfo.ClanPoints = row["cwpoints"];
			}

			query.reset();
		}

		charInfo.Equipment = GetEquipment (cid);
		charInfo.Inventory = GetInventory (cid);
	}
	catch (mysqlpp::Exception& ex)
	{
		logger->error (boost::format("Error getting character information: %1%") % ex.what());
	}

	charInfo.CharacterId = -1;
	return charInfo;
}
