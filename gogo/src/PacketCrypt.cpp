#include "PacketCrypt.h"
#include <boost/cstdint.hpp>

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

		return packet;
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

			b = (uint8_t)(a >> 8);
			b = (b | a) ^ 0xF0;
			packet[i] = b;
		}

		return packet;
	}
}
