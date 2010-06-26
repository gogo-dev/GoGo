#pragma once
#include "Structures.h"

// This class controls the MUIDs of various in-game objects.
class MUIDSanta
{
private:
	volatile MUID next;	// The "next" MUID to give out.

public:
	MUIDSanta();
	MUID get();
	void give_back(MUID id);
};
