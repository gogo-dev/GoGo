#pragma once
#include <gunz/detail/Collection.h>

#include <boost/cstdint.hpp>

#include <vector>

namespace gunz {

class Player;

namespace detail {

class PlayerList : public Collection<Player*, std::vector<Player*> >
{
public:
	// Since player lists are required to always be less than or equal to 255
	// players, we cheat a little bit. If it IS above, this function just
	// rounds down to 255 and returns that.
	boost::uint8_t Length() const;
};

}
}
