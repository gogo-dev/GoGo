#include <database/MySQLGunzDB.h>
#include <boost/bind/bind.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

static Query make_delete_character_query(Connection& c, uint32_t aid, uint32_t marker, const char* name)
{
	Query q = c.query();
	q << "DELETE FROM `character` WHERE accountid=" << aid << " AND marker=" << marker << " AND name=" << mysqlpp::quote <<  name;
	return q;
}

static Query make_update_marker_info_query(Connection& c, uint32_t aid, uint32_t marker)
{
	Query q = c.query();
	q << "UPDATE `character` set marker=marker-1 where marker > " << marker << " and accountid=" << aid;
	return q;
}

bool MySQLGunzDB::DeleteCharacter(uint32_t aid, uint32_t marker, const string& name)
{
	bool success = exec_query(
		bind(make_delete_character_query, _1, aid, marker, name.c_str())
	);

	if(!success)
		return false;

	return exec_query(
		bind(make_update_marker_info_query, _1, aid, marker)
	);
}
