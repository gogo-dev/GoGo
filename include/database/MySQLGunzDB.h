#pragma once
#include "GunzDB.h"
#include "mysql++.h"


class MySQLGunzDB : public GunzDB
{
	private:
		mysqlpp::Connection gunzconn;

	public:
		MySQLGunzDB(const char* host, const char* user, const char* password, const char* port);
		~MySQLGunzDB();

		// Login Process related functions
		void GetAccountInfoForLogin(const char* user, const char* password);
};