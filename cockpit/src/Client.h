#pragma once
#include <cockpit/Logger.h>
#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/Packet.h>
#include <cockpit/packet/Registry.h>

#include <util/buffer.h>

#include <string>

#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/cstdint.hpp>
#include <boost/thread/mutex.hpp>

namespace cockpit {

class Client : public Transmitter, public boost::enable_shared_from_this<Client>
{
public:
	struct PacketHeader;
	struct PayloadHeader;

private:
	Logger* logger;
	ClientHandler* handler;
	packet::Registry registry;
	boost::array<boost::uint8_t, 32> cryptoKey;

	boost::uint8_t currentPacketID;

	bool connected;

public:
	boost::asio::ip::tcp::socket socket;

	void recieve_packet_header();
	void on_packet_header(
		boost::shared_ptr<PacketHeader> rawPacket,
		boost::system::error_code err,
		size_t bytesTransferred
	);

	void recieve_payload(boost::uint16_t fullPacketLength, bool encrypted);
	void on_payload(
		boost::shared_array<boost::uint8_t> payload,
		boost::uint16_t payloadSize,
		bool encrypted,
		boost::system::error_code err,
		size_t bytesTransferred
	);

	void on_send(
		boost::system::error_code err,
		size_t bytesTransferred,
		boost::shared_array<boost::uint8_t> buf,
		size_t packetLength
	);

public:
	Client(Logger* logger, ClientHandlerFactory* factory, boost::asio::io_service* io);

	void start();

	void send(const packet::Packet& packet);

	void disconnect();

	std::string get_ip() const;

	~Client();
};

}
