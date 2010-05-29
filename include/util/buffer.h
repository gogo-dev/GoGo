#pragma once
#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/shared_array.hpp>

class Buffer
{
	using namespace boost;
private:
	shared_array<uint8_t> data_;
	size_t length_;

public:
	Buffer(size_t length);
	Buffer(const void* initialData, size_t length);
	Buffer(const Buffer& other);

	uint8_t* data();
	size_t length();

	~Buffer();
};
