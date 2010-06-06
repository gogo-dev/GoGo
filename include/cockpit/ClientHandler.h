#pragma once

namespace cockpit {

class Transmitter;
namespace packet { class Registry; }

class ClientHandler
{
public:
	virtual void initialize(Transmitter* socket, packet::Registry* registry) = 0;

	virtual ~ClientHandler()
	{
	}
};

}