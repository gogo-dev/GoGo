#include "../GoGoClient.h"

#include <database/oopsies.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseLogin.h>
#include <cockpit/packet/Parameters.h>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace packet;

void GoGoClient::OnMatchLogin(
    const std::string& username,
	const std::string& password,
	int32_t commandVersion,
	uint32_t ChecksumPack)
{
	PacketErrorCode errorCode;

	try
	{
		myAccount = database->GetAccountInfo (username, password);

		logger->info(format("User: %1% has logged in!") % username);
		errorCode = PEC_NONE;
	}
	catch (InvalidAccountInfo &e)
	{
		logger->info(e.what());
		errorCode = PEC_WRONG_PASSWORD;
	}
	catch (BannedUser &e)
	{
		logger->info(e.what());
		errorCode = PEC_USER_BANNED;
	}

	packet::int32 result(errorCode);
	packet::string serverName ("Lol Emu Test");
	packet::int8 mode(2);
	packet::string account(username);
	packet::uint8 ugrade(myAccount.AccountAccess);
	packet::uint8 pgrade(myAccount.AccountPremium);
	packet::MUID muid(myMUID);
	packet::blob encryptMSG (1, 20);

	for (int i = 0; i < 5; ++i)
		encryptMSG.add_param(packet::int32(0));

	protocol::Match_ResponseLogin toSend(result, serverName, mode, account, ugrade, pgrade, muid, encryptMSG);
	transmitter->send(&toSend);

}
