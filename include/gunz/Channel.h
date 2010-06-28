#pragma once
#include <gunz/simple_types.h>

namespace gunz {

// TODO(Clark): Flesh this out.
class Channel
{
public:
	/*
		NECESSARY METHODS:
			+ void Join(Player*)
				- Adds the player to the current channel list, ensuring they
				  recieve updates for chats.

			+ void Leave(Player*)
				- Removes the player from the channel list. They will no longer
				  recieve chat updates.

			+ void Chat(Player* speaker, const char* message)
				- Sends a chat message to the whole channel, from "speaker".

			+ ChannelRule GetRule() const
				- Returns the "rule" for the channel. I'm still not totally
				  sure what this means. Talk to Jacob.

			+ ChannelType GetType() const
				- Returns whether the channel is one of CT_GENERAL, CT_PRIVATE,
				  CT_USER, or CT_CLAN.

			+ std::vector<PlayerTraits> GetPlayerList() const
				- Returns a player list, return information on each player
				  currently in the channel. The reason raw Player*s aren't used
				  is that the answer to this question can't be answered:
				  "What happens if a player disconnects and is deleted?"

			+ Stage* CreateStage(Player* stageMaster, const std::string& name, const std::string& password)
				- Creates a stage with the name and password. If the password
				  is blank, the stage is considered open. A pointer to the
				  newly created stage is then returned. stageMaster is
				  automagically added to the stage as the stageMaster.

			+ Stage* JoinStage(MUID stageID, const std::string& password)
				- Joins a stage with the requested name and password. Returns
				  NULL if the stageID isn't valid, or the password doesn't
				  match.

			+ Stage* JoinRandomStage()
				- Returns a valid stage that the player will be placed in.
				  Password-protected and full stages are skipped. If a valid
				  stage cannot be found, NULL is returned.

		DEPENDENCIES:
			PlayerTraits
			Player
			Stage
	*/
};

}
