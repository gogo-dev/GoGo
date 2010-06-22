#pragma once
#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/static_assert.hpp>
#include <cassert>

#ifdef BOOST_NO_NULLPTR
	#define nullptr NULL
#endif

namespace cockpit {

// A very basic arena implementation. Useful for the "many small allocations"
// that is our current packet construction/deconstruction implementation.
template <size_t heapSize>
class Allocator : boost::noncopyable
{
private:
	uint8_t heap[heapSize];
	boost::uint8_t* currentElem;
	boost::uint8_t* heapEnd;

public:
	Allocator()
	{
		currentElem = heap;
		heapEnd = heap + heapSize;
	}

	boost::uint8_t* allocate(size_t amount)
	{
		// Our heap is full. Fall back to oldschool new/delete.
		if(currentElem + amount > heapEnd)
			return new uint8_t[amount];

		// Heeey, we have room in the heap! Allocate, then return.
		else
			return (currentElem += amount) - amount;
	}

	/**
		Allocates a raw type quickly and easily, without ugly casts. Be
		VERY careful with using this method. Constructors will NOT be called,
		as this method assumes T is a POD type.
	*/
	template <typename T>
	T* allocate()
	{
		return reinterpret_cast<T*>(allocate(sizeof(T)));
	}

	// THIS NOT MODIFYING INTERNAL STATE IS VITAL. DO NOT REMOVE THE CONST
	// SPECIFIER. It's necessary to keep this thing mildly thread-safe.
	void free(boost::uint8_t*& ptr) const
	{
		// If the pointer is in the heap, ignore it. Otherwise, call delete[] on it
		// since we went oldschool when the heap is full.
		if((ptr < heap) || (ptr >= heapEnd))
			delete[] ptr;

		ptr = nullptr;
	}

	// Resets the heap. This is hugely unsafe. Make sure you've called free()
	// on all outstanding pointers BEFORE calling this method. This will not
	// be checked for you.
	void purge()
	{
		currentElem = heap;
	}

	~Allocator()
	{
	}

	/**
		Performs an allocation at construction, and frees the memory when
		destructed. Yay exception safety?
	*/
	class scoped_allocation : boost::noncopyable
	{
	private:
		boost::uint8_t* ptr;
		Allocator& alloc;

	public:
		scoped_allocation(Allocator& _alloc, size_t amount)
			: alloc(_alloc)
		{
			ptr = alloc.allocate(amount);
		}

		boost::uint8_t* raw()
		{
			assert(ptr);
			return ptr;
		}

		~scoped_allocation()
		{
			alloc.free(ptr);
		}
	};

	/**
		Frees a pointer previously requested from the allocator automatically
		when this object gets destructed. Note that this does absolutely NO
		checking to see wheter or not it came from the allocator in the first
		place, so please be safe. :)
	*/
	class auto_free : public boost::noncopyable
	{
	private:
		const Allocator& alloc;
		boost::uint8_t*& ptr;

	public:
		auto_free(const Allocator& _alloc, boost::uint8_t* _ptr)
			: alloc(_alloc), ptr(_ptr)
		{
		}

		~auto_free()
		{
			assert(ptr);
			alloc.free(ptr);
		}
	};
};

}

#ifdef BOOST_NO_NULLPTR
	#undef nullptr
#endif
