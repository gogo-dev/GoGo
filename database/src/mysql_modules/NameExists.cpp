#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

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
