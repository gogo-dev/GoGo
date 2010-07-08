#pragma once
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/config.hpp>
#include <boost/function.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <cassert>
#include <cstddef>
#include <functional>
#include <list>
#include <utility>

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
		- Reentrant (Iff you use any of the find methods)
*/
template <typename ElemTy>
class Collection
{
private:
	mutable boost::shared_mutex protection;
	typedef boost::unique_lock<boost::shared_mutex> WritingLock;
	typedef boost::shared_lock<boost::shared_mutex> ReadingLock;

	typedef typename std::list<ElemTy> ElemContainer;
	typedef typename ElemContainer::iterator ElemIter;
	typedef typename ElemContainer::const_iterator ConstElemIter;
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
		Removes an element from the collection. Runs in O(n).

		@return Whether or not the element could be removed.
	*/
	bool Remove(const ElemTy& elem)
	{
		ElemIter loc;

		boost::upgrade_lock<boost::shared_mutex> r(protection);
		loc = std::find(elems.begin(), elems.end(), elem);

		if(loc == elems.end())
			return false;

		boost::upgrade_to_unique_lock<boost::shared_mutex> w(r);
		elems.erase(loc);

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
		WritingLock w(protection);
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
		ReadingLock r(protection);
		std::for_each(elems.begin(), elems.end(), func);
	}

	/**
		Use this function to search for an element in the collection. If you
		just want to use operator==, use the other overload instead. A custom
		predicate, however, is MUCH more versatile.

		@param  predicate A function that returns whether or not the current
		                  element is "the one" (that we're searching for).

		@return A valid pointer to the found element. If the element was not
		        found, it will be NULL.
	*/
	ElemTy* find(const boost::function<bool (const ElemTy& p)>& predicate)
	{
		ReadingLock r(protection);
		ElemIter current = elems.begin(), end = elems.end();

		for(; current != end; ++current)
			if(predicate(*current))
				return &*current;

		return NULL;
	}

	const ElemTy* find(const boost::function<bool (const ElemTy& p)>& predicate) const
	{
		ReadingLock r(protection);
		ConstElemIter current = elems.begin(), end = elems.end();

		for(; current != end; ++current)
			if(predicate(*current))
				return &*current;

		return NULL;
	}

	/**
		Just a convenient little wrapper around the predicated version of find
		if you're just searching for a specific element.
	*/
	std::pair<bool, ElemTy*> find(const ElemTy& toFind)
	{
		return find(boost::bind(std::equal_to<ElemTy>(), boost::cref(toFind), _1));
	}

	std::pair<bool, const ElemTy*> find(const ElemTy& toFind) const
	{
		return find(boost::bind(std::equal_to<ElemTy>(), boost::cref(toFind), _1));
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
