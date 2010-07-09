#pragma once
#include <gunz/detail/PlayerList.h>

namespace gunz {

class Stage
{
public:
	struct Traits
	{
	};

private:
	Traits traits;

public:
	detail::PlayerList players;

public:
	Stage(const Traits& traits);
	Traits GetTraits() const;

	~Stage();
};

}
