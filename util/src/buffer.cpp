#include <util/buffer.h>
#include <util/memory.h>
#include <boost/checked_delete.hpp>

using namespace std;
using namespace boost;

Buffer::Buffer(size_t _length)
	: data_(new uint8_t[_length])
{
	length_ = _length;
}

Buffer::Buffer(const void* initialData, size_t _length)
{
	length_ = _length;
	memory::copy(data_, initialData, length_);
}

Buffer::Buffer(const Buffer& other)
	: data_(new uint8_t[other.length_])
{
	length_ = other.length_;
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
