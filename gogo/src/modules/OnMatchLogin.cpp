#include "../GoGoClient.h"
#include "../error_codes.h"

#include <gunz/simple_types.h>

#include <database/oopsies.h>
#include <database/GunzDB.h>

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseLogin.h>
#include <cockpit/packet/Parameters.h>

#include <boost/format.hpp>

using namespace std;
using namespace boost;
using namespace cockpit;

static void reply(
	Transmitter* transmitter,
	PacketErrorCode result,
	const char* serverName,
	int8_t mode,
	const char* account,
	uint8_t ugrade,
	uint8_t pgrade,
	gunz::MUID muid)
{
	packet::blob encryptMSG(1, 20);
	encryptMSG.add_param(packet::zeros(20));

	transmitter->send(packet::protocol::Match_ResponseLogin(result, serverName, mode, account, ugrade, pgrade, muid, encryptMSG));
}

void GoGoClient::OnMatchLogin(
    const std::string& username,
	const std::string& password,
	int32_t /* commandVersion */,
	uint32_t /* ChecksumPack */)
{
	PacketErrorCode errorCode = PEC_NONE;

	try {
		myAccount = database->GetAccountInfo(username, password);
		logger->debug(format("User: %1% has logged in!") % username);

	} catch (InvalidAccountInfo &e) {
		logger->info(e.what());
		errorCode = PEC_WRONG_PASSWORD;

	} catch (BannedUser &e) {
		logger->info(e.what());
		errorCode = PEC_USER_BANNED;

	} catch(const InternalDatabaseError& ex) {
		logger->warning(ex.what());
	}

	return reply(
		transmitter,
		errorCode,
		"GoGo MatchServer",	// TODO: Load this from the config file.
		2,	// What? Is this supposed to mean something?
		username.c_str(),
		myAccount.AccountAccess,
		myAccount.AccountPremium,
		myMUID
	);
}
