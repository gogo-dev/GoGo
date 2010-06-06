#pragma once
#include <boost/asio/ip/tcp.hpp>

namespace cockpit {

namespace packet {
	class Packet;
	class Registry;
}

class Socket
{
private:
	packet::Registry* registry;

public:
	Socket(boost::asio::io_service* io);

	void set_registry(packet::Registry* registry);

	void begin();
	void disconnect();

	boost::asio::ip::tcp::socket& get_raw();

	void send(const packet::Packet* packet);

	~Socket();
};

}