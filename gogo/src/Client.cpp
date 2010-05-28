#include "Client.h"
#include <boost/format.hpp>
#include <util/memory.h>

using namespace boost;

Client::Client(Logger* _logger, asio::io_service &service, MUIDSanta* _santa)
	: socket(service), logger(_logger), santa(_santa)
{
	memory::set(cryptkey, 0x00, sizeof(cryptkey));
	clientid = santa->get();
}

void Client::start()
{
	logger->info(
		format("Incoming connection from [%1%], MUID = %2%.")
			% socket.remote_endpoint().address().to_string()
			% clientid
	);

	send_handshake();
}

Handshake &Client::GetHandshake(std::string ip, boost::uint64_t clientid)
{
	uint32_t tempValues[3] = { 0 };
	boost::asio::io_service io;
	boost::asio::ip::tcp::socket socket(io);
	uint8_t cryptkey[32] = { 0 };
	
	uint8_t* cryptkeyPtr = cryptkey;
	Handshake handshake(1, clientid);

	//Static client keys.
	uint8_t IV[2][16] = {
		{
			0x37, 0x04, 0x5D, 0x2E, 0x43, 0x3A, 0x49, 0x53,
			0x50, 0x05, 0x13, 0xC9, 0x28, 0xA4, 0x4D, 0x05
		},
		{
			0x57, 0x02, 0x5B, 0x04, 0x34, 0x06, 0x01, 0x08,
			0x37, 0x0A, 0x12, 0x69, 0x41, 0x38, 0x0F, 0x78
		}
	};

	//Crypt key creation.
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, &handshake.Timestamp, 4);
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, &handshake.ServerId, sizeof(boost::uint32_t));
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, &clientid, sizeof(clientid));
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, IV, sizeof(IV[0]));

	for (int i = 0; i < 4; ++i)
	{
		memory::copy(tempValues, IV[1]+(i*4), sizeof(uint32_t));
		memory::copy(tempValues + 1, cryptkey+(i*sizeof(uint32_t)), sizeof(uint32_t));
		tempValues[2] = tempValues[0] ^ tempValues[1];
		memory::copy(cryptkey+(i*4), tempValues + 2 ,sizeof(uint32_t));
	}

	return handshake;
}
void Client::send_handshake()
{
	uint32_t tempValues[3] = { 0 };
	uint8_t* cryptkeyPtr = cryptkey;
	Handshake handshake(1, clientid);
	uint8_t packet[26] = {0};
	uint8_t* packetPtr = packet;

	//Static client keys.
	uint8_t IV[2][16] = {
		{
			0x37, 0x04, 0x5D, 0x2E, 0x43, 0x3A, 0x49, 0x53,
			0x50, 0x05, 0x13, 0xC9, 0x28, 0xA4, 0x4D, 0x05
		},
		{
			0x57, 0x02, 0x5B, 0x04, 0x34, 0x06, 0x01, 0x08,
			0x37, 0x0A, 0x12, 0x69, 0x41, 0x38, 0x0F, 0x78
		}
	};

	//Crypt key creation.
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, &handshake.Timestamp, 4);
	
	//TODO: Fix the order of this...
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, &handshake.ServerId, sizeof(boost::uint32_t));
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, &clientid, sizeof(clientid));
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, IV, sizeof(IV[0]));

	for (int i = 0; i < 4; ++i)
	{
		memory::copy(tempValues, IV[1]+(i*4), sizeof(uint32_t));
		memory::copy(tempValues + 1, cryptkey+(i*sizeof(uint32_t)), sizeof(uint32_t));
		tempValues[2] = tempValues[0] ^ tempValues[1];
		memory::copy(cryptkey+(i*4), tempValues + 2 ,sizeof(uint32_t));
	}

	//Create the packet.
	packetPtr = memory::pcopy (packetPtr, &handshake.Header, sizeof(boost::uint16_t));
	packetPtr = memory::pcopy (packetPtr, &handshake.Size, sizeof(boost::uint32_t));
	packetPtr = memory::pcopy (packetPtr, &handshake.ServerId, sizeof(MUID));
	packetPtr = memory::pcopy (packetPtr, &handshake.PlayerId, sizeof(MUID));
	packetPtr = memory::pcopy (packetPtr, &handshake.Timestamp, sizeof(boost::uint32_t));

	socket.send(boost::asio::buffer(packet, 26));
}

Client::~Client()
{
	santa->give_back(clientid);
}
