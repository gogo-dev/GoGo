#pragma once

namespace cockpit {

class Socket;
namespace packet { class Registry; }

class ClientHandler
{
public:
	virtual void initialize(Socket* socket, packet::Registry* registry) = 0;

	virtual ~ClientHandler()
	{
	}
};

}