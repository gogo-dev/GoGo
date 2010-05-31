#include <net/PacketCrypto.h>

using namespace boost;

namespace packet
{

uint8_t* decrypt(uint8_t* packet, int length, int index,
	const uint8_t* key)
{
	uint8_t a, b;

	packet += index;

	for(int i = 0; i < length; ++i)
	{
		a = packet[i] ^ 0xF0;
		b = a & 0x1F;
		b = (a >> 5) | (b << 3);
		packet[i] = b ^ key[i & 0x1F];
	}

	return packet - index;
}

uint8_t* encrypt(uint8_t* packet, int length, int index,
	const uint8_t* key)
{
	uint16_t a;
	uint8_t  b;

	packet += index;

	for(int i = 0; i < length; ++i)
	{
		a = (packet[i] ^ key[i & 0x1F]) << 5;
		b = static_cast<uint8_t>(a >> 8);
		b = (b | a) ^ 0xF0;
		packet[i] = b;
	}

	return packet - index;
}

uint16_t checksum(const uint8_t* packet, int length,
	int index)
{
	uint32_t t[4] = { 0 };

	packet += index;

	for (int i = 0; i < 4; ++i)
		t[0] += *packet++;

	packet += 2;

	for (int i = 6; i < length; ++i)
		t[1] += *packet++;

	t[2] = t[1] - t[0];
	t[3] = t[2] >> 0x10;

	return static_cast<uint16_t>(t[2] + t[3]);
}

}