#include "../GoGoClient.h"
#include "../error_codes.h"

#include <gunz/Channel.h>
#include <gunz/ChannelList.h>
#include <gunz/simple_types.h>

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/Parameters.h>
#include <cockpit/packet/protocol/Channel_ResponsePlayerList.h>

#include <cassert>

using namespace std;
using namespace boost;
using namespace cockpit;

void GoGoClient::OnChannelPlayerList (const gunz::MUID& playerId, const gunz::MUID& channelId, const uint32_t&  page)
{
	//Okay math time....
	//Each page is 6 players , so the index we want to get is page * 6.
	//So if page is 1, we'd get players 6 - 11

	uint32_t clientStart = page * 6;
	if (clientStart > myChannel->players.Length())
		return;

	//get number of players from the stage.
	uint32_t count = min(myChannel->players.Length() - clientStart, 6);

	packet::uint8 playerCount((uint8_t)myChannel->players.Length());
	packet::uint8 pageNum((uint8_t)page);
	packet::blob playerList(count, 71);

	std::vector<Player*> players = myChannel->players.Clone();
	std::vector<Player*>::iterator i;

	for (i = players.begin(); i < players.end(); i++)
	{
		GoGoClient* client = (GoGoClient*)(*i);

		playerList.add_param(packet::MUID(client->myMUID));
		playerList.add_param(packet::blob_string(client->myCharacter.CharacterName.c_str(), 32));
		playerList.add_param(packet::blob_string(client->myCharacter.ClanName.c_str(), 16));
		playerList.add_param(packet::uint8((uint8_t)client->myCharacter.CharacterLevel));
		playerList.add_param(packet::int32(client->myPlace));
		playerList.add_param(packet::uint8(client->myAccount.AccountAccess));
		playerList.add_param(packet::uint8(2)); // usually 2.
		playerList.add_param(packet::int32(client->myCharacter.ClanId));
		playerList.add_param(packet::int32(0)); // emblem?
	}

	transmitter->send(packet::protocol::Channel_ResponsePlayerList(playerCount, pageNum, playerList));
}
