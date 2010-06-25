#pragma once
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

#include <typeinfo>	// Fixes a bug in mysql on clang++.
#include <mystring.h> // yet another bug in mysql + clang++.
#include <mysql++.h>

class ConnectionPool
    : boost::noncopyable,
      public mysqlpp::ConnectionPool
{
private:
	std::string dbname;
	std::string host;
	std::string user;
	std::string password;
	boost::uint16_t port;

public:
	ConnectionPool(const char* dbname, const char* host, const char* user, const char* password, boost::uint16_t port);

private:
	mysqlpp::Connection* create();
	void destroy(mysqlpp::Connection* connection);
	unsigned int max_idle_time();

public:
	~ConnectionPool();
};
