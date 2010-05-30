#include <util/buffer.h>
#include <util/memory.h>
#include <boost/checked_delete.hpp>
#include <cstddef>

using namespace std;
using namespace boost;

Buffer::Buffer(size_t _length)
{
	length_ = _length;

	if(length_ > 0)
		data_ = new uint8_t[_length];
	else
		data_ = NULL;
}

Buffer::Buffer(const void* initialData, size_t _length)
{
	length_ = _length;

	if(length_ > 0)
		data_ = new uint8_t[length_];
	else
		data_ = NULL;

	memory::copy(data_, initialData, length_);
}

Buffer::Buffer(const Buffer& other)
{
	length_ = other.length_;
	
	if(length_ > 0)
		data_ = new uint8_t[length_];
	else
		data_ = NULL;

	memory::copy(data_, other.data_, length_);
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
