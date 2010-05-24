#pragma once

namespace packet
{
	// Takes a packet, the packet length, the index to start decryption,
	// and the encryption key. The return value is equal to "packet",
	// and the buffer "packet" is decrypted.
	unsigned char* decrypt(unsigned char* packet, int length, int index,
			const unsigned char* key);

	// Takes a packet, the packet length, the index to start encryption,
	// and the encryption key. The return value is equal to "packet",
	// and the buffer "packet" is decrypted.
	unsigned char* encrypt(unsigned char* packet, int length, int index,
			const unsigned char* key);
}
