#pragma once

#include <cassert>
#include <cstddef>

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>

namespace reflex {
namespace detail {

// By pulling as much as possible up into the base class, we try to speed up
// compile times by removing useless instantiation of functions which do not
// depend on type.
class BufferBase
{
protected:
	typedef boost::mutex Lock;
	typedef boost::condition_variable Condition;
	typedef boost::unique_lock<Lock> Locker;

	size_t minSize;
	size_t capacity;
	size_t numElems;

	// The total number of elements ever pushed into the queue.
	uintmax_t traffic;

	mutable Lock protection;
	mutable Condition queueHasElements;

	static bool is_power_of_two(size_t x)
	{
		return (x != 0) && ((x & (x - 1)) == 0);
	}

	// Prevents user code from instantiating BufferBase unless it's through a
	// Buffer instantiation.
	BufferBase()  {}
	~BufferBase() {}

public:
	uintmax_t get_traffic() const
	{
		Locker r(protection);
		return traffic;
	}
};

/**
	This class aims to be the perfect queue for several threads producing and a
	single, different thread consuming. Elements will be consumed in the order
	they are produced. There MUST be only one consumer thread. The behavior is
	undefined otherwise.

	INTERNALS:

		WorkQueue is implemented internally as a dynamically resizing circular
		buffer. This offers good locality of reference, as well as constant
		amortized efficiency. A minor drawback of this approach is iterator
		invalidity, but that shouldn't be a problem given the sparse interface
		which lacks iterators :)
*/
template <typename ElemTy>
class Buffer : public detail::BufferBase, boost::noncopyable
{
private:
	ElemTy* buffer;

	ElemTy* head;    // The pointer to the head of the circular buffer.
	ElemTy* tail;    // The pointer to the tail of the circular buffer.

private:
	// Increments a pointer, compensating for the circular nature of the buffer.
	ElemTy* increment_internal_pointer(ElemTy* ptr)
	{
		assert(
			is_power_of_two(capacity)
		 && "We are using optimizations that assume the capacity will always be a power of two. Obviously, this is not the case!"
		);

		return buffer + ((ptr - buffer + 1) & (capacity - 1));
	}

	void resize(size_t newCap)
	{
		assert(
			newCap >= numElems
			&& "Trying to resize to an insufficient capacity. This makes me wat, and makes your computer overwrite the bounds of an array."
		);

		ElemTy* newBuffer = new ElemTy[newCap];

		for(size_t i = 0; i < numElems; ++i)
		{
			newBuffer[i] = *head;
			head = increment_internal_pointer(head);
		}

		delete[] buffer;
		buffer = newBuffer;

		head = newBuffer;
		tail = newBuffer + numElems;

		capacity = newCap;
	}

public:
	/**
		@param  defaultSize The initial number of elements to have in the queue.
		                    The queue will initially be of size 2^defaultSize.
	*/
	Buffer(size_t _minSize = 5)
	{
		if(_minSize < 2)
			_minSize = 2;

		capacity = 1 << _minSize;
		minSize =  capacity;

		numElems = 0;

		buffer = new ElemTy[capacity];
		head = buffer;
		tail = buffer;

		traffic = 0;
	}

	/**
		push() adds an item onto the end of the queue. If the internal buffer
		is full, the entire thing will be reallocated and the elements will be
		copied - similar in behavior to a vector. For efficiency reasons, the
		size will always be doubled when a resize must happen.
	*/
	void push(const ElemTy& elem)
	{
		{
			Locker w(protection);

			size_t newSize = numElems + 1;

			// If we hit the bursting point of the array, double the size.
			if(newSize > capacity)
				resize(capacity << 1);

			*tail = const_cast<ElemTy&>(elem);
			tail = increment_internal_pointer(tail);

			numElems = newSize;
			++traffic;
		}

		queueHasElements.notify_one();
	}

	/**
		pop() removes an element from the front of the queue and returns it. If
		the queue is empty, pop() will block until it has an element to return.

		If, after pop() removes an element, the queue is 1/4 of total capacity,
		the internal buffer will be resized to 1/2 its current size. This
		maintains the power-of-two property, prevents unnecessary reallocations,
		and keeps memory usage at a sane level.
	*/
	ElemTy pop()
	{
		Locker w(protection);

		while(numElems == 0)
			queueHasElements.wait(w);

		size_t newSize = numElems - 1;

		// When the number of elements drops below 1/4 of total capacity, the
		// buffer is resized to 1/2 it's current length. If the resize would
		// make it so that the buffer would drop below minSize, it is ignored.
		// These two lines ensure 3 properties:
		//     1) The buffer's memory usage stays sane.
		//     2) The buffer's capacity never drops below minSize.
		//     3) The buffer's capacity is always a power of two.
		if((newSize <= (capacity / 4)) && (newSize >= (minSize * 2)))
			resize(capacity >> 1);

		ElemTy* ret = head;

		head = increment_internal_pointer(head);

		numElems = newSize;

		return *ret;
	}

	~Buffer()
	{
		Locker w(protection);
		delete[] buffer;
	}
};

}
}
