#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace boost;
using namespace mysqlpp;

static void make_account_info_query(Query& q, const char* username, const char* password)
{
	q << "SELECT aid, ugradeid, pgradeid FROM account"
	     " WHERE username=" << mysqlpp::quote << username <<
	     " AND password=md5(" << mysqlpp::quote << password << ")"
	     " LIMIT 1";
}

static AccountInfo handle_account_info_query(const StoreQueryResult& result, const char* username)
{
	size_t rowCount = result.num_rows();

	assert(rowCount < 2);

	if(rowCount == 0)
		throw InvalidAccountInfo();

	const Row& row = result[0];

	AccountInfo ret(row["aid"], username, row["ugradeid"], row["pgradeid"]);

	if ((ret.access == 253) || (ret.access == 105))
		throw BannedUser(username);

	return ret;
}

AccountInfo MySQLGunzDB::GetAccountInfo(const std::string& user, const std::string& password)
{
	return run_query<AccountInfo>(
		boost::bind(make_account_info_query, _1, user.c_str(), password.c_str()),
		boost::bind(handle_account_info_query, _1, user.c_str())
	);
}
