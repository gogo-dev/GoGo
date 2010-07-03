#pragma once
#include <gunz/ChannelTraits.h>

#include <util/SmallVector.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <vector>

namespace gunz {

class ChannelList : boost::noncopyable
{
private:
	// This keeps the class reentrant, y'all.
	typedef boost::shared_lock<boost::shared_mutex> ReadingLock;
	typedef boost::unique_lock<boost::shared_mutex> WritingLock;
	mutable boost::shared_mutex protection;

	typedef SmallVector<ChannelTraits, 32> CList;
	CList channelList;

public:
	ChannelList();

	void AddChannel(const ChannelTraits& toAdd);

	// This is usually superfluous, as channels are automatically removed when
	// they are empty (except for general channels).
	bool RemoveChannel(MUID channelID);

	/**
		Looks up a channel by doing a simple linear search. When predicate
		returns true, a copy of the channel that the predicate found is
		returned. If the channel is not found, the resultant ChannelTraits
		will have a UID of 0.
	*/
	ChannelTraits LookupChannel(const boost::function<bool (const ChannelTraits&)>& predicate) const;

	std::vector<ChannelTraits> GetChannelList() const;

	~ChannelList();
};

}
