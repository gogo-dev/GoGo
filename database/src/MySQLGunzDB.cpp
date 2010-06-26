#include <database/oopsies.h>
#include <database/MySQLGunzDB.h>

#include <exception>

#include <cstddef>

#include <boost/function.hpp>
#include <boost/bind/bind.hpp>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace mysqlpp;

typedef mysqlpp::StoreQueryResult::const_iterator ResultIt;

MySQLGunzDB::MySQLGunzDB(Logger* log, const char* dbname, const char* host, const char* user, const char* password, uint16_t port)
	: connectionPool(dbname, host, user, password, port), logger(log)
{
	logger->debug("Testing database connection...");
	Connection c(dbname, host, user, password, port);
	logger->debug("Connected!");
}

MySQLGunzDB::~MySQLGunzDB()
{
}

bool MySQLGunzDB::exec_query(function<Query (Connection&)> QueryMaker)
{
	try {
		scoped_connection c(connectionPool);
		return !(QueryMaker(*(c.connection)).exec());
	} catch(const Exception& ex) {
		logger->error(boost::format("MySQL Error: %1%") % ex.what());
		throw InternalDatabaseError();
	}
}

static Query make_account_info_query(Connection& c, const char* username, const char* password)
{
	Query q = c.query();

	q << "SELECT aid, ugradeid, pgradeid FROM account"
	     " WHERE username=" << mysqlpp::quote << username <<
	     " AND password=md5(" << mysqlpp::quote << password << ")"
	     " LIMIT 1";

	return q;
}

static AccountInfo handle_account_info_query(const StoreQueryResult& result, const char* username)
{
	size_t rowCount = result.num_rows();

	assert(rowCount < 2);

	if(rowCount == 0)
		throw InvalidAccountInfo();

	AccountInfo ret;
	const Row& row = result[0];

	ret.AccountId = row["aid"];
	ret.AccountAccess = row["ugradeid"];
	ret.AccountPremium = row["ugradeid"];
	ret.AccountName = username;

	if ((ret.AccountAccess == 253) || (ret.AccountAccess == 105))
		throw BannedUser(username);

	return ret;
}

AccountInfo MySQLGunzDB::GetAccountInfo(const std::string& user, const std::string& password)
{
	return run_query<AccountInfo>(
		bind(make_account_info_query, _1, user.c_str(), password.c_str()),
		bind(handle_account_info_query, _1, user.c_str())
	);
}

static Query make_get_equipment_query(Connection& c, uint32_t cid)
{
	Query q = c.query();
	q << "SELECT * from character_equip where charid=" << cid;
	return q;
}

static SmallVector<Item, 12> handle_get_equipment(const StoreQueryResult& result)
{
	size_t rowCount = result.num_rows();
	assert(rowCount < 2);

	SmallVector<Item, 12> ret;

	if(rowCount == 0)
		return ret;

	const Row& row = result[0];

	Item temp;
	for(size_t i = 1, size = row.size(); i < size; ++i)
	{
		temp.ItemCID = row[i];
		ret.push_back(temp);
	}

	return ret;
}

SmallVector<Item, 12> MySQLGunzDB::GetEquipment(uint32_t cid)
{
	return run_query<SmallVector<Item, 12> >(
		bind(make_get_equipment_query, _1, cid),
		handle_get_equipment
	);
}

static Query make_get_inventory_query(Connection& c, uint32_t cid)
{
	Query q = c.query();
	q << "SELECT * FROM character_inventory where charid=" << cid;
	return q;
}

static vector<Item> handle_get_inventory(const StoreQueryResult& result)
{
	vector<Item> items(16);

	for(ResultIt i = result.begin(), end = result.end(); i != end; ++i)
	{
		const Row& row = *i;
		Item item;

		item.ItemCID = row["id"];
		item.ItemID = row["itemid"];

		if(row["rental"])
		{
			// TODO(Jacob): Handle item.RentHour
		}

		items.push_back(item);
	}

	return items;
}

vector<Item> MySQLGunzDB::GetInventory(uint32_t cid)
{
	return run_query<vector<Item> >(
		bind(make_get_inventory_query, _1, cid),
		handle_get_inventory
	);
}

static Query make_get_character_list_query(Connection& c, uint32_t aid)
{
	Query q = c.query();
	q << "SELECT name,level,marker FROM `character` where accountid=" << aid << " ORDER BY marker ASC";
	return q;
}

static SmallVector<CharacterEntry, 4> handle_get_character_list(const StoreQueryResult& result)
{
	SmallVector<CharacterEntry, 4> charList;

	assert(result.num_rows() <= 4);

	for(ResultIt i = result.begin(), end = result.end(); i != end; ++i)
	{
		const Row& row = *i;

		CharacterEntry character;
		character.CharacterIndex = row["marker"];
		character.CharacterLevel = row["level"];
		character.CharacterName = string(row["name"]);
	}

	return charList;
}

SmallVector<CharacterEntry, 4> MySQLGunzDB::GetCharacterList(uint32_t aid)
{
	return run_query<SmallVector<CharacterEntry, 4> >(
		bind(make_get_character_list_query, _1, aid),
		handle_get_character_list
	);
}

Query make_name_exists_query(Connection& c, const char* name)
{
	Query q = c.query();
	q << "SELECT accountid FROM `character` where name=" << mysqlpp::quote << name;
	return q;
}

bool handle_name_exists(const StoreQueryResult& result)
{
	size_t rowCount = result.num_rows();
	assert(rowCount < 2);

	return rowCount == 1;
}

bool MySQLGunzDB::NameExists(std::string name)
{
	return run_query<bool>(
		bind(make_name_exists_query, _1, name.c_str()),
		handle_name_exists
	);
}

Query make_get_cid_query(Connection& c, uint32_t aid, uint32_t marker)
{
	Query q = c.query();
	q << "SELECT id FROM `character` where accountid=" << aid << " AND marker=" << marker;
	return q;
}

uint32_t handle_get_cid(const StoreQueryResult& result)
{
	assert(result.num_rows() == 1);
	return result[0]["id"];
}

uint32_t MySQLGunzDB::GetCID(uint32_t aid, uint32_t marker)
{
	return run_query<uint32_t>(
		bind(make_get_cid_query, _1, aid, marker),
		handle_get_cid
	);
}

Query make_create_character_query(Connection& c,
	uint32_t aid, string name, uint32_t marker, uint32_t sex, uint32_t hair, uint32_t face, uint32_t costume)
{
	Query q = c.query();
	q << "INSERT INTO `character` (accountid,name,sex,hair,face,costume,marker) values ("
	  << aid << "," << mysqlpp::quote << name.c_str() << "," << sex << "," << hair << "," << face << "," << costume << "," << marker << ")";
	return q;
}

Query make_create_character_equip_query(Connection& c, uint32_t cid)
{
	Query q = c.query();
	q << "INSERT INTO character_equip(charid) VALUES (" << cid <<")";
	return q;
}

void MySQLGunzDB::CreateCharacter(boost::uint32_t aid, std::string name, boost::uint32_t marker, boost::uint32_t sex, boost::uint32_t hair, boost::uint32_t face, boost::uint32_t costume)
{
	if (!NameExists(name))
		throw NameInUse();

	bool succeeded = exec_query(
		bind(make_create_character_query, _1, aid, name, marker, sex, hair, face, costume)
	);

	if(!succeeded)
		throw InvalidCharacterName();

	uint32_t cid = GetCID(aid, marker);

	succeeded = exec_query(
		bind(make_create_character_equip_query, _1, cid)
	);

	if(!succeeded)
		throw InvalidCharacterName();
}

Query make_get_character_info_query(Connection& c, uint32_t aid, uint8_t marker)
{
	Query q = c.query();
	q << "SELECT * FROM `character` WHERE accountid=" << aid << " AND marker=" << static_cast<uint32_t>(marker);
	return q;
}

// Gets everything but the clan info, equipment, and inventory!
CharacterInfo handle_get_character_info(const StoreQueryResult& result, uint8_t marker)
{
	size_t rowCount = result.num_rows();
	assert(rowCount < 2);

	if(rowCount == 0)
		throw InvalidCharacterInfo();

	const Row& row = result[0];
	CharacterInfo charInfo;

	charInfo.CharacterId = row["id"];
	charInfo.CharacterMarker = marker;
	charInfo.CharacterName = string(row["name"]);
	charInfo.ClanId = row["clanid"];
	charInfo.CharacterLevel = row["level"];
	charInfo.CharacterSex = row["sex"];
	charInfo.CharacterHair = row["hair"];
	charInfo.CharacterFace = row["face"];
	charInfo.CharacterXP = row["xp"];
	charInfo.CharacterBP = row["bp"];

	return charInfo;
}

Query make_get_clan_info_query(Connection& c, uint32_t clanId)
{
	Query q = c.query();
	q << "SELECT * FROM clan WHERE id=" << clanId;
	return q;
}

void handle_clan_info(const StoreQueryResult& result, CharacterInfo* charInfo /* [out] */)
{
	size_t rowCount = result.num_rows();
	assert(rowCount < 2);

	const Row& row = result[0];

	if(rowCount == 1)
	{
		charInfo->ClanName = string(row["name"]);
		charInfo->ClanPoints = row["cwpoints"];
	}
}

CharacterInfo MySQLGunzDB::GetCharacterInfo(uint32_t aid, uint8_t slot)
{
	// Normal, clan, equip, inventory.
	CharacterInfo ret = run_query<CharacterInfo>(
		bind(make_get_character_info_query, _1, aid, static_cast<uint32_t>(slot)),
		bind(handle_get_character_info, _1, slot)
	);

	run_query<void>(
		bind(make_get_clan_info_query, _1, ret.ClanId),
		bind(handle_clan_info, _1, &ret)
	);

	ret.Equipment = GetEquipment(ret.CharacterId);
	ret.Inventory = GetInventory(ret.CharacterId);

	return ret;
}
