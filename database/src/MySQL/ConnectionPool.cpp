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

// Waits for 30 seconds of unuse before destroying a connection.
unsigned int ConnectionPool::max_idle_time()
{
	return 30;
}

ConnectionPool::~ConnectionPool()
{
	clear();
}
