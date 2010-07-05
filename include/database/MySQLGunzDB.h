#pragma once
#include <cockpit/Logger.h>

#include <database/oopsies.h>
#include <database/MySQL/ConnectionPool.h>

#include "GunzDB.h"
#include <typeinfo>	// Fixes a bug in mysql on clang++.
#include <mystring.h> // yet another bug in mysql + clang++.
#include <mysql++.h>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <memory>

class MySQLGunzDB : public GunzDB
{
private:
	ConnectionPool connectionPool;
	cockpit::Logger* logger;

private:
	struct scoped_connection : boost::noncopyable
	{
	private:
		ConnectionPool& pool;

	public:
		mysqlpp::Connection* connection;

		scoped_connection(ConnectionPool& _pool)
			: pool(_pool), connection(_pool.grab())
		{
		}

		~scoped_connection()
		{
			pool.release(connection);
		}
	};

private:
	/**
		Runs a query, automatically protecting the database from non-serial
		access.

		@param  QueryMaker    This is a function which takes a connection, and
		                      must generate a valid mysqlpp::Query from it. Think
		                      of it as your "factory".
		@param  ResultHandler This function is called after the query retrieves
		                      the result from the database. The handler will be
		                      called with the UseQueryResult passed into it.
		                      Whatever value this function returns will also be
		                      returned from run_query.

		@return Whatever ResultHandler returned.

		@throws InternalDatabaseError If the query failed, or some other bad
		                              database error occured.
	*/
	template <typename ResultType>
	ResultType run_query(
		boost::function<std::auto_ptr<mysqlpp::Query> (mysqlpp::Connection&)> QueryMaker,
		boost::function<ResultType (const mysqlpp::StoreQueryResult&)> ResultHandler
	)
	{
		mysqlpp::StoreQueryResult result;

		try
		{
			scoped_connection c(connectionPool);
			result = QueryMaker(*(c.connection))->store();
		}
		catch(const mysqlpp::Exception& ex)
		{
			logger->error(boost::format("MySQL Error: %1%") % ex.what());
			throw InternalDatabaseError();
		}

		return ResultHandler(result);
	}

	/**
		Executes the query. Returns true if it succeeded, false if it failed.
	*/
	bool exec_query(boost::function<std::auto_ptr<mysqlpp::Query> (mysqlpp::Connection&)> QueryMaker);

public:
	MySQLGunzDB(cockpit::Logger* logger, const char* dbname, const char* host, const char* user, const char* password, boost::uint16_t port = 3306);
	~MySQLGunzDB();

	//Login Process related functions
	AccountInfo GetAccountInfo(const std::string& user, const std::string& password);

	void DeleteCharacter(const AccountInfo& acc, boost::uint32_t marker);

	//Character processing related functions
private:
	SmallVector<Item, 12> GetEquipment(boost::uint32_t cid);
	std::vector<Item> GetInventory(boost::uint32_t cid);

public:
	SmallVector<CharacterEntry, 4> GetCharacterList(const AccountInfo& account);
	bool NameExists(std::string name);
	void CreateCharacter(const AccountInfo& account, const std::string& name, boost::uint32_t marker, boost::uint32_t sex, boost::uint32_t hair, boost::uint32_t face, boost::uint32_t costume);
	CharacterInfo GetCharacterInfo(const AccountInfo& acc, boost::uint8_t slot);

	boost::uint32_t GetCID(boost::uint32_t aid, boost::uint32_t marker);
};
