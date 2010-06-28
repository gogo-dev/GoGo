#include <gunz/ChannelTraits.h>

using namespace std;
using namespace boost;

namespace gunz {

ChannelTraits::ChannelTraits()
	: uid(0),
	  name("<<unnamed>>"),
	  maxPlayers(200),
	  rule(CR_ELITE),
	  type(CT_GENERAL),
	  minLevel(0),
	  maxLevel(255)
{
}

ChannelTraits::ChannelTraits(
	MUID _uid,
	const string& _name,
	uint32_t _maxPlayers,
	ChannelRule _rule,
	ChannelType _type,
	uint8_t _minLevel,
	uint8_t _maxLevel)
	: uid(_uid),
	  name(_name),
	  maxPlayers(_maxPlayers),
	  rule(_rule),
	  type(_type),
	  minLevel(_minLevel),
	  maxLevel(_maxLevel)
{
}

ChannelTraits::ChannelTraits(const ChannelTraits& other)
	: uid(other.uid),
	  name(other.name),
	  maxPlayers(other.maxPlayers),
	  rule(other.rule),
	  type(other.type),
	  minLevel(other.minLevel),
	  maxLevel(other.maxLevel)
{
}

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
