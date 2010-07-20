#pragma once
#include <cassert>
#include <cstddef>

#include <boost/call_traits.hpp>

/**
	This class aims to be the perfect queue for a single thread producing and a
	single, different thread consuming. Elements will be consumed in the order
	they are produced.

	INTERNALS:

		WorkQueue is implemented internally as a dynamically resizing circular
		buffer. This offers good locality of reference, as well as good
		amortized efficiency. A minor drawback of this approach is iterator
		invalidity, but that shouldn't be a problem given the sparse interface.

		//
*/
template <typename ElemTy>
class WorkQueue
{
private:
	size_t minSize;

	size_t currentCapacity;
	size_t numElems;

	ElemTy* buffer;
	ElemTy* head;
	ElemTy* tail;

private:
	void resize(size_t newSize)
	{
		assert(newSize > currentCapacity);

		ElemTy* newBuffer = new ElemTy[newSize];

		for(size_t i = 0; i < numElems; ++i)
			newBuffer[i] = *head++;

		delete[] buffer;
		buffer = newBuffer;

		head = newBuffer;
		tail = newBuffer + numElems;
	}

	static bool buffer_has_wrapped(ElemTy* head, ElemTy* tail)
	{
		return head < tail;
	}

public:
	/**
		@param  defaultSize The initial number of elements to have in the queue.
		                    The queue will initially be of size 2^defaultSize.
	*/
	WorkQueue(size_t defaultSize = 5)
	{
		currentCapacity = 1 << defaultSize;
		numElems = 0;

		buffer = new ElemTy[currentCapacity];
		head = buffer;
		tail = buffer;
	}

	/**
		push() adds an item onto the end of the queue. If the internal buffer
		is full, the entire thing will be reallocated and the elements will be
		copied - similar in behavior to a vector. For efficiency reasons, the
		size will always be doubled when a resize must happen.
	*/
	void push(typename boost::call_traits<ElemTy>::param_type elem)
	{
		if((numElems + 1) > currentCapacity)
			resize(2 * currentCapacity);

		static_cast<void>(elem);
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
		return ElemTy();
	}

	~WorkQueue()
	{
		delete[] buffer;
	}
};
