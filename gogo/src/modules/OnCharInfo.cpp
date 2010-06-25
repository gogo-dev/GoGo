#include "../GoGoClient.h"

#include <database/oopsies.h>
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

	try {
		myCharacter = database->GetCharacterInfo(myAccount.AccountId, marker);
	} catch(InvalidCharacterInfo& e) {
		logger->debug(e.what());
		return;
	}

	// Oh my god, good luck guys.
	uint8 index(marker);
	blob info(1, 146);

	info.add_param(blob_string(myCharacter.CharacterName.c_str(), 32));
	info.add_param(blob_string(myCharacter.ClanName.c_str(), 16));
	info.add_param(int32(myCharacter.CharacterGrade));
	info.add_param(int16(myCharacter.ClanPoints));
	info.add_param(uint8(myCharacter.CharacterMarker));
	info.add_param(int16(myCharacter.CharacterLevel));
	info.add_param(uint8(myCharacter.CharacterSex));
	info.add_param(uint8(myCharacter.CharacterHair));
	info.add_param(uint8(myCharacter.CharacterFace));
	info.add_param(uint32(myCharacter.CharacterXP));
	info.add_param(uint32(myCharacter.CharacterBP));
	info.add_param(floating_point(0)); // fBonusRate - not used.
	info.add_param(zeros(18)); // not used :/

	assert(myCharacter.Equipment.size() == 12);

	for(size_t i = 0; i < myCharacter.Equipment.size(); ++i)
		info.add_param(int32(myCharacter.Equipment[i].ItemID));

	info.add_param(int32(myAccount.AccountAccess));
	info.add_param(int32(myCharacter.ClanId));

	transmitter->send(Match_ResponseAccountCharInfo(myCharacter.CharacterMarker, info));
}
