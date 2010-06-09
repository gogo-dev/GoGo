#pragma once
#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>

namespace cockpit {

// A very basic arena implementation. Useful for the "many small allocations"
// that is our current packet construction/deconstruction implementation.
class Allocator : private boost::noncopyable
{
private:
	boost::uint8_t* heapBegin;
	boost::uint8_t* heapEnd;

	boost::uint8_t* currentElem;

public:
	Allocator(size_t heapSize);

	boost::uint8_t* allocate(size_t amount);
	void free(boost::uint8_t* ptr);

	~Allocator();
};

}
