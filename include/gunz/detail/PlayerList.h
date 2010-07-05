#pragma once
#include <boost/function.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <vector>

namespace gunz {

class Player;

namespace detail {

class PlayerList
{
private:
	// This keeps the class reentrant, y'all.
	typedef boost::shared_lock<boost::shared_mutex> ReadingLock;
	typedef boost::unique_lock<boost::shared_mutex> WritingLock;
	mutable boost::shared_mutex protection;

	typedef std::vector<Player*> Roster;
	Roster players;

public:
	PlayerList();
	PlayerList(const PlayerList& other);
	PlayerList& operator=(const PlayerList& other);
	~PlayerList();

	void AddPlayer(Player* p);
	void RemovePlayer(Player* p);

	// Maps a function over every valid player. You are allowed to call
	// non-const functions on the player with this function. If you only need
	// access to const functions, consider using const_map.
	PlayerList& map(const boost::function<void (Player* p)>& lambda);

	// Maps a function over every valid player. You are prohibited from calling
	// non-const functions on the player with this function. If you require
	// access to non-const function, use map instead.
	void const_map(const boost::function<void (const Player* p)>& lambda) const;
};

}
}
