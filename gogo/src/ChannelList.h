#pragma once
#include "Channel.h"

#include <boost/noncopyable.hpp>

#include <util/SmallVector.h>

// TODO(Clark): Flesh this out.
class ChannelList : boost::noncopyable
{
private:
	// By making this read-only, we remove our need for mutexing. The only
	// problem with this, though, is that each channel must now hold their own
	// mutex.
	const SmallVector<Channel, 16> activeChannels;

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
	}

	//

	~ChannelList();
};
