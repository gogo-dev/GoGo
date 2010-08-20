#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace boost;
using namespace mysqlpp;

static void make_get_cid_query(Query& q, uint32_t aid, uint32_t marker)
{
	q << "SELECT id FROM `character` where accountid=" << aid << " AND marker=" << marker;
}

static uint32_t handle_get_cid(const StoreQueryResult& result)
{
	assert(result.num_rows() == 1);
	return result[0]["id"];
}

uint32_t MySQLGunzDB::GetCID(uint32_t aid, uint32_t marker)
{
	if(aid == 0xFFFFFFFF)
		throw InvalidAccountInfo();

	return run_query<uint32_t>(
		boost::bind(make_get_cid_query, _1, aid, marker),
		handle_get_cid
	);
}
