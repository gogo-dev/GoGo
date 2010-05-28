#include <database/MySQLGunzDB.h>

using namespace std;

MySQLGunzDB::MySQLGunzDB(const char* host, const char* user, const char* password, const char* port)
{
	gunzconn.connect(host, user, password, port);
}

MySQLGunzDB::~MySQLGunzDB()
{
}

void MySQLGunzDB::GetAccountInfoForLogin(const char* /*user*/, const char* /*password*/)
{

	//TODO(Specials): fill this in

	return;

}