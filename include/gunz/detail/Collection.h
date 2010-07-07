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

template <typename ElemTy>
class Collection
{
private:
	mutable boost::shared_mutex protection;
	typedef boost::unique_lock<boost::shared_mutex> WritingLock;
	typedef boost::shared_lock<boost::shared_mutex> ReadingLock;

	typedef typename std::vector<ElemTy*> ElemContainer;
	typedef typename ElemContainer::iterator ElemIter;
	ElemContainer elems;

public:
	Collection()
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

	void Add(ElemTy* elem)
	{
		WritingLock w(protection);
		elems.push_back(elem);
	}

	void Remove(ElemTy* elem)
	{
		boost::upgrade_lock<boost::shared_mutex> r(protection);
		ElemIter end = elems.end();
		ElemIter loc = std::find(elems.begin(), end, elem);

		assert((loc != end) && "Tried to remove a nonexistant element from a collection.");

		if(loc == end)
			return;

		boost::upgrade_to_unique_lock<boost::shared_mutex> w(r);
		std::swap(*loc, *(end - 1));
		elems.pop_back();
	}

	void map(const boost::function<void (ElemTy* p)>& func)
	{
		WritingLock r(protection);
		std::for_each(elems.begin(), elems.end(), func);
	}

	void cmap(const boost::function<void (const ElemTy* p)>& func) const
	{
		ReadingLock w(protection);
		std::for_each(elems.begin(), elems.end(), func);
	}

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
