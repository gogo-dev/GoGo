#include "Allocator.h"

using namespace boost;

namespace cockpit {

Allocator::Allocator(size_t heapSize)
{
	heapBegin = new uint8_t[heapSize];
	heapEnd = heapBegin + heapSize;

	currentElem = heapBegin;
}

uint8_t* Allocator::allocate(size_t amount)
{
	// Our heap is full. Fall back to oldschool new/delete.
	if(currentElem + amount > heapEnd)
		return new uint8_t[amount];
	// Heeey, we have room in the heap! Allocate, then return.
	else
	{
		uint8_t* ret = currentElem;
		currentElem += amount;
		return ret;
	}
}

void Allocator::free(uint8_t* ptr)
{
	// If the pointer is in the heap, ignore it. Otherwise, call delete[] on it
	// since we went oldschool when the heap is full.
	if((ptr < heapBegin) || (ptr > heapEnd))
		delete[] ptr;
}

Allocator::~Allocator()
{
	delete heapBegin;
}

}
