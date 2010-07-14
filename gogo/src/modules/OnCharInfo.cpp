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
		return transmitter->disconnect("Tried to get info for an out-of-bounds character.");

	if(!myAccount.isValid)
		return transmitter->disconnect("Tried to get character info without first logging in.");

	try {
		myCharacter = database->GetCharacterInfo(myAccount, marker);
	} catch(InvalidCharacterInfo& e) {
		logger->debug(e.what());
		return;
	}

	// Oh my god, good luck guys.
	blob info(1, 146);

	info
		.add_param(blob_string(myCharacter.name.c_str(), 32))
		.add_param(blob_string(myCharacter.clanName.c_str(), 16))
		.add_param(int32(myCharacter.grade))
		.add_param(int16(myCharacter.clanScore))
		.add_param(uint8(myCharacter.marker))
		.add_param(int16(myCharacter.level))    // TODO: Wtf...
		.add_param(int16(myCharacter.level))    //             ....?
		.add_param(uint8(myCharacter.gender))
		.add_param(uint8(myCharacter.hairstyle))
		.add_param(uint8(myCharacter.facestyle))
		.add_param(uint32(myCharacter.experience))
		.add_param(uint32(myCharacter.bounty))
		.add_param(floating_point(0)) // fBonusRate - not used.
		.add_param(zeros(18))	// not used :/
	;

	assert(myCharacter.equipment.size() == 12);

	for(size_t i = 0; i < myCharacter.equipment.size(); ++i)
		info.add_param(int32(myCharacter.equipment[i].ItemID));

	info
		.add_param(int32(myAccount.AccountAccess))
		.add_param(int32(myCharacter.clanid))
	;

	transmitter->send(Match_ResponseAccountCharInfo(myCharacter.marker, info));
}
