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

static void convert_to_traits(gunz::MUID myMUID, const CharacterInfo& charInfo, gunz::Player::Traits& traits)
{
	traits.muid = myMUID;
	traits.characterName = charInfo.name;
	traits.clanid = charInfo.clanid;
	traits.clanName = charInfo.clanName;
	traits.level = charInfo.level;
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
		.add_param(blob_string(myCharacter.name.c_str(), 32))
		.add_param(blob_string(myCharacter.clanName.c_str(), 16))
		.add_param(int32(myCharacter.grade))
		.add_param(int16(myCharacter.clanScore))
		.add_param(uint8(myCharacter.marker))
		.add_param(int16(myCharacter.level))
		.add_param(uint8(myCharacter.gender))
		.add_param(uint8(myCharacter.hairstyle))
		.add_param(uint8(myCharacter.facestyle))
		.add_param(uint32(myCharacter.experience))
		.add_param(uint32(myCharacter.bounty))
		.add_param(floating_point(0))	// fBonusRate - not used.
		.add_param(zeros(18))
	;

	assert(myCharacter.equipment.size() == 12);

	for(int i = 0; i < 12; ++i)
		info.add_param(int32(myCharacter.equipment[i].ItemID));

	info
		.add_param(int32((uint32_t)myAccount.AccountAccess))
		.add_param(int32(myCharacter.clanid))
	;

	blob extra(1,1);
	extra.add_param(uint8(0x3E));

	transmitter->send(Match_ResponseSelectChar(result, info, extra));

	ModifyTraits(bind(convert_to_traits, myMUID, myCharacter, _1));
}
