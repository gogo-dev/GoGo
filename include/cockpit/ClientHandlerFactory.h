#pragma once
#include <memory>

namespace cockpit {

class ClientHandler;

/**
	The client handler factory is an implementation of the "Factory" design
	pattern: http://en.wikipedia.org/wiki/Factory_method_pattern. This class is
	used to fulfill requests for new ClientHandlers, whenever a client connects.
*/
class ClientHandlerFactory
{
public:
	/**
		This is called whenever a client connects, and must create a valid
		ClientHandler.

		@return A valid ClientHandler.
	*/
	virtual std::auto_ptr<ClientHandler> create_client_handler() = 0;

	virtual ~ClientHandlerFactory()
	{
	}
};

}
