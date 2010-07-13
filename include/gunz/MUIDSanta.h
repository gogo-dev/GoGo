#pragma once
#include <gunz/simple_types.h>

#include <platform.h>

namespace gunz {

// This class controls the MUIDs of various in-game objects.
class MUIDSanta
{
private:
	SynchronizedInteger(next);

public:
	MUIDSanta();
	MUID get();
	void give_back(MUID id);
};

}
