#include <gunz/Player.h>
#include <boost/thread/locks.hpp>

using namespace boost;

namespace gunz {

Player::Player(const Traits& _traits)
	: traits(_traits)
{
}

Player::Traits Player::GetTraits() const
{
	shared_lock<shared_mutex> r(protection);
	return traits;
}

void Player::ModifyTraits(const function<void (Traits&)>& modifier)
{
	unique_lock<shared_mutex> w(protection);
	modifier(traits);
}

}
