#pragma once
#include <cassert>
#include <cstddef>
#include <functional>

#include <boost/bind/bind.hpp>
#include <boost/call_traits.hpp>
#include <boost/ref.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

/**
	This class aims to be the perfect queue for a single thread producing and a
	single, different thread consuming. Elements will be consumed in the order
	they are produced. There MUST be only one producer and one consumer thread.
	If there is not, undefined behavior results.

	INTERNALS:

		WorkQueue is implemented internally as a dynamically resizing circular
		buffer. This offers good locality of reference, as well as good
		amortized efficiency. A minor drawback of this approach is iterator
		invalidity, but that shouldn't be a problem given the sparse interface.
*/
template <typename ElemTy>
class WorkQueue
{
	typedef typename boost::call_traits<ElemTy>::param_type ParamType;
private:
	size_t minSize;  // The size of the container will NEVER drop below
	                 // this amount.

	size_t capacity; // This number is actually log2(realCapacity). This
	                 // allows us to replace a modulus with a shift.

	size_t numElems; // Duh.

	ElemTy* buffer;  // The pointer to the beginning of the internal
	                 // buffer.

	ElemTy* head;    // The pointer to the head of the circular buffer.
	ElemTy* tail;    // The pointer to the tail of the circular buffer.

	boost::mutex protection;
	boost::condition_variable cond;

private:

	// Increments a pointer, compensating for the circular nature of the buffer.
	ElemTy* increment_internal_pointer(ElemTy* ptr)
	{
		// This will ONLY work if capacity is a power of two.
		return ((ptr - buffer + 1) & (capacity - 1)) + buffer;
	}

	void resize(size_t newCap)
	{
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

	void grow()
	{
		assert(
			numElems == capacity
		 && "We're trying to grow the buffer without it being necessary!"
		);

		resize(capacity * 2);
	}

	void shrink()
	{
		assert(
			numElems < (capacity / 2)
		 && "If we try to shrink the array now (we are), we will corrupt memory."
		);

		resize(capacity / 2);
	}

	inline bool queue_has_element()
	{
		return numElems != 0;
	}

public:
	/**
		@param  defaultSize The initial number of elements to have in the queue.
		                    The queue will initially be of size 2^defaultSize.
	*/
	WorkQueue(size_t defaultSize = 5)
	{
		if(defaultSize < 2)
			defaultSize = 2;

		capacity = 1 << defaultSize;
		minSize =  capacity;

		numElems = 0;

		buffer = new ElemTy[capacity];
		head = buffer;
		tail = buffer;
	}

	/**
		push() adds an item onto the end of the queue. If the internal buffer
		is full, the entire thing will be reallocated and the elements will be
		copied - similar in behavior to a vector. For efficiency reasons, the
		size will always be doubled when a resize must happen.
	*/
	void push(ParamType elem)
	{
		{
			boost::unique_lock<boost::mutex> w(protection);

			size_t newSize = numElems + 1;

			if(newSize > capacity)
				grow();

			*tail = elem;
			tail = increment_internal_pointer(tail);

			numElems = newSize;
		}

		cond.notify_one();
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
		using namespace std;
		using namespace boost;

		unique_lock<mutex> w(protection);

		cond.wait(w, bind(not_equal_to<size_t>(), cref(numElems), 0));

		size_t newSize = numElems - 1;

		if(newSize < capacity / 4 && newSize >= (minSize * 2))
			shrink();

		ElemTy& ret = *head;

		head = increment_internal_pointer(head);

		numElems = newSize;

		return ret;
	}

	~WorkQueue()
	{
		delete[] buffer;
	}
};
