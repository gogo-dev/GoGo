#pragma once
#include <cstddef>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/shared_array.hpp>

class Buffer
{
private:
	boost::uint8_t* data_;
	size_t length_;

private:
	void init_buffer(size_t length);

public:
	Buffer(size_t length);
	Buffer(const void* initialData, size_t length);
	Buffer(const Buffer& other);

#if BOOST_HAS_RVALUE_REFS
	Buffer(const Buffer&& rhs)
	{
		data_ = rhs.data_;
		length_ = rhs.length_;
	}
#endif

	boost::uint8_t* data();
	const boost::uint8_t* data() const;

	size_t length() const;

	bool operator==(const Buffer& other) const;

	~Buffer();
};
