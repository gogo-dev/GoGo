#pragma once
#include "Structures.h"
#include <boost/thread/mutex.hpp>
#include <boost/cstdint.hpp>

// This class controls the MUIDs of various in-game objects.
class MUIDSanta
{
private:
	MUID next;	// The "next" MUID to give out.
	boost::mutex protection;	// I always use it.

public:
	MUIDSanta();
	MUID get();
	void give_back(MUID id);
};