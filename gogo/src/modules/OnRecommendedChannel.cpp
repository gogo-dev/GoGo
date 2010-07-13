#include "../GoGoClient.h"
#include "../error_codes.h"

#include <gunz/Channel.h>
#include <gunz/ChannelList.h>
#include <gunz/simple_types.h>

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/Parameters.h>
#include <cockpit/packet/protocol/Channel_ResponseJoin.h>

#include <cassert>

using namespace std;
using namespace boost;
using namespace cockpit;

static bool IsRecommandedChannel(const CharacterInfo& myCharacter, const gunz::Channel& channel)
{
	gunz::Channel::Traits traits = channel.GetTraits();

	return traits.maxLevel >= myCharacter.CharacterLevel
	    && traits.minLevel <= myCharacter.CharacterLevel
	    && traits.maxPlayers < channel.players.Length()
	    && myCharacter.ClanId == 0;
}

static bool IsFirstChannel(const gunz::Channel&)
{
	return true;
}

void GoGoClient::OnRecommendedChannel()
{
	myChannel = channelList->Find(boost::bind(&IsRecommandedChannel, myCharacter, _1));

	if (myChannel == NULL)
	{
		myChannel = channelList->Find(boost::bind(&IsFirstChannel, _1));
		assert(myChannel);
	}

	myChannel->players.Add(this);
	gunz::Channel::Traits traits = myChannel->GetTraits();

	packet::MUID channelId(traits.uid);
	packet::int32 channelType(traits.type);
	packet::string channelName(traits.name);
	packet::boolean unknown(true);

	myPlace = gunz::MP_LOBBY;
	transmitter->send(packet::protocol::Channel_ResponseJoin (channelId, channelType, channelName, unknown));
}
