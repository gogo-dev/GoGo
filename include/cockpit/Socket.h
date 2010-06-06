#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/cstdint.hpp>

namespace cockpit {

namespace packet { class Packet; }

class Socket
{
private:
	packet::Registry* registry;
	boost::asio::ip::tcp::socket raw;

	/**
		When this mutex is locked, the socket is NOT running, when it is
		unlocked, the socket IS running. This is used as a nice easy way to
		handle when begin() should return - it just waits for the mutex!
	*/
	boost::mutex socket_terminated;

	void signal_termination();
	void wait_for_termination();

	/**
		Use this to get the Packet ID of the "next" packet. Basically a
		counter that can be thought of as a thread-safe equivelent to
		static uint8_t next; return ++next;
	*/
	boost::uint8_t next_packet();

	boost::mutex packetidLock;
	boost::uint8_t currentPacketID;

public:
	/**
		Constructs a new connection to a client, using "io" as our io service.
		Please note that the socket doesn't actually lead anywhere until an
		accept function is called on this->get_raw().

		@throws Nothing.
	*/
	Socket(boost::asio::io_service* io);

	/**
		Sets the packet registry this socket will use. Each socket may use one
		and only one packet registry. The registry in use will be that which
		is the parameter used while calling this function last.

		@throw Nothing.
	*/
	void set_registry(packet::Registry* registry);

	/**
		Starts the event pump for the socket's connection. Whenever a packet is
		recieved, it will be dispatched to the packet::Registry instance that
		was set with set_registry. When the connection to the client is
		terminated, begin() returns. Until that happens, begin() will block.

		@throw Nothing.
	*/
	void begin();

	/**
		Immediately terminates the event pump for the socket's connection. Any
		asynchronous requests will be dropped, and the begin() function will be
		signaled to return.

		@throw Nothing.
	*/
	void disconnect();

	/**
		A convenience function to use the raw boost::socket for recieving
		the connection into. This is just mostly needed by MatchServer.

		@throw Nothing.
		@return The internal, raw socket.
	*/
	boost::asio::ip::tcp::socket& get_raw();

	/**
		Sends a raw packet across the 'net to our client. It is assumed you are
		already connected to the client.
	*/
	void send(const packet::Packet* packet);

	~Socket();
};

}
