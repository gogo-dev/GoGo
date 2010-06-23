#include "../GoGoClient.h"

#include <database/oopsies.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseDeleteChar.h>
#include <cockpit/packet/Parameters.h>

#include <vector>
using namespace std;
using namespace boost;
using namespace cockpit;

void GoGoClient::OnCharDelete(MUID uidPlayer, uint32_t charMarker, std::string charName)
{
	using packet::protocol::Match_ResponseDeleteChar;
	PacketErrorCode errorCode = PEC_NONE;

	if (uidPlayer != myMUID)
	{
		logger->info(format("[%1%] MUID Hacking Detected!") % transmitter->get_ip());
		transmitter->disconnect();
		return;
	}

	if (charName.length() <= 3)
		errorCode = PEC_NAME_SHORT;

	else if (charName.length() >= 16)
		errorCode = PEC_NAME_LONG;

	else if (!database->DeleteCharacter(myAccount.AccountId, charMarker, charName))
		errorCode = PEC_INVALID_NAME;

	packet::int32 result(errorCode);

	transmitter->send(Match_ResponseDeleteChar(result));
}
