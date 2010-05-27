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
}

void Client::send_handshake()
{
	uint32_t unknownValue = 2;
	uint32_t tempValues[3] = { 0 };

	uint8_t packet[26] = {
		0x0A, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00
	};

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
	memory::copy(cryptkey, socket.remote_endpoint().address().to_v4().to_bytes().c_array(), 4);
	memory::copy(cryptkey+4, &unknownValue, 4);
	memory::copy(cryptkey+8, &clientid, 8);
	memory::copy(cryptkey+16, &IV[0], 16);

	//Now the fun time, packet creations.
	memory::copy(packet+10, cryptkey+4, 12);
	memory::copy(packet+22, cryptkey+0, 4);

	for (int i = 0; i < 4; ++i)
	{
		memcpy(tempValues, IV[1]+(i*4), 4);
		memcpy(tempValues + 1, cryptkey+(i*sizeof(uint32_t)), 4);
		tempValues[2] = tempValues[0] ^ tempValues[1];
		memcpy(cryptkey+(i*4), tempValues + 2 ,4);
	}

	socket.send (boost::asio::buffer (packet, 26));
}

Client::~Client()
{
	santa->give_back(clientid);
}
