#pragma once
#include <gunz/ChannelTraits.h>
#include <gunz/detail/PlayerList.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

namespace gunz {

class MUIDSanta;
class Player;

class ChannelList : boost::noncopyable
{
	friend class Channel;

private:
	MUIDSanta* santa;

	detail::Collection<ChannelTraits> channelList;
	detail::PlayerList players;

	// This is just to help out Channel populate the... populations!
private:
	void Join(Player* player);
	void Leave(Player* player);

public:
	ChannelList(MUIDSanta* santa);

	/**
		Adds a new, empty channel to the channel list. Interesting side-effect,
		if no one ever joins this channel, it will stick around forever.
	*/
	void AddChannel(ChannelTraits toAdd);

	/**
		This function is usually unneeded, as channels are automatically
		removed when they are empty (except for general channels).
	*/
	bool RemoveChannel(MUID channelID);

	/**
		Looks up a channel by doing a simple linear search. When predicate
		returns true, a copy of the channel that the predicate found is
		returned. If the channel is not found, the resultant ChannelTraits
		will have a UID of 0.

		@see http://en.wikipedia.org/wiki/Predicate_(mathematical_logic)
	*/
	ChannelTraits LookupChannel(const boost::function<bool (const ChannelTraits&)>& predicate) const;

	/**
		Returns a snapshot of the current channels currently alive.
	*/
	std::vector<ChannelTraits> GetChannelList() const;

	/**
		Broadcasts a message to everyone in ALL channels. Any validation such
		as "is this person an admin?" should be done elsewhere.
	*/
	void Announce(const char* sender, const char* message);

	~ChannelList();
};

}
