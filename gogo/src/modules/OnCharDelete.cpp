#include "../GoGoClient.h"

#include "../error_codes.h"

#include <database/oopsies.h>
#include <database/GunzDB.h>

#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseDeleteChar.h>
#include <cockpit/packet/Parameters.h>

#include <vector>

using namespace std;
using namespace boost;
using namespace cockpit;

void GoGoClient::OnCharDelete(gunz::MUID /* uidPlayer */, uint32_t charMarker, const std::string& /* charName */)
{
	if(!myAccount.isValid)
		return transmitter->disconnect("Tried to delete a character without first logging in.");

	database->DeleteCharacter(myAccount, charMarker);
	transmitter->send(packet::protocol::Match_ResponseDeleteChar(PEC_NONE));
}
