#pragma once
#include <gunz/simple_types.h>

namespace gunz {

/**
	A player represents a single entity in the gunz library. Pointers to
	players are basically the only communication with the outside world that
	the gunz library has.
*/
class Player
{
public:
	/**
		This callback is called when the player has recieved a message from any
		other player. This function must be reentrant, as other players could
		be chatting in potentially infinite threads.
	*/
	virtual void OnMessage(MessageType type, const char* sender, const char* message) = 0;
};

}
