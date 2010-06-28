#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

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

void MySQLGunzDB::CreateCharacter(const AccountInfo& accountInfo, const string& name, uint32_t marker, uint32_t sex, uint32_t hair, uint32_t face, uint32_t costume)
{
	if(!accountInfo.isValid)
		throw InvalidAccountInfo();

	if (!NameExists(name))
		throw NameInUse();

	bool succeeded = exec_query(
		bind(make_create_character_query, _1, accountInfo.AccountId, name, marker, sex, hair, face, costume)
	);

	if(!succeeded)
		throw InvalidCharacterName();

	uint32_t cid = GetCID(accountInfo.AccountId, marker);

	succeeded = exec_query(
		bind(make_create_character_equip_query, _1, cid)
	);

	if(!succeeded)
		throw InvalidCharacterName();
}
