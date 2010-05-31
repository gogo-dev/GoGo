#pragma once
#include <cstddef>
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

	boost::uint8_t* data();
	const boost::uint8_t* data() const;

	size_t length() const;

	bool operator==(const Buffer& other) const;

	~Buffer();
};
