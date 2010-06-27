#include "../GoGoClient.h"

#include <database/oopsies.h>
#include <database/GunzDB.h>

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseAccountCharInfo.h>
#include <cockpit/packet/Parameters.h>

#include <vector>
#include <cstddef>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace packet;

void GoGoClient::OnCharInfo(uint8_t marker)
{
	using packet::protocol::Match_ResponseAccountCharInfo;

	if (marker > 3)
	{
		logger->info(format("[%1%] Hack Detected! (Tried to get info for an out-of-bounds character)") % transmitter->get_ip());
		return transmitter->disconnect();
	}

	if(!myAccount.isValid)
		return transmitter->disconnect();

	try {
		myCharacter = database->GetCharacterInfo(myAccount.AccountId, marker);
	} catch(InvalidCharacterInfo& e) {
		logger->debug(e.what());
		return;
	}

	// Oh my god, good luck guys.
	blob info(1, 146);

	info
		.add_param(blob_string(myCharacter.CharacterName.c_str(), 32))
		.add_param(blob_string(myCharacter.ClanName.c_str(), 16))
		.add_param(int32(myCharacter.CharacterGrade))
		.add_param(int16(myCharacter.ClanPoints))
		.add_param(uint8(myCharacter.CharacterMarker))
		.add_param(int16(myCharacter.CharacterLevel))
		.add_param(int16(myCharacter.CharacterLevel))
		.add_param(uint8(myCharacter.CharacterSex))
		.add_param(uint8(myCharacter.CharacterHair))
		.add_param(uint8(myCharacter.CharacterFace))
		.add_param(uint32(myCharacter.CharacterXP))
		.add_param(uint32(myCharacter.CharacterBP))
		.add_param(floating_point(0)) // fBonusRate - not used.
		.add_param(zeros(18))	// not used :/
	;

	assert(myCharacter.Equipment.size() == 12);

	for(size_t i = 0; i < myCharacter.Equipment.size(); ++i)
		info.add_param(int32(myCharacter.Equipment[i].ItemID));

	info
		.add_param(int32(myAccount.AccountAccess))
		.add_param(int32(myCharacter.ClanId))
	;

	transmitter->send(Match_ResponseAccountCharInfo(myCharacter.CharacterMarker, info));
}
