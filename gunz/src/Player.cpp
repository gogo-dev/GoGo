#include <gunz/Player.h>
#include <boost/thread/locks.hpp>

using namespace boost;

namespace gunz {

Player::Traits::Traits(MUID _muid, const std::string& _characterName, const std::string& _clanName, boost::uint8_t _level, MatchPlace _place, boost::uint8_t _ugradeid, boost::uint32_t _clanid)
	: muid(_muid),
	  clanid(_clanid),
	  place(_place),
	  characterName(_characterName),
	  clanName(_clanName),
	  level(_level),
	  ugradeid(_ugradeid)
{
}

Player::Traits::~Traits()
{
}

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
