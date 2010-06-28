#include "../GoGoClient.h"

#include "../error_codes.h"

#include <database/oopsies.h>
#include <database/GunzDB.h>

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseCreateChar.h>
#include <cockpit/packet/Parameters.h>

#include <vector>

using namespace std;
using namespace boost;
using namespace cockpit;

static void reply(Transmitter* t, int32_t result, const std::string& characterName)
{
	t->send(packet::protocol::Match_ResponseCreateChar(
		result, characterName
	));
}

void GoGoClient::OnCharCreate(gunz::MUID /* uidPlayer */, uint32_t charMarker, const std::string& charName, uint32_t charSex, uint32_t charHair, uint32_t charFace, uint32_t charCostume)
{
	if(!myAccount.isValid)
		return transmitter->disconnect();

	try
	{
		if(charName.length() <= 3)
			return reply(transmitter, PEC_NAME_SHORT, charName);

		if(charName.length() >= 16)
			return reply(transmitter, PEC_NAME_LONG, charName);

		database->CreateCharacter(myAccount, charName, charMarker, charSex, charHair, charFace, charCostume);

		return reply(transmitter, PEC_NONE, charName);
	}
	catch(const NameInUse& e)
	{
		logger->debug(e.what());
		return reply(transmitter, PEC_NAME_IN_USE, charName);
	}
	catch(const InvalidCharacterInfo& e)
	{
		logger->debug(e.what());
		return reply(transmitter, PEC_INVALID_NAME, charName);
	}
}
