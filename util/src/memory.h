#pragma once
#include <boost/cstdint.hpp>	// For uint8_t, etc.
#include <cstring>		// For size_t.
#include <cassert>		// For assert

namespace memory {

// Peforms a type-safe memcpy. Returns a copy of "dest" for convenience.
template <typename T>
inline T* copy(T* dest, const void* src, size_t count)
{
	size_t i;
	uint8_t* fixedDest = reinterpret_cast<uint8_t*>(dest);
	const uint8_t* fixedSrc = reinterpret_cast<const uint8_t*>(src);
	
	assert(((count % sizeof(T)) == 0) &&
		"The count is not a multiple of the size of the target. Yay memory corruption."
	);

	for(i = 0; i < count; ++i)
		*fixedDest++ = *fixedSrc++;	

	return dest;
}

// Performs a memcpy, but returns a pointer to one byte past the end of the
// copy.
template <typename T>
inline T* pcopy(T* dest, const void* src, size_t count)
{
	size_t i;
	uint8_t* fixedDest = reinterpret_cast<uint8_t*>(dest);
	const uint8_t* fixedSrc = reinterpret_cast<const uint8_t*>(src);

	assert(((count % sizeof(T)) == 0) &&
		"The count is not a multiple of the size of the target. Yay memory corruption."
	);

	for(i = 0; i < count; ++i)
		*fixedDest++ = *fixedSrc++;

	return reinterpret_cast<T*>(fixedDest);
}

}
