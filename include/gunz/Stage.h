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
	detail::PlayerList players;
	Traits traits;

public:
	// TODO: Is a default constructor necessary?
	Stage();
	Stage(const Traits& traits);
	Traits GetTraits() const;

	~Stage();
};

}
