#pragma once
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>

#include <cstddef>
#include <cassert>

namespace cockpit {

// All allocator actions that don't need to be dependent on the array size can
// be done in here. This allows the implementations to be pulled out of the
// header, reducing compile times significantly.
class AllocatorBase : boost::noncopyable
{
protected:
	boost::uint8_t* heapBegin;
	boost::uint8_t* currentElem;
	boost::uint8_t* heapEnd;

	AllocatorBase(boost::uint8_t* heapBegin, boost::uint8_t* heapEnd);
	~AllocatorBase();

public:
	boost::uint8_t* allocate(size_t amount);
	void free(boost::uint8_t*& ptr) const;
	void purge();

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
};

// A very basic arena implementation. Useful for the "many small allocations"
// that is our current packet construction/deconstruction implementation.
template <size_t heapSize>
class Allocator : public AllocatorBase
{
private:
	boost::uint8_t heap[heapSize];

public:
	Allocator()
		: AllocatorBase(heap, heap + heapSize)
	{
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
		boost::uint8_t* ptr;

	public:
		auto_free(const Allocator& _alloc, boost::uint8_t* _ptr)
			: alloc(_alloc), ptr(_ptr)
		{
		}

		~auto_free()
		{
			assert(ptr);

			if(ptr)
				alloc.free(ptr);
		}
	};
};

}
