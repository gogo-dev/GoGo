#include "../GoGoClient.h"
#include "../error_codes.h"

#include <gunz/Channel.h>
#include <gunz/ChannelList.h>
#include <gunz/detail/Collection.h>
#include <gunz/simple_types.h>

#include <cockpit/Logger.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/Parameters.h>
#include <cockpit/packet/protocol/Channel_ResponseJoin.h>
#include <boost/format.hpp>
using namespace std;
using namespace boost;
using namespace cockpit;


bool IsRecommandedChannel(const CharacterInfo& myCharacter, const gunz::Channel& channel)
{
	const gunz::Channel::Traits& traits = channel.GetTraits();
	return (traits.maxLevel >= myCharacter.CharacterLevel && traits.minLevel <= myCharacter.CharacterLevel &&
		traits.maxPlayers < channel.players.Length() && myCharacter.ClanId == 0);
}

bool IsFirstChannel (const gunz::Channel& channel)
{
	return true;
}
void GoGoClient::OnRecommandedChannel()
{
	myChannel = channelList->Find(boost::bind(&IsRecommandedChannel, myCharacter, _1));

	if (myChannel == NULL)
	{
		myChannel = channelList->Find(boost::bind(&IsFirstChannel, _1));
	}

	myChannel->players.Add(this);
	gunz::Channel::Traits& traits = myChannel->GetTraits();
	logger->info (boost::format("Channel UID: %1%") % traits.uid);
	
	packet::MUID channelId(traits.uid);
	packet::int32 channelType(traits.type);
	packet::string channelName(traits.name);
	packet::boolean unknown(true);
	
	transmitter->send(packet::protocol::Channel_ResponseJoin (channelId, channelType, channelName, unknown));
}
