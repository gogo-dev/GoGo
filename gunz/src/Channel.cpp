#include <gunz/Channel.h>

namespace gunz {

Channel::Traits::Traits()
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

Channel::Traits::Traits(const Channel::Traits& other)
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

Channel::Traits::Traits(
	MUID _uid,
	const std::string& _name,
	boost::uint8_t _maxPlayers,
	Channel::Rule _rule,
	Channel::Type _type,
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

Channel::Traits& Channel::Traits::operator=(const Channel::Traits& other)
{
	uid = other.uid;
	name = other.name;
	maxPlayers = other.maxPlayers;
	playerCount = other.playerCount;
	rule = other.rule;
	type = other.type;
	minLevel = other.minLevel;
	maxLevel = other.maxLevel;

	return *this;
}

// We take a little shortcut here. Instead of doing a whole wack of unnecessary
// comparisons, we just compare UIDs. This is totally cheating, but I don't care.
bool Channel::Traits::operator==(const Channel::Traits& other) const
{
	return uid == other.uid;
}

Channel::Traits::~Traits()
{
}

Channel::Channel(const Traits& _traits)
	: traits(_traits)
{
}

Channel::Traits Channel::GetTraits() const
{
	return traits;
}

bool Channel::operator==(const Channel& other) const
{
	return traits == other.traits;
}

Channel::~Channel()
{
}

}
