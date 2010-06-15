#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/cstdint.hpp>
#include <boost/array.hpp>


namespace cockpit {

class Transmitter;
namespace packet { class Registry; }

/**
	The ClientHandler must be fully implemented by the application using
	cockpit, and contains the core of the game-specific code.
*/
class ClientHandler
{
public:
	/**
		initialize() is called after a connection is make and before any packets
		are exchanged. All this function has to do is register all necessary
		packet handlers with the registry.

		@param socket    The transmitter we will use from now on to send gunz
		                 packets.
		@param registry  The packet::Registry that all packet hooks must be
		                 registered against.
	*/
	virtual void initialize(Transmitter* socket, packet::Registry* registry) = 0;

	/**
		This function performs handshaking with the client (synchronously),
		returing the encryption keys when available.

		@param s      The socket used to read/write the necessary packets to
		              handshake and get valid encryption keys. THIS MUST NOT
		              BE SAVED. Hence, the const-ness of this function.

		@return       The encryption keys.
	*/
	virtual boost::array<boost::uint8_t, 32>
	handshake(boost::asio::ip::tcp::socket& s) const = 0;

	virtual ~ClientHandler()
	{
	}
};

}
