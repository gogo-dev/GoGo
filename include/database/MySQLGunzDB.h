#pragma once
#include <cockpit/Logger.h>

#include <database/oopsies.h>

#include "GunzDB.h"
#include <typeinfo>	// Fixes a bug in mysql on clang++.
#include <mystring.h> // yet another bug in mysql + clang++.
#include <mysql++.h>

#include <boost/thread/recursive_mutex.hpp> // don't we love mutexs?
#include <boost/function.hpp>

class MySQLGunzDB : public GunzDB
{
private:
	mysqlpp::Connection gunzconn;
	cockpit::Logger* logger;
	boost::recursive_mutex databaseProtection;
private:
<<<<<<< HEAD
	static std::vector<Item> GetItemsFromRow(const mysqlpp::Row& row);
	boost::uint32_t GetCID (boost::uint32_t aid, boost::uint32_t marker);
	bool DoesNameExist(std::string name);
=======
	boost::uint32_t GetCID(boost::uint32_t aid, boost::uint32_t marker);

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
		boost::function<mysqlpp::Query (mysqlpp::Connection&)> QueryMaker,
		boost::function<ResultType (const mysqlpp::StoreQueryResult&)> ResultHandler
	)
	{
		mysqlpp::StoreQueryResult result;

		try {
			boost::recursive_mutex::scoped_lock p(databaseProtection);
			result = QueryMaker(gunzconn).store();
		} catch(const mysqlpp::Exception& ex) {
			logger->error(boost::format("MySQL Error: %1%") % ex.what());
			throw InternalDatabaseError();
		}

		return ResultHandler(result);
	}

	/**
		Executes the query. Returns true if it succeeded, false if it failed.
	*/
	bool exec_query(boost::function<mysqlpp::Query (mysqlpp::Connection&)> QueryMaker);

public:
	MySQLGunzDB(cockpit::Logger* _logger, const char* dbname, const char* host, const char* user, const char* password, unsigned int port = 3306);
	~MySQLGunzDB();

	//Login Process related functions
	AccountInfo GetAccountInfo(const std::string& user, const std::string& password);

	bool DeleteCharacter(boost::uint32_t cid, boost::uint32_t marker, std::string name);

	//Character processing related functions
	SmallVector<Item, 12> GetEquipment(boost::uint32_t cid);
	std::vector<Item> GetInventory(boost::uint32_t cid);
	SmallVector<CharacterEntry, 4> GetCharacterList(boost::uint32_t aid);
	bool NameExists(std::string name);
	void CreateCharacter(boost::uint32_t aid, std::string name, boost::uint32_t marker, boost::uint32_t sex, boost::uint32_t hair, boost::uint32_t face, boost::uint32_t costume);
	CharacterInfo GetCharacterInfo(boost::uint32_t cid, boost::uint8_t slot);
};
