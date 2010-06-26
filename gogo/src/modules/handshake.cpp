#include "../GoGoClient.h"
#include <gunz/simple_types.h>

#include <util/memory.h>
#include <boost/asio/ip/tcp.hpp>

using namespace boost;

namespace
{
	struct Handshake
	{
		boost::uint16_t Header;
		boost::uint32_t Size;
		MUID ServerId;
		MUID PlayerId;

		// Never used; MAIET is retarded. We just set this to 0x0DEADCA7 to be cool.
		boost::uint32_t Timestamp;

		Handshake(MUID player);
	};
}

Handshake::Handshake(MUID player)
{
	Header = 10;
	Size = 26;
	ServerId = 0;
	PlayerId = player;
	Timestamp = 0x0DEADCA7;
}

static array<uint8_t, 26> make_handshake(MUID myMUID, array<uint8_t, 32>& cryptoKey)
{
	uint32_t tempValues[3] = { 0 };
	uint8_t* cryptkeyPtr = cryptoKey.c_array();
	Handshake handshake(myMUID);

	boost::array<boost::uint8_t, 26> packet = { {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00
	} };

	uint8_t* packetPtr = &(packet[0]);

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
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, &myMUID, sizeof(myMUID));
	cryptkeyPtr = memory::pcopy(cryptkeyPtr, IV, sizeof(IV[0]));

	for (int i = 0; i < 4; ++i)
	{
		memory::copy(tempValues, IV[1]+(i*4), sizeof(uint32_t));
		memory::copy(tempValues + 1, cryptoKey.c_array() +(i*sizeof(uint32_t)), sizeof(uint32_t));
		tempValues[2] = tempValues[0] ^ tempValues[1];
		memory::copy(cryptoKey.c_array()+(i*4), tempValues + 2 ,sizeof(uint32_t));
	}

	//Create the packet.
	packetPtr = memory::pcopy(packetPtr, &handshake.Header, sizeof(boost::uint16_t));
	packetPtr = memory::pcopy(packetPtr, &handshake.Size, sizeof(boost::uint32_t));
	packetPtr = memory::pcopy(packetPtr, &handshake.ServerId, sizeof(MUID));
	packetPtr = memory::pcopy(packetPtr, &handshake.PlayerId, sizeof(MUID));
	packetPtr = memory::pcopy(packetPtr, &handshake.Timestamp, sizeof(boost::uint32_t));

	return packet;
}

array<uint8_t, 32> GoGoClient::handshake(asio::ip::tcp::socket& s) const
{
	array<uint8_t, 32> ret;
	s.send(asio::buffer(make_handshake(myMUID, ret), 26));
	return ret;
}
