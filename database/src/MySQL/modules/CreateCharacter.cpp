#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

static void make_create_character_query(Query& q,
	uint32_t aid, string name, uint32_t marker, uint32_t sex, uint32_t hair, uint32_t face, uint32_t costume)
{
	q << "INSERT INTO `character` (accountid,name,sex,hair,face,costume,marker) values ("
	  << aid << "," << mysqlpp::quote << name.c_str() << "," << sex << "," << hair << "," << face << "," << costume << "," << marker << ")";
}

static void make_create_character_equip_query(Query& q, uint32_t cid)
{
	q << "INSERT INTO character_equip(charid) VALUES (" << cid <<")";
}

void MySQLGunzDB::CreateCharacter(const AccountInfo& accountInfo, const string& name, uint32_t marker, uint32_t sex, uint32_t hair, uint32_t face, uint32_t costume)
{
	if(!accountInfo.isValid)
		throw InvalidAccountInfo();

	if (NameExists(name))
		throw NameInUse();

	bool succeeded = exec_query(
		bind(make_create_character_query, _1, accountInfo.AccountId, name, marker, sex, hair, face, costume)
	);

	if(!succeeded)
		throw InvalidCharacterName();

	succeeded = exec_query(
		bind(make_create_character_equip_query, _1, GetCID(accountInfo.AccountId, marker))
	);

	if(!succeeded)
		throw InvalidCharacterName();
}
