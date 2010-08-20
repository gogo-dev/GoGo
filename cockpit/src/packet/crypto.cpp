#include "crypto.h"

using namespace boost;

namespace cockpit {
namespace packet {

// toDecrypt is at &(packet[packetIndex])
uint8_t* decrypt(uint8_t* toDecrypt, size_t length, size_t packetIndex, const uint8_t* key)
{
	uint8_t a, b;
	
	for(size_t loopEnd = packetIndex + length; packetIndex != loopEnd; ++packetIndex, ++toDecrypt)
	{
		a = *toDecrypt ^ 0xF0;
		b = a & 0x1F;
		*toDecrypt = ((a >> 5) | (b << 3)) ^ key[packetIndex & 0x1F];
	}

	return toDecrypt;
}

// toEncrypt is at &(packet[packetIndex])
uint8_t* encrypt(uint8_t* toEncrypt, size_t length, size_t packetIndex, const uint8_t* key)
{
	uint16_t a;
	uint8_t  b;

	for(size_t loopEnd = packetIndex + length; packetIndex != loopEnd; ++packetIndex, ++toEncrypt)
	{
		a = (*toEncrypt ^ key[packetIndex & 0x1F]) << 5;
		b = static_cast<uint8_t>(a >> 8);
		*toEncrypt = static_cast<uint8_t>((b | a) ^ 0xF0);
	}

	return toEncrypt;
}

// Finds the sum of all the elements in consecutive memory locations.
static uint32_t find_sum(const uint8_t* ptr, size_t length)
{
	uint32_t sum = 0;

	for(const uint8_t* end = ptr + length; ptr != end; ++ptr)
		sum += *ptr;

	return sum;
}

uint16_t checksum(const uint8_t* packet, size_t length)
{
	uint32_t s = find_sum(packet + 6, length - 6) - find_sum(packet, 4);
	return static_cast<uint16_t>(s + (s >> 0x10));
}

}
}
