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
	// Unimplemented for now... we don't need it until the number of clients
	// exceeds 2^64. In order for that to happen, the entire population of
	// the world would need to connect 2.75 * 10^9 times. And even then, this
	// algorithm won't generate any collisions unless there's been someone
	// on from the very beginning. Suffice to say, there's no pressing need
	// to make this algorithm "right", or any more complex until a bug report
	// is filed.
}