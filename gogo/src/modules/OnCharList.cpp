#include "../GoGoClient.h"

#include <database/CharacterEntry.h>
#include <database/GunzDB.h>
#include <database/oopsies.h>

#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseAccountCharList.h>
#include <cockpit/packet/Parameters.h>

#include <vector>

using namespace std;
using namespace boost;
using namespace cockpit;
using namespace cockpit::packet;

void GoGoClient::OnCharList()
{
	using protocol::Match_ResponseAccountCharList;

	typedef SmallVector<CharacterEntry, 4> CharList;

	if(!myAccount.isValid)
		return transmitter->disconnect();

	CharList charList = database->GetCharacterList(myAccount.AccountId);
	blob charBlob(charList.size(), 34);

	if (charList.size() == 0)
	{
		charBlob.add_param(packet::zeros(32));
	}
	else
	{
		for (CharList::iterator i = charList.begin(), e = charList.end(); i != e; ++i)
		{
			charBlob
				.add_param(blob_string(i->CharacterName.c_str(), 32))
				.add_param(uint8(i->CharacterIndex))
				.add_param(uint8(i->CharacterLevel))
			;
		}
	}

	transmitter->send(Match_ResponseAccountCharList(charBlob));
}
