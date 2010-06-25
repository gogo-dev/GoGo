#include "../GoGoClient.h"

#include <database/oopsies.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseDeleteChar.h>
#include <cockpit/packet/Parameters.h>

#include <vector>

using namespace std;
using namespace boost;
using namespace cockpit;

static void send_result(Transmitter* transmitter, PacketErrorCode err)
{
	using packet::protocol::Match_ResponseDeleteChar;
	transmitter->send(Match_ResponseDeleteChar(packet::int32(err)));
}

void GoGoClient::OnCharDelete(MUID /* uidPlayer */, uint32_t charMarker, const std::string& /* charName */)
{
	database->DeleteCharacter(myAccount.AccountId, charMarker);
	return send_result(transmitter, PEC_NONE);
}
