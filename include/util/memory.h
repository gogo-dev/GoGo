#pragma once
#include <boost/cstdint.hpp>	// For uint8_t, etc.
#include <cstring>		// For size_t.
#include <cassert>		// For assert

namespace memory {

	// Peforms a type-safe memcpy. Returns a copy of "dest" for convenience.
	template <typename T>
	inline T* copy(T* dest, const void* src, size_t count)
	{
		assert(
			((count % sizeof(T)) == 0) &&
			"The count is not a multiple of the size of the target. Yay memory corruption."
		);

		return reinterpret_cast<T*>(memcpy(dest, src, count));
	}

	// Performs a memcpy, but returns a pointer to one byte past the end of the
	// copy.
	template <typename T>
	inline T* pcopy(T* dest, const void* src, size_t count)
	{
		if(count == 0)
			return dest;

		using namespace boost;

		register size_t n = (count + 7)/8;
		uint8_t* fixedDest = reinterpret_cast<uint8_t*>(dest);
		const uint8_t* fixedSrc = reinterpret_cast<const uint8_t*>(src);

		assert(
			((count % sizeof(T)) == 0) &&
			"The count is not a multiple of the size of the target. Yay memory corruption."
		);

		// See: http://en.wikipedia.org/wiki/Duff's_device
		switch(count % 8)
		{
		case 0:
			do {
				*fixedDest++ = *fixedSrc++;
		case 7:
				*fixedDest++ = *fixedSrc++;
		case 6:
				*fixedDest++ = *fixedSrc++;
		case 5:
				*fixedDest++ = *fixedSrc++;
		case 4:
				*fixedDest++ = *fixedSrc++;
		case 3:
				*fixedDest++ = *fixedSrc++;
		case 2:
				*fixedDest++ = *fixedSrc++;
		case 1:
				*fixedDest++ = *fixedSrc++;
			} while(--n > 0);
		}

		return reinterpret_cast<T*>(fixedDest);
	}

	/**
		Essentially a clone of "memset". Will set "count" bytes of "dest" to "value".
		Returns "dest" for convenience.
	*/
	template <typename T>
	inline T* set(T* dest, boost::uint8_t value, size_t count)
	{
		return reinterpret_cast<T*>(memset(reinterpret_cast<void*>(dest), value, count));
	}

	/**
		Zeroes count bytes of memory pointed at by dest.
	*/
	template <typename T>
	inline T* zero(T* dest, size_t count)
	{
		return set(dest, 0, count);
	}

}
