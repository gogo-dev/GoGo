#include <database/MySQLGunzDB.h>

using namespace std;

MySQLGunzDB::MySQLGunzDB(std::string host, std::string user, std::string password, std::string port)
{
	//start the connection
			gunzconn.connect(
							host.c_str(),
							user.c_str(),
							password.c_str(),
							port.c_str()
							);
}

MySQLGunzDB::~MySQLGunzDB()
{


}

void MySQLGunzDB::GetAccountInfoForLogin(const std::string &user, const std::string &password)
{

	//todo: fill this in

	return;

}