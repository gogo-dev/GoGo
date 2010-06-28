#include <gunz/ChannelList.h>

using namespace std;
using namespace boost;

namespace gunz {

vector<const Channel*> ChannelList::get_some(function<bool (const Channel*)> predicate) const
{
	vector<const Channel*> ret(activeChannels.size());

	for(CList::const_iterator i = activeChannels.begin(), end = activeChannels.end(); i != end; ++i)
	{
		const Channel* current = &(*i);	// That's right!
		if(predicate(current))
			ret.push_back(current);
	}

	return ret;
}

const vector<Channel*>* ChannelList::get_all() const
{
	return &shortcut;
}

ChannelList::~ChannelList()
{
}

}
