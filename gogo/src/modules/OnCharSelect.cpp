#include "../GoGoClient.h"

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseSelectChar.h>
#include <cockpit/packet/Parameters.h>

#include <database/oopsies.h>
#include <database/GunzDB.h>

#include <gunz/Player.h>

#include <boost/bind/bind.hpp>

#include <vector>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace packet;

// TODO: Temp.
static void convert_to_traits(gunz::MUID myMUID, const CharacterInfo& charInfo, gunz::Player::Traits& traits)
{
	traits.muid = myMUID;
	traits.characterName = charInfo.CharacterName;
	traits.clanid = charInfo.ClanId;
	traits.clanName = charInfo.ClanName;
	traits.level = charInfo.CharacterLevel;
}

void GoGoClient::OnCharSelect(boost::uint64_t /* uid */, uint8_t marker)
{
	using packet::protocol::Match_ResponseSelectChar;

	if(marker > 3)
		return transmitter->disconnect("Tried to select an out-of-bounds character.");

	if(!myAccount.isValid)
		return transmitter->disconnect("Tried to select a character without first logging in.");

	try {
		myCharacter = database->GetCharacterInfo(myAccount, marker);
	} catch(InvalidCharacterInfo& e) {
		return transmitter->disconnect(e.what());
	}

	// Oh my god, good luck guys.
	int32 result(0);
	blob info(1, 146);

	info
		.add_param(blob_string(myCharacter.CharacterName.c_str(), 32))
		.add_param(blob_string(myCharacter.ClanName.c_str(), 16))
		.add_param(int32(myCharacter.CharacterGrade))
		.add_param(int16(myCharacter.ClanPoints))
		.add_param(uint8(myCharacter.CharacterMarker))
		.add_param(int16(myCharacter.CharacterLevel))
		.add_param(uint8(myCharacter.CharacterSex))
		.add_param(uint8(myCharacter.CharacterHair))
		.add_param(uint8(myCharacter.CharacterFace))
		.add_param(uint32(myCharacter.CharacterXP))
		.add_param(uint32(myCharacter.CharacterBP))
		.add_param(floating_point(0))	// fBonusRate - not used.
		.add_param(zeros(18))
	;

	assert(myCharacter.Equipment.size() == 12);

	for(int i = 0; i < 12; ++i)
		info.add_param(int32(myCharacter.Equipment[i].ItemID));

	info
		.add_param(int32((uint32_t)myAccount.AccountAccess))
		.add_param(int32(myCharacter.ClanId))
	;

	blob extra(1,1);
	extra.add_param(uint8(0x3E));

	transmitter->send(Match_ResponseSelectChar(result, info, extra));

	ModifyTraits(bind(convert_to_traits, myMUID, myCharacter, _1));
}
