#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

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
