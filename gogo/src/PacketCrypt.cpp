#include "PacketCrypt.h"
#include <boost/cstdint.hpp>

using namespace boost;

namespace packet
{
	uint8_t* decrypt(uint8_t* packet, int length, int index,
		const uint8_t* key)
	{
		uint8_t a, b;

		for (int i = 0; i < length; ++i)
		{
			a = packet[index + i];
			a ^= 0xF0;
			b = a & 0x1F;
			a >>= 5;
			b <<= 3;
			b = a | b;
			packet[index + i] = b ^ key[i % 32];
		}

		return packet;
	}

	uint8_t* encrypt(uint8_t* packet, int length, int index,
		const uint8_t* key)
	{
		uint16_t a;
		uint8_t  b;

		for(int i = 0; i < length; ++i)
		{
			a = packet[index + i];
			a ^= key[i % 32];
			a <<= 5;

			b = (uint8_t)(a >> 8);
			b |= (uint8_t)(a & 0xFF);
			b ^= 0xF0;
			packet[index + i] = b;
		}

		return packet;
	}
}
