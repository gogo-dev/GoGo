#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

static Query make_get_character_list_query(Connection& c, uint32_t aid)
{
	Query q = c.query();
	q << "SELECT name,level,marker FROM `character` where accountid=" << aid << " ORDER BY marker ASC";
	return q;
}

static SmallVector<CharacterEntry, 4> handle_get_character_list(const StoreQueryResult& result)
{
	typedef mysqlpp::StoreQueryResult::const_iterator ResultIt;

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
	if(aid == 0xFFFFFFFF)
		throw InvalidAccountInfo();

	return run_query<SmallVector<CharacterEntry, 4> >(
		bind(make_get_character_list_query, _1, aid),
		handle_get_character_list
	);
}
