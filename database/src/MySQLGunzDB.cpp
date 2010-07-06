#include <database/oopsies.h>
#include <database/MySQLGunzDB.h>

#include <exception>

#include <cstddef>

#include <boost/function.hpp>
#include <boost/bind/bind.hpp>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace mysqlpp;

typedef mysqlpp::StoreQueryResult::const_iterator ResultIt;

MySQLGunzDB::MySQLGunzDB(Logger* log, const char* dbname, const char* host, const char* user, const char* password, uint16_t port)
	: connectionPool(dbname, host, user, password, port), logger(log)
{
	logger->debug("Testing database connection...");
	Connection c(dbname, host, user, password, port);
	logger->debug("Connected!");
}

MySQLGunzDB::~MySQLGunzDB()
{
}

bool MySQLGunzDB::exec_query(function<void (Query&)> QueryMaker)
{
	try {
		scoped_connection c(connectionPool);

		Query q(c.connection->query());
		QueryMaker(q);
		return !q.exec();

	} catch(const Exception& ex) {
		logger->error(boost::format("MySQL Error: %1%") % ex.what());
		throw InternalDatabaseError();
	}
}
