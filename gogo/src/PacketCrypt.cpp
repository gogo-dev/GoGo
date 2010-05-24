#include "PacketCrypt.h"
#include <boost/cstdint.hpp>

namespace packet
{
	unsigned char* decrypt(unsigned char* packet, int length, int index,
		const unsigned char* key)
	{
		boost::uint8_t a, b;

		for (int i = 0; i < length; ++i)
		{
			a = packet[index + i];
			a ^= 0xF0;
			b = (boost::uint8_t)(a & 0x1F);
			a >>= 5;
			b <<= 3;
			b = (boost::uint8_t) (a | b);
			packet[index + i] = (boost::uint8_t) (b ^ key[i % 32]);
		}

		return packet;
	}

	unsigned char* encrypt(unsigned char* packet, int length, int index,
		const unsigned char* key)
	{
		boost::uint16_t a;
		boost::uint8_t  b;

		for(int i = 0; i < length; ++i)
		{
			a = packet[index + i];
			a ^= key[i % 32];
			a <<= 5;

			b = (boost::uint8_t)(a >> 8);
			b |= (boost::uint8_t)(a & 0xFF);
			b ^= 0xF0;
			packet[index + i] = (boost::uint8_t)b;
		}

		return packet;
	}
}
