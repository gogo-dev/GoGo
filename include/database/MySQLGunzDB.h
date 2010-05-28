#pragma once
#include "GunzDB.h"
#include "mysql++.h"


class MySQLGunzDB : public GunzDB
{
	private:

	public:
		/* Connection constructor/connecting/reconnecting/disconnecting */
		static mysqlpp::Connection gunzconn;
		MySQLGunzDB(std::string host, std::string user, std::string password, std::string port);
		~MySQLGunzDB();

		/* Login Process related functions*/
		void GetAccountInfoForLogin(const std::string& user, const std::string& password);
};