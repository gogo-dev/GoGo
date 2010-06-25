#include "../GoGoClient.h"

#include <database/oopsies.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/protocol/Match_ResponseAccountCharList.h>
#include <cockpit/packet/Parameters.h>

#include <vector>
using namespace std;
using namespace boost;
using namespace cockpit;
void GoGoClient::OnCharList()
{
	using packet::protocol::Match_ResponseAccountCharList;

	typedef SmallVector<CharacterEntry, 4> CharList;

	CharList charList = database->GetCharacterList(myAccount.AccountId);
	packet::blob charBlob(charList.size(), 34);

	if (charList.size() == 0)
	{
		charBlob.add_param(packet::zeros(32));
	}
	else
	{
		for (CharList::iterator i = charList.begin(), e = charList.end(); i != e; ++i)
		{
			charBlob.add_param(packet::blob_string(i->CharacterName.c_str(), 32));
			charBlob.add_param(packet::uint8(i->CharacterIndex));
			charBlob.add_param(packet::uint8(i->CharacterLevel));
		}
	}

	transmitter->send(Match_ResponseAccountCharList(charBlob));
}
