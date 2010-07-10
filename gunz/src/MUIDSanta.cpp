#include <gunz/MUIDSanta.h>

#if defined(_MSC_VER)
	#include <windows.h>
#endif

namespace gunz {

MUIDSanta::MUIDSanta()
	: next(1)	// Gunz doesn't like it when we give out MUIDs of 0.
{
}

MUID MUIDSanta::get()
{
// TODO(Clark): Move this ugly #ifdef hell out into an "atomics" library of sorts.
#if defined(__GNUC__) || defined(__clang__)
	return __sync_fetch_and_add(&next, 1);
#elif defined(_MSC_VER)
	return InterlockedIncrement((LONG*)&next);
#else
	#error "Unsupported platform! Please write your own lock-free increment."
#endif
}

void MUIDSanta::give_back(MUID /*id*/)
{
	// Unimplemented for now... we don't need it until the number of clients
	// exceeds 2^64. In order for that to happen, the entire population of
	// the world would need to connect 2.75 * 10^9 times EACH. And even then,
	// this algorithm won't generate any collisions unless there's been someone
	// on from the very beginning. Suffice to say, there's no pressing need
	// to make this algorithm "right", or any more complex until a bug report
	// is filed.
}

}
