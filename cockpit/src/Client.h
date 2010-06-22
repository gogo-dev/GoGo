#pragma once
#include "Allocator.h"

#include <cockpit/Logger.h>
#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/ClientHandler.h>
#include <cockpit/Transmitter.h>
#include <cockpit/packet/Packet.h>
#include <cockpit/packet/Registry.h>

#include <util/buffer.h>

#include <string>
#include <memory>

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
	std::auto_ptr<ClientHandler> handler;
	packet::Registry registry;
	boost::array<boost::uint8_t, 32> cryptoKey;

	boost::uint8_t currentPacketID;

	bool connected;

	#define KB	*1024
	#define MB	*1024 KB
	#define GB	*1024 MB

	// A temporary storage area for packets as they're processed. This prevents
	// unnecessary heap allocations from taking place, assuming that the total
	// requested memory is less than the provided size. Oh, and if it ever goes
	// above that, no biggie - the allocation will be passed onto the system
	// malloc.
	typedef Allocator<8 KB> PacketAllocator;
	PacketAllocator packetPool;

	#undef GB
	#undef MB
	#undef KB

public:
	boost::asio::ip::tcp::socket socket;

	void recieve_packet_header();
	void on_packet_header(
		PacketHeader* rawPacket,
		boost::system::error_code err,
		size_t bytesTransferred
	);

	void recieve_payload(boost::uint16_t fullPacketLength, bool encrypted);
	void on_payload(
		boost::uint8_t* payload,
		boost::uint16_t payloadSize,
		bool encrypted,
		boost::system::error_code err,
		size_t bytesTransferred
	);

	void on_send(
		boost::system::error_code err,
		size_t bytesTransferred,
		boost::uint8_t* buf,
		size_t packetLength
	);

public:
	Client(Logger* logger, ClientHandlerFactory* factory, boost::asio::io_service* io);

	void start();

	void send(const packet::Packet& packet, bool encrypted);

	void disconnect();

	std::string get_ip() const;

	~Client();
};

}
