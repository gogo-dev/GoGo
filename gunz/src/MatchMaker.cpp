#include <gunz/MatchMaker.h>
#include <gunz/ChannelTraits.h>
#include <gunz/simple_types.h>

#include <util/SmallVector.h>

#include <cstddef>
#include <cassert>
#include <algorithm>

#include <boost/thread/shared_mutex.hpp>

using namespace std;
using namespace boost;

typedef lock_guard<shared_mutex> ExclusiveLock;
typedef shared_lock<shared_mutex> SharedLock;

namespace gunz {

struct MatchMaker::Data
{
	// This mutex protects ALL accesses through MatchMaker. Use it wisely.
	mutable shared_mutex lock;

	SmallVector<ChannelTraits, 32> channels;
	MUIDSanta* santa;
};

MatchMaker::MatchMaker(MUIDSanta* santa)
	: d(new Data)
{
	assert(santa);
	d->santa = santa;
}

void MatchMaker::add_channel(const ChannelTraits& traits)
{
	ExclusiveLock e(d->lock);
	d->channels.push_back(traits);
}

void MatchMaker::remove_channel(MUID muid)
{
	ChannelTraits t;
	t.uid = muid;

	ChannelTraits* location = NULL;
	ChannelTraits* end = NULL;
	{
		SharedLock s(d->lock);
		location = find(d->channels.begin(), (end = d->channels.end()), t);
	}

	assert(location);
	assert(end);

	if(location == NULL || end == NULL || location == end)
		return;

	ExclusiveLock e(d->lock);
	d->channels.erase(location);
}

vector<ChannelTraits> MatchMaker::get_channel_list() const
{
	SharedLock s(d->lock);
	return vector<ChannelTraits>(d->channels.begin(), d->channels.end());
}

MatchMaker::~MatchMaker()
{
	delete d;
}

}
