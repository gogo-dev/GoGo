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

	vector<CharacterEntry> charList = database->GetCharacterList(myAccount.AccountId);
	packet::blob charBlob (charList.size(), 34);

	if (charList.size() == 0)
	{
		for (int i = 0; i < 32; ++i)
			charBlob.add_param(packet::uint8(0));
	}
	else
	{
		for (size_t i = 0; i < charList.size(); ++i)
		{
			charBlob.add_param(packet::blob_string(charList[i].CharacterName.c_str(), 32));
			charBlob.add_param(packet::uint8(charList[i].CharacterIndex));
			charBlob.add_param(packet::uint8(charList[i].CharacterLevel));
		}
	}

	transmitter->send(Match_ResponseAccountCharList(charBlob));
}
