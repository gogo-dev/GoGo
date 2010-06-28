#include <gunz/PlayerTraits.h>

using namespace std;
using namespace boost;

namespace gunz {

PlayerTraits::PlayerTraits()
{
}

PlayerTraits::PlayerTraits(
	MUID _muid,
	const std::string& _name,
	const std::string& _clanName,
	boost::uint8_t _level,
	PlayerTraits::PlayerLocation _location,
	boost::uint8_t _ugradeid,
	boost::int32_t _clanid)
	: muid(_muid), name(_name), clanName(_clanName), level(_level),
	  location(_location), ugradeid(_ugradeid), clanid(_clanid)
{
}

PlayerTraits::~PlayerTraits()
{
}

}
