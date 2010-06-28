#pragma once
#include <gunz/Channel.h>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

#include <algorithm>
#include <vector>

#include <util/SmallVector.h>

namespace gunz {

class ChannelList : boost::noncopyable
{
private:
	typedef SmallVector<Channel, 16> CList;
	// By making this read-only, we remove our need for mutexing. The only
	// problem with this, though, is that each channel must now hold their own
	// mutex.
	CList activeChannels;

	// Provides a nice easy way to access all the channels in activeChannels,
	// without having to know how they're stored.
	std::vector<Channel*> shortcut;

public:
	/**
		Constructs a channel list from a container of any type, by passing in
		that container's iterators. NOTE: It MUST be a container of Channel. I
		don't know why I have to explicitly mention that, but I like to think
		it's good to know.
	*/
	template <typename IteratorType>
	ChannelList(const IteratorType& begin, const IteratorType& end)
		: activeChannels(begin, end)
	{
		shortcut.reserve(activeChannels.size());
		for(CList::iterator i = activeChannels.begin(), end = activeChannels.end(); i != end; ++i)
			shortcut.push_back(&(*i));
	}

	/**
		Returns a vector of channels for every channel for which the predicate
		holds.

		@param  predicate When this returns true, the parameter will be one of
		                  the returned channels.

		@return A full list of every channel for which the predicate held true.
	*/
	std::vector<const Channel*> get_some(boost::function<bool (const Channel*)> predicate) const;

	/// Returns pointers to every single channel. Please try to avoid using
	/// this function in favor of get() as much as possible.
	const std::vector<Channel*>* get_all() const;

	~ChannelList();
};

}
