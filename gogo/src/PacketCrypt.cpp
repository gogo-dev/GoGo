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
			b = (uint8_t)(a >> 8);
			b = (b | a) ^ 0xF0;
			packet[i] = b;
		}

		return packet - index;
	}

	uint16_t checksum(uint8_t* packet, int length, int index)
	{
		uint32_t intermediateValues[4] = {0};

		for (int i = 0; i < 4; ++i)
			intermediateValues[0] += packet[index + i];
		
		for (int i = 6; i < length; ++i)
			intermediateValues[1] += intermediateValues[index + i];

		intermediateValues[2] = intermediateValues[1] - intermediateValues[0];
		intermediateValues[3] = intermediateValues[2] >> 0x10;

		return (uint16_t)(intermediateValues[2] + intermediateValues[3]);
	}
}
