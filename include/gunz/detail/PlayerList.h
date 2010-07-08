#pragma once
#include <gunz/detail/Collection.h>
#include <vector>

namespace gunz {

class Player;

namespace detail {

typedef Collection<Player*, std::vector<Player*> > PlayerList;

}
}
