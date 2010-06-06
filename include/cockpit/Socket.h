#pragma once

namespace cockpit {

namespace packet { class Packet; }

class Socket
{
public:
	Socket();

	void begin();
	void disconnect();

	void send(const packet::Packet* packet);

	~Socket();
};

}
