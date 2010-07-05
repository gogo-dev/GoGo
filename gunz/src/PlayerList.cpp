#include <gunz/detail/PlayerList.h>
#include <gunz/Player.h>

#include <algorithm>

using namespace boost;

namespace gunz {
namespace detail {

PlayerList::PlayerList()
{
}

PlayerList::PlayerList(const PlayerList& other)
{
	ReadingLock l(other.protection);
	players = other.players;
}

PlayerList& PlayerList::operator=(const PlayerList& other)
{
	ReadingLock l(other.protection);
	players = other.players;

	return *this;
}

PlayerList::~PlayerList()
{
}

void PlayerList::AddPlayer(Player* p)
{
	WritingLock l(protection);
	players.push_back(p);
}

// A nice little optimization to remove over 9000 copies.
static void remove_element(std::vector<Player*>& players, std::vector<Player*>::iterator loc)
{
	std::swap(*loc, *(players.end() - 1));
	players.pop_back();
}

void PlayerList::RemovePlayer(Player* p)
{
	upgrade_lock<shared_mutex> r(protection);

	Roster::iterator loc = std::find(players.begin(), players.end(), p);
	assert(loc != players.end() && "Tried to remove a player that isn't in the list. Wat?");

	upgrade_to_unique_lock<shared_mutex> w(r);
	remove_element(players, loc);
}

PlayerList& PlayerList::map(const boost::function<void (Player* p)>& lambda)
{
	Roster::iterator current, end;

	upgrade_lock<shared_mutex> r(protection);
	current = players.begin();
	end = players.end();

	upgrade_to_unique_lock<shared_mutex> w(r);
	for(; current < end; ++current)
		lambda(*current);

	return *this;
}

void PlayerList::const_map(const boost::function<void (const Player* p)>& lambda) const
{
	ReadingLock r(protection);

	for(Roster::const_iterator current = players.begin(), end = players.end();
	    current != end; ++current)
	{
		lambda(*current);
	}
}

}
}
