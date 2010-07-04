#pragma once
#include <gunz/ChannelTraits.h>

#include <util/SmallVector.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <vector>

namespace gunz {

class MUIDSanta;

class ChannelList : boost::noncopyable
{
private:
	// This keeps the class reentrant, y'all.
	typedef boost::shared_lock<boost::shared_mutex> ReadingLock;
	typedef boost::unique_lock<boost::shared_mutex> WritingLock;
	mutable boost::shared_mutex protection;

	typedef SmallVector<ChannelTraits, 32> CList;
	CList channelList;

	MUIDSanta* santa;

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
	void Announce(const char* sender, const char* message) const;

	~ChannelList();
};

}
