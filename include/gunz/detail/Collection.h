#pragma once
#include <algorithm>
#include <boost/config.hpp>
#include <boost/function.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <cassert>
#include <cstddef>
#include <vector>

namespace gunz {
namespace detail {

/**
	This class is used as a generic, fast, reentrant container for arbitrary
	types. The class is nowhere near as full-featured as std::vector, but it
	works quite nicely for our needs.

	ElemTy must satisfy the following concepts:
		- CopyConstructable
		- MoveConstrucable if you're using C++0x (optional, but recommended)
		- Assignable
*/
template <typename ElemTy>
class Collection
{
private:
	mutable boost::shared_mutex protection;
	typedef boost::unique_lock<boost::shared_mutex> WritingLock;
	typedef boost::shared_lock<boost::shared_mutex> ReadingLock;

	typedef typename std::vector<ElemTy> ElemContainer;
	typedef typename ElemContainer::iterator ElemIter;
	ElemContainer elems;

public:
	Collection()
	{
	}

	/**
		Constructs the collection with a starting size. As long as the number
		of elements never exceeds that size, the collection will not need to
		reallocate all of its elements.
	*/
	Collection(size_t defaultSize)
		: elems(defaultSize)
	{
	}

	Collection(const Collection& other)
	{
		ReadingLock rOther(other.protection);
		elems = other.elems;
	}

	Collection& operator=(const Collection& other)
	{
		ReadingLock rOther(other.protection);
		elems = other.elems;
		return *this;
	}

#if BOOST_HAS_RVALUE_REFS
	Collection(Collection&& other)
	{
		ReadingLock rOther(other.protection);
		elems = std::move(other.elems);
	}

	Collection& operator=(Collection&& other)
	{
		ReadingLock rOther(other.protection);
		elems = std::move(other.elems);
		return *this;
	}
#endif

	/**
		Adds an element to the collection. Runs in amortized O(1).
	*/
	void Add(const ElemTy& elem)
	{
		WritingLock w(protection);
		elems.push_back(elem);
	}

	/**
		Removes an element from the collection. Runs in O(1).

		@return Whether or not the element could be removed.
	*/
	bool Remove(const ElemTy& elem)
	{
		boost::upgrade_lock<boost::shared_mutex> r(protection);
		ElemIter end = elems.end();
		ElemIter loc = std::find(elems.begin(), end, elem);

		if(loc == end)
			return false;

		boost::upgrade_to_unique_lock<boost::shared_mutex> w(r);
		std::swap(*loc, *(end - 1));
		elems.pop_back();

		return true;
	}

	/**
		Maps a function over every element in the collection with modifications
		to the elements allowed. Runs in O(n).

		Mappping is the concept of calling a function for every element in the
		collection. If you don't need to modify any of the elements, consider
		using cmap instead, as it will be far more efficient.

		@param  func    The function to map. It must take a reference to an
		                element.

		@see Collection::cmap
	*/
	void map(const boost::function<void (ElemTy& p)>& func)
	{
		WritingLock r(protection);
		std::for_each(elems.begin(), elems.end(), func);
	}

	/**
		Maps a function over every element in the collection with modifications
		to the elements forbidden. Runs in O(n).

		Mapping is the concept of calling a function for every element in the
		collection. If you need to modify any of the elements, this function
		will not work for you. Use map instead.

		@param  func    The function to map. It must take a const reference to
		                an element.

		@see Collection::map
	*/
	void cmap(const boost::function<void (const ElemTy& p)>& func) const
	{
		ReadingLock w(protection);
		std::for_each(elems.begin(), elems.end(), func);
	}

	/**
		Returns the count of how many elements are in the collection. Runs in
		O(1).
	*/
	size_t length() const
	{
		ReadingLock r(protection);
		return elems.size();
	}

	~Collection()
	{
	}
};

}
}
