#pragma once
#include <gunz/detail/Collection.h>
#include <gunz/detail/PlayerList.h>
#include <gunz/Channel.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <list>

namespace gunz {

class ChannelList : boost::noncopyable, public detail::Collection<Channel, std::list<Channel> >
{
private:
	detail::PlayerList players;

public:
	ChannelList();

	~ChannelList();
};

}
