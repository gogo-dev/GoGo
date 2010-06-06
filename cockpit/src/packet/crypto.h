#pragma once
#include <boost/cstdint.hpp>

namespace cockpit {
namespace packet {

// Takes a packet, the packet length, the index to start decryption,
// and the encryption key. The return value is equal to "packet",
// and the buffer "packet" is decrypted.
boost::uint8_t* decrypt(boost::uint8_t* packet, int length, int index,
						const boost::uint8_t* key);

// Takes a packet, the packet length, the index to start encryption,
// and the encryption key. The return value is equal to "packet",
// and the buffer "packet" is decrypted.
boost::uint8_t* encrypt(boost::uint8_t* packet, int length, int index,
						const boost::uint8_t* key);

// Takes a packet, the packet length, the index to start checksumming
// and checksums the packet. The return value is the checksum'd value.
boost::uint16_t checksum(const boost::uint8_t* packet, int length);

}
}