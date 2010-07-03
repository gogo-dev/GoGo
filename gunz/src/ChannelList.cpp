#include <gunz/ChannelList.h>

#include <boost/bind.hpp>

using namespace std;
using namespace boost;

namespace gunz {

ChannelList::ChannelList()
{
}

void ChannelList::AddChannel(const ChannelTraits& toAdd)
{
	WritingLock l(protection);
	channelList.push_back(toAdd);
}

bool ChannelList::RemoveChannel(MUID channelID)
{
	upgrade_lock<shared_mutex> upgradable(protection);

	// If you can think of same way to functionally factor out this loop,
	// that would be great. Predicates would be nice :(
	for(CList::iterator i = channelList.begin(), e = channelList.end();
	    i != e; ++i)
	{
		if(i->uid == channelID)
		{
			upgrade_to_unique_lock<shared_mutex> uniq(upgradable);
			channelList.erase(i);

			// The loop MUST NOT BE CONTINUED. We just invalidated the iterator.
			return true;
		}
	}

	return false;
}

ChannelTraits ChannelList::LookupChannel(const function<bool (const ChannelTraits&)>& predicate) const
{
	ReadingLock l(protection);

	for(CList::const_iterator i = channelList.begin(), e = channelList.end();
	    i != e; ++i)
	{
		if(predicate(*i))
			return *i;
	}

	return ChannelTraits(0, "", 0, CR_ELITE, CT_GENERAL, 0, 0);
}

vector<ChannelTraits> ChannelList::GetChannelList() const
{
	ReadingLock l(protection);
	return vector<ChannelTraits>(channelList.begin(), channelList.end());
}

ChannelList::~ChannelList()
{
}

}
