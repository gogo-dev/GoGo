#include "../GoGoClient.h"

#include <database/oopsies.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseCreateChar.h>
#include <cockpit/packet/Parameters.h>

#include <vector>
using namespace std;
using namespace boost;
using namespace cockpit;

void GoGoClient::OnCharCreate(MUID uidPlayer, uint32_t charMarker, std::string charName, uint32_t charSex, uint32_t charHair, uint32_t charFace, uint32_t charCostume)
{
	using packet::protocol::Match_ResponseCreateChar;
	PacketErrorCode errorCode = PEC_NONE;

	if (uidPlayer != myMUID)
	{
		logger->info(format("[%1%] MUID Hacking Detected!") % transmitter->get_ip());
		transmitter->disconnect();
		return;
	}

	try
	{
		if (charName.length() <= 3)
			errorCode = PEC_NAME_SHORT;

		else if (charName.length() >= 16)
			errorCode = PEC_NAME_LONG;

		else if (!database->CreateCharacter(myAccount.AccountId, charName, charMarker, charSex, charHair, charFace, charCostume))
			errorCode = PEC_INVALID_NAME;
	}
	catch(NameInUse& e)
	{
		logger->debug(e.what());
		errorCode = PEC_NAME_IN_USE;
	}

	packet::int32 result(errorCode);
	packet::string name(charName);

	transmitter->send(Match_ResponseCreateChar(result, name));
}
