#include <gunz/ChannelList.h>
#include <gunz/MUIDSanta.h>
#include <gunz/Player.h>

#include <boost/bind/bind.hpp>

using namespace std;
using namespace boost;

namespace gunz {

ChannelList::ChannelList(MUIDSanta* _santa)
	: santa(_santa)
{
}

void ChannelList::Join(Player* player)
{
	players.Add(player);
}

void ChannelList::Leave(Player* player)
{
	players.Remove(player);
}

void ChannelList::AddChannel(ChannelTraits toAdd)
{
	toAdd.uid = santa->get();
	channelList.Add(toAdd);
}

bool ChannelList::RemoveChannel(MUID channelID)
{
	// Only MUIDs are compared, so we stub out the rest.
	return channelList.Remove(ChannelTraits(channelID, "", 0, CR_NEWBIE, CT_GENERAL, 0, 0));
}

ChannelTraits ChannelList::LookupChannel(const function<bool (const ChannelTraits&)>& predicate) const
{
	const ChannelTraits* result = channelList.find(predicate);

	if(result)
		return *result;
	else
		return ChannelTraits(0, "", 0, CR_NEWBIE, CT_GENERAL, 0, 0);
}

static void build_vector(vector<ChannelTraits>& vec, const ChannelTraits& newElem)
{
	vec.push_back(newElem);
}

vector<ChannelTraits> ChannelList::GetChannelList() const
{
	vector<ChannelTraits> ret;
	ret.reserve(channelList.length());
	channelList.cmap(bind(build_vector, ref(ret), _1));
	return ret;
}

void ChannelList::Announce(const char* sender, const char* message)
{
	players.map(bind(&Player::OnMessage, _1, MT_ANNOUNCE, sender, message));
}

ChannelList::~ChannelList()
{
}

}
