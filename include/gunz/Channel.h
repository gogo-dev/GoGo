#pragma once
#include <gunz/detail/Collection.h>
#include <gunz/detail/PlayerList.h>
#include <gunz/simple_types.h>
#include <gunz/Stage.h>

#include <boost/cstdint.hpp>
#include <list>
#include <string>

namespace gunz {

class Channel : public detail::Collection<Stage, std::list<Stage> >
{
public:
	enum Type
	{
		CT_GENERAL,
		CT_PRIVATE,
		CT_USER,
		CT_CLAN
	};

	enum Rule
	{
		CR_NOVICE,
		CR_NEWBIE,
		CR_ROOKIE,
		CR_MASTERY,
		CR_ELITE
	};

	struct Traits
	{
		MUID uid;
		std::string name;
		boost::uint32_t maxPlayers;
		boost::uint32_t playerCount;
		Rule rule;
		Type type;
		boost::uint8_t minLevel;
		boost::uint8_t maxLevel;

		Traits();
		Traits(const Traits& other);

		// Doesn't do anything fancy, it only exists for convenience.
		Traits(MUID uid,
		       const std::string& name,
		       boost::uint32_t maxPlayers,
		       Rule rule,
		       Type type,
		       boost::uint8_t minLevel,
		       boost::uint8_t maxLevel);

		Traits& operator=(const Traits& other);

		bool operator==(const Traits& other) const;

		~Traits();
	};

private:
	Traits traits;
	detail::PlayerList players;

public:
	Channel();
	Channel(const Traits& traits);

	Traits GetTraits() const;

	bool operator==(const Channel& other) const;

	~Channel();
};

}
