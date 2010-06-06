#include <cockpit/Socket.h>

#include "packet/crypto.h"

#include <cockpit/packet/Packet.h>
#include <cockpit/Logger.h>

#include <util/memory.h>

#include <cstddef>

#include <boost/asio.hpp>
#include <boost/format.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace {

struct packet_header
{
	uint16_t version;
	uint16_t size;
	uint16_t checksum;
	uint16_t id;
	uint8_t counter;
};

}

namespace cockpit {

Socket::Socket(io_service* io)
	: registry(NULL), raw(*io)
{
	currentPacketID = 0;
}

void Socket::signal_termination()
{
	socket_terminated.unlock();
}

void Socket::wait_for_termination()
{
	socket_terminated.lock();
}

void Socket::set_registry(packet::Registry* _registry)
{
	registry = _registry;
}

void Socket::begin()
{
	// Perform handshake

	// Enter main loop
		// Recieve packet
		// Decrypt packet
		// dispatch packet

	wait_for_termination();
}

void Socket::disconnect()
{
	try {
		raw.shutdown(tcp::socket::shutdown_both);
		raw.close();
	} catch(system::system_error) {
	}

	signal_termination();
}

tcp::socket& Socket::get_raw()
{
	return raw;
}

uint8_t Socket::next_packet()
{
	mutex::scoped_lock guard(packetidLock);
	return ++currentPacketID;
}

static void fix_checksum(uint8_t* packet, size_t len)
{
	uint16_t sum = packet::checksum(packet, len);
	memory::copy(packet + 2*sizeof(uint16_t), &sum, sizeof(sum));
}

static void make_packet(Buffer& outBuffer, const packet_header& header, const Buffer& parameters)
{
	uint8_t* buf = outBuffer.data();
	buf = memory::pcopy(buf, &header, sizeof(header));
	memory::copy(buf, parameters.data(), parameters.length());

	fix_checksum(outBuffer.data(), outBuffer.length());
}

void Socket::send(const packet::Packet* packet)
{
	Buffer packetData = packet->serialize();

	// If the packet is too large to send, just drop it quietly.
	if(sizeof(packet_header) + packetData.length())
		return;

	Buffer toSend(sizeof(packet_header) + packetData.length());

	packet_header packetHeader = {
		0x64,	// Unencrypted.
		static_cast<uint16_t>(sizeof(packet_header) + packetData.length()),
		0x00,	// Temporary value until fix_checksum is called.
		packet->id(),
		next_packet()
	};

	make_packet(toSend, packetHeader, packetData);

	try {
		raw.send(buffer(toSend.data(), toSend.length()));
	} catch(system::system_error) {
		disconnect();
	}
}

}