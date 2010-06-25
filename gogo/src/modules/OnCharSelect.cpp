#include "../GoGoClient.h"

#include <database/oopsies.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseSelectChar.h>
#include <cockpit/packet/Parameters.h>

#include <vector>
using namespace std;
using namespace boost;
using namespace cockpit;
using namespace packet;

void GoGoClient::OnCharSelect(boost::uint64_t /* uid */, uint8_t marker)
{
	using packet::protocol::Match_ResponseSelectChar;

	if (marker > 3)
	{
		logger->info(format("[%1%] Hack Detected! (Tried to get info for an out-of-bounds character)") % transmitter->get_ip());
		return transmitter->disconnect();
	}

	try
	{
		myCharacter = database->GetCharacterInfo(myAccount.AccountId, marker);
	} catch(InvalidCharacterInfo& e) {
		logger->debug(e.what());
		return transmitter->disconnect();
	}

	// Oh my god, good luck guys.
	int32 result(0);
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
	info.add_param(zeros(18));

	assert(myCharacter.Equipment.size() == 12);

	for(int i = 0; i < 12; ++i)
		info.add_param(int32(myCharacter.Equipment[i].ItemID));

	info.add_param(int32((uint32_t)myAccount.AccountAccess));
	info.add_param(int32(myCharacter.ClanId));

	blob extra(1,1);
	extra.add_param(uint8(0x3E));

	transmitter->send(Match_ResponseSelectChar(result, info, extra));
}
