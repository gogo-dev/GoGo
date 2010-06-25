#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

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
