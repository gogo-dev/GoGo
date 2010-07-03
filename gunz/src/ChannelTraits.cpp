#include <gunz/ChannelTraits.h>

using namespace std;
using namespace boost;

namespace gunz {

ChannelTraits::ChannelTraits()
	: uid(0),
	  name("<<unnamed>>"),
	  maxPlayers(0),
	  playerCount(0),
	  rule(CR_ELITE),
	  type(CT_GENERAL),
	  minLevel(0),
	  maxLevel(0)
{
}

ChannelTraits::ChannelTraits(const ChannelTraits& other)
	: uid(other.uid),
	  name(other.name),
	  maxPlayers(other.maxPlayers),
	  playerCount(0),
	  rule(other.rule),
	  type(other.type),
	  minLevel(other.minLevel),
	  maxLevel(other.maxLevel)
{
}

ChannelTraits::ChannelTraits(
	MUID _uid,
	const std::string& _name,
	boost::uint32_t _maxPlayers,
	ChannelRule _rule,
	ChannelType _type,
	boost::uint8_t _minLevel,
	boost::uint8_t _maxLevel)
	  : uid(_uid),
	    name(_name),
	    maxPlayers(_maxPlayers),
	    playerCount(0),
	    rule(_rule),
	    type(_type),
	    minLevel(_minLevel),
	    maxLevel(_maxLevel)
{
}

ChannelTraits& ChannelTraits::operator=(ChannelTraits other)
{
	std::swap(other, *this);
	return *this;
}

// The following two functions depend on the uniquity of uids.
bool ChannelTraits::operator<(const ChannelTraits& other) const
{
	return uid < other.uid;
}

bool ChannelTraits::operator==(const ChannelTraits& other) const
{
	return uid == other.uid;
}

ChannelTraits::~ChannelTraits()
{
}

}
