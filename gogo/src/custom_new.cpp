#include <cstddef>
#include <cstdlib>
#include <new>

// Instead of returning the number of requested bytes, we overload "new" to
// round the number of bytes up to the nearest power of two. This property
// leads to much less memory fragmentation, although comes at the cost of
// using up to "bytes" extra bytes of memory. This file implements that scheme.

static size_t round_up_to_pow_2(size_t n)
{
	n--;    // For the odd case where it's already a power of two, we subtract
	        // one to prevent this algorithm from getting the NEXT power of two.

	for(size_t offset = 1; offset < (sizeof(size_t) * 8); offset *= 2)
		n = (n >> offset) | n;

	return n + 1;
}

void* operator new(size_t bytes) throw(std::bad_alloc)
{
	void* mem = malloc(round_up_to_pow_2(bytes));

	if(mem == NULL)
		throw std::bad_alloc();

	return mem;
}

void* operator new(size_t bytes, std::nothrow_t) throw()
{
	return malloc(round_up_to_pow_2(bytes));
}

void* operator new[](size_t bytes) throw(std::bad_alloc)
{
	void* mem = malloc(round_up_to_pow_2(bytes));

	if(mem == NULL)
		throw std::bad_alloc();

	return mem;
}

void* operator new[](size_t bytes, std::nothrow_t) throw()
{
	return malloc(round_up_to_pow_2(bytes));
}

void operator delete(void* mem, std::nothrow_t) throw(std::bad_alloc)
{
	if(mem != NULL)
		free(mem);
}

void operator delete(void* mem) throw()
{
	if(mem != NULL)
		free(mem);
}

void operator delete[](void* mem, std::nothrow_t) throw(std::bad_alloc)
{
	if(mem != NULL)
		free(mem);
}

void operator delete[](void* mem) throw()
{
	if(mem != NULL)
		free(mem);
}
