#include "MUIDSanta.h"

using namespace boost;

MUIDSanta::MUIDSanta()
{
	next = 0;
}

MUID MUIDSanta::get()
{
	mutex::scoped_lock(protection);
	return next++;
}

void MUIDSanta::give_back(MUID /*id*/)
{
	// Unimplemented for now... we don't need it. Maybe next week.
}