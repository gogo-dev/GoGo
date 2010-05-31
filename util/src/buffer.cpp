#include <util/buffer.h>
#include <util/memory.h>
#include <boost/checked_delete.hpp>
#include <cstddef>

using namespace std;
using namespace boost;

Buffer::Buffer(size_t _length)
{
	init_buffer(_length);
}

Buffer::Buffer(const void* initialData, size_t _length)
{
	init_buffer(_length);
	memory::copy(data_, initialData, length_);
}

Buffer::Buffer(const Buffer& other)
{
	init_buffer(other.length_);
	memory::copy(data_, other.data_, length_);
}

void Buffer::init_buffer(size_t length)
{
	length_ = length;

	if(length > 0)
		data_ = new uint8_t[length];
	else
		data_ = NULL;
}

uint8_t* Buffer::data()
{
	return data_;
}

const uint8_t* Buffer::data() const
{
	return data_;
}

size_t Buffer::length() const
{
	return length_;
}

Buffer::~Buffer()
{
	checked_array_delete(data_);
}
