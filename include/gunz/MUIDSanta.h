#pragma once
#include <gunz/simple_types.h>
#include <boost/thread.hpp>

namespace gunz {

// This class controls the MUIDs of various in-game objects.
class MUIDSanta
{
private:
	volatile MUID next;	// The "next" MUID to give out.
#if defined(_MSC_VER)
	#if (_WIN32_WINNT < 0x0600)
		boost::mutex muidMutex; //For windows.	
	#endif
#endif
public:
	MUIDSanta();
	MUID get();
	void give_back(MUID id);
};

}
