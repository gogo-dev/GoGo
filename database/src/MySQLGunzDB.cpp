#include <database/oopsies.h>
#include <database/MySQLGunzDB.h>
#include <exception>

using namespace std;
using namespace boost;
using namespace cockpit;

MySQLGunzDB::MySQLGunzDB(Logger* log, const char* dbname, const char* host, const char* user, const char* password, unsigned int port)
	: logger(log)
{
	if (!gunzconn.connect(dbname, host, user, password, port))
		throw std::runtime_error((format("Error connecting to the database: %1%") % gunzconn.error()).str().c_str());

	logger->info("Successfully connected to database.");
}

MySQLGunzDB::~MySQLGunzDB()
{
}

AccountInfo MySQLGunzDB::GetAccountInfo(const std::string& user, const std::string& password)
{
	AccountInfo accountInfo;

	try
	{
		mysqlpp::Query query = gunzconn.query();

		query << "SELECT aid, ugradeid, pgradeid FROM account "
		         "WHERE username=" << mysqlpp::quote << user.c_str() <<
		         " AND password=md5(" << mysqlpp::quote << password.c_str() << ")"
		         " LIMIT 1";

		mysqlpp::Row row = query.use().fetch_row();

		if (!row)
			throw InvalidAccountInfo();

		accountInfo.AccountId = row["aid"];
		accountInfo.AccountAccess = row["ugradeid"];
		accountInfo.AccountPremium = row["ugradeid"];
		accountInfo.AccountName = user;

		if (accountInfo.AccountAccess == 253 || accountInfo.AccountAccess == 105)
			throw BannedUser (user);

		return accountInfo;

	} catch(mysqlpp::Exception& ex)	{
		logger->warning(format("MySQL Error: %1%") % ex.what());
		throw InvalidAccountInfo();
	}
}

vector<Item> MySQLGunzDB::GetItemsFromRow(const mysqlpp::Row& row)
{
	Item temp;
	vector<Item> ret;

	for(size_t i = 1; i < row.size(); ++i)
	{
		temp.ItemCID = row[i];
		ret.push_back(temp);
	}

	return ret;
}

std::vector<Item> MySQLGunzDB::GetEquipment(boost::uint32_t cid)
{
	std::vector<Item> items;

	mysqlpp::Query query = gunzconn.query();
	query << "SELECT * from character_equip where charid=" << cid;

	mysqlpp::Row row = query.use().fetch_row();

	if(!row)
		throw InvalidCID();

	return GetItemsFromRow(row);
}

vector<Item> MySQLGunzDB::GetInventory(uint32_t cid)
{
	std::vector<Item> items;
	mysqlpp::Query query = gunzconn.query();
	query << "SELECT * FROM character_inventory where charid=" << cid;

	mysqlpp::UseQueryResult res = query.use();
	mysqlpp::Row row;

	while(row = res.fetch_row())
	{
		Item item;
		item.ItemCID = row["id"];
		item.ItemID = row["itemid"];
		bool rental = row["rental"];

		if(rental)
		{
			//TODO: Add the time shit.
		}

		items.push_back(item);
	}

	return items;
}

std::vector<CharacterEntry> MySQLGunzDB::GetCharacterList (boost::uint32_t aid)
{
	std::vector<CharacterEntry> charList;
	try
	{
		mysqlpp::Query query = gunzconn.query();
		query << "SELECT name,level,marker FROM `character` where accountid=" << aid << " ORDER BY marker ASC";
		mysqlpp::Row row;

		while (row = query.use().fetch_row())
		{
			CharacterEntry character;
			character.CharacterIndex = row["marker"];
			character.CharacterLevel = row["level"];
			character.CharacterName  = std::string(row["name"]);

			charList.push_back(character);
		}

	} catch(mysqlpp::Exception& ex) {
		logger->warning(format("MySQL Error: %1%") % ex.what());
	}

	return charList;
}
CharacterInfo MySQLGunzDB::GetCharacterInfo(boost::uint32_t cid, boost::uint8_t slot)
{
	CharacterInfo charInfo;

	try
	{
		mysqlpp::Query query = gunzconn.query();
		query << "SELECT * FROM `character` WHERE id=" << cid << " AND marker=" << slot <<" LIMIT 1";
		mysqlpp::Row row = query.use().fetch_row();

		if(!row)
			throw InvalidCharacterInfo();

		charInfo.CharacterId = cid;
		charInfo.CharacterMarker = slot;
		charInfo.CharacterName = std::string(row["name"]);
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

			if(row)
			{
				charInfo.ClanName = std::string(row["name"]);
				charInfo.ClanPoints = row["cwpoints"];
			}

			query.reset();
		}

		charInfo.Equipment = GetEquipment(cid);
		charInfo.Inventory = GetInventory(cid);

		return charInfo;

	} catch(mysqlpp::Exception& ex) {
		logger->warning(format("MySQL Error: %1%") % ex.what());
		throw InvalidCharacterInfo();
	}
}
