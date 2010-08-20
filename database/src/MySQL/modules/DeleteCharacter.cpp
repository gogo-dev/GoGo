#include <database/MySQLGunzDB.h>

#include <boost/cstdint.hpp>
#include <boost/bind/bind.hpp>

using namespace boost;
using namespace mysqlpp;

static void make_delete_character_query(Query& q, uint32_t aid, uint32_t marker)
{
	q << "DELETE FROM `character` WHERE accountid=" << aid << " AND marker=" << marker;
}

static void make_update_marker_info_query(Query& q, uint32_t aid, uint32_t marker)
{
	q << "UPDATE `character` set marker=marker-1 where marker > " << marker << " and accountid=" << aid;
}

void MySQLGunzDB::DeleteCharacter(const AccountInfo& acc, uint32_t marker)
{
	if(marker > 3)
		return;

	if(!acc.isValid)
		throw InvalidAccountInfo();

	exec_query(
		boost::bind(make_delete_character_query, _1, acc.aid, marker)
	);

	exec_query(
		boost::bind(make_update_marker_info_query, _1, acc.aid, marker)
	);
}
