#pragma once
#include <string>

namespace cockpit {

namespace packet { class Packet; }

/**
	The Transmitter class acts as an interface to the ClientHandler's so they
	may react accordingly to recieved packets, sending appropriate responses.
	If responses need to be processed, just hook the handler.
*/
class Transmitter
{
public:
	/**
		Sends a raw packet across the 'net to our client. It is assumed you are
		already connected to the client.

		@param packet A pointer to a valid packet to send.
	*/
	virtual void send(const packet::Packet& packet) = 0;

	/**
		Disconnects the client. No more handlers will be called, the
		connection will be terminated, and eventually, the ClientHandler's
		destructor will be called.
	*/
	virtual void disconnect() = 0;

	/**
		Gets the target's IP address, in the form of 127.0.0.1.

		@return  The connection's IP address.
	*/
	virtual std::string get_ip() const = 0;

	virtual ~Transmitter()
	{
	}
};

}
