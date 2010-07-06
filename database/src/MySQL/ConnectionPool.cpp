#include <database/MySQL/ConnectionPool.h>

using namespace std;

ConnectionPool::ConnectionPool(
	const char* _dbname,
	const char* _host,
	const char* _user,
	const char* _password,
	unsigned short _port)
	: dbname(_dbname), host(_host), user(_user), password(_password), port(_port)
{
}

mysqlpp::Connection* ConnectionPool::create()
{
	return new mysqlpp::Connection(dbname.c_str(), host.c_str(), user.c_str(), password.c_str(), port);
}

void ConnectionPool::destroy(mysqlpp::Connection* connection)
{
	delete connection;
}

#define SECONDS
#define MINUTES SECONDS*60
#define HOURS MINUTES*60

unsigned int ConnectionPool::max_idle_time()
{
	return 5 MINUTES;
}

#undef HOURS
#undef MINUTES
#undef SECONDS

ConnectionPool::~ConnectionPool()
{
	clear();
}
