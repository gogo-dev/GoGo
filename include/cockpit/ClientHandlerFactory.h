#pragma once

namespace cockpit {

class ClientHandler;

class ClientHandlerFactory
{
public:
	virtual ClientHandler* create_client_handler() = 0;

	virtual ~ClientHandlerFactory()
	{
	}
};

}