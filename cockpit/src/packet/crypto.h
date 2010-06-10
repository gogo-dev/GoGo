#pragma once
#include <cstddef>
#include <boost/cstdint.hpp>

namespace cockpit {
namespace packet {

/**
	Decrypts a subset of a packet (from toDecrypt to toDecrypt + length) in-place.

	@param  toDecrypt    The beginning of the packet subset to decrypt.
	@param  length       The length of the packet subset that we'll be decrypting.
	@param  packetIndex  Where in the packet toDecrypt is, relative to the first byte.
	@param  key          The crypto key for the packet. This must be a 26-byte array.

	@return A pointer to toDecrypt + length, provided for convenience.
*/
boost::uint8_t* decrypt(boost::uint8_t* toDecrypt, size_t length,
             size_t packetIndex,
             const boost::uint8_t* key);

/**
	Encrypts a subset of a packet (from toEncrypt to toEncrypt + length) in-place.

	@param  toEncrypt    The beginning of the packet subset to encrypt.
	@param  length       The length of the packet subset we'll be encrypting.
	@param  packetIndex  Where in the packet toEncrypt is, relative to the first byte.
	@param  key          The crypto key for the packet. This must be a 26-byte array.

	@return A pointer to toEncrypt + length, provided for convenience.
*/
boost::uint8_t* encrypt(boost::uint8_t* toEncrypt, size_t length,
                        size_t packetIndex,
                        const boost::uint8_t* key);

/**
	Performs a checksum for a packet (MAIET's algorithm).

	@param  packet  A pointer to the raw packet data.
	@param  length  The length of the raw packet data.

	@return The packet's checksum.
*/
boost::uint16_t checksum(const boost::uint8_t* packet, size_t length);

}
}
