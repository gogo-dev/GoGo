#include "Allocator.h"

using namespace std;
using namespace boost;

namespace cockpit {

AllocatorBase::AllocatorBase(boost::uint8_t* _heapBegin, boost::uint8_t* _heapEnd)
	: heapBegin(_heapBegin), currentElem(_heapBegin), heapEnd(_heapEnd)
{
}

AllocatorBase::~AllocatorBase()
{
}

uint8_t* AllocatorBase::allocate(size_t amount)
{
	// Our heap is full. Fall back to oldschool new/delete.
	if(currentElem + amount > heapEnd)
		return new uint8_t[amount];

	// Heeey, we have room in the heap! Allocate, then return.
	else
		return (currentElem += amount) - amount;
}

// THIS NOT MODIFYING INTERNAL STATE IS VITAL. DO NOT REMOVE THE CONST
// SPECIFIER. It's necessary to keep this thing mildly thread-safe.
void AllocatorBase::free(boost::uint8_t*& ptr) const
{
	// If the pointer is in the heap, ignore it. Otherwise, call delete[] on it
	// since we went oldschool when the heap is full.
	if((ptr < heapBegin) || (ptr >= heapEnd))
		delete[] ptr;

	ptr = NULL;
}

void AllocatorBase::purge()
{
	currentElem = heapBegin;
}

}
