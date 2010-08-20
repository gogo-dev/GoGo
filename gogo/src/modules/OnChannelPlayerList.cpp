#include "../GoGoClient.h"
#include "../error_codes.h"

#include <gunz/Channel.h>
#include <gunz/ChannelList.h>
#include <gunz/simple_types.h>

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/Parameters.h>
#include <cockpit/packet/protocol/Channel_ResponsePlayerList.h>

#include <algorithm>
#include <cassert>
#include <climits>

using namespace boost;
using namespace cockpit;

// Increments the number unless it's already at max.
inline static uint8_t ceilinged_increment(uint8_t num)
{
	if(num == UCHAR_MAX)
		return num;
	else
		return num + 1;
}

// unlike most of the codebase, this function has indicies starting at 1. It just makes the math easier.
static void add_player_to_player_list(
	packet::blob& playerList,    // The blob we're constructing.
	uint32_t startPlayer,        // The first player in the list to add (inclusive).
	uint32_t endPlayer,          // The last player in the list to add (exclusive).
	size_t& currentPlayer,       // The current player in the list (starts at 0).
	uint8_t& totalPlayerCount,   // A running count of how many players there are. When it hits 255, it just stays there.
	uint32_t& playersAdded,      // The number of players added to the player list.
	gunz::Player* const& player) // The current player!
{
	++currentPlayer;

	totalPlayerCount = ceilinged_increment(totalPlayerCount);

	if(currentPlayer < startPlayer)
		return;

	if(currentPlayer >= endPlayer)
		return;

	playersAdded = ceilinged_increment(playersAdded);

	gunz::Player::Traits traits = player->GetTraits();

	playerList
		.add_param(packet::MUID(traits.muid))
		.add_param(packet::blob_string(traits.characterName.c_str(), 32))
		.add_param(packet::blob_string(traits.clanName.c_str(), 16))
		.add_param(packet::uint8(traits.level))
		.add_param(packet::int32(traits.place))
		.add_param(packet::uint8(traits.ugradeid))
		.add_param(packet::uint8(2))	// usually 2.
		.add_param(packet::int32(traits.clanid))
		.add_param(packet::int32(0))	// emblem?
	;
}

void GoGoClient::OnChannelPlayerList(const gunz::MUID&, const gunz::MUID&, const uint32_t& page)
{
	if(myChannel == NULL)
		return transmitter->disconnect("Tried to request a player list without being in a channel.");

	if(page > UCHAR_MAX)
		return transmitter->disconnect("Tried to access an out-of-bounds page (> 255).");

	packet::blob playerList(0, 71); // The count is set later. 0 is used as a placeholder for now.

	uint8_t totalPlayerCount = 0;
	uint32_t playersAdded = 0;

	{
		size_t currentPlayer = 0;

		//Okay math time....
		//Each page is 6 players , so we start from player [page * 6] and end at player [(page + 1) * 6]
		//So if page is 1, we'd get players 7 - 12
		myChannel->players.CMap(
			bind(add_player_to_player_list,
				ref(playerList),
				page * 6,
				(page + 1) * 6,
				ref(currentPlayer),
				ref(totalPlayerCount),
				ref(playersAdded),
				_1
			)
		);
	}

	playerList.set_count(playersAdded);

	transmitter->send(packet::protocol::Channel_ResponsePlayerList(totalPlayerCount, static_cast<uint8_t>(page), playerList));
}
