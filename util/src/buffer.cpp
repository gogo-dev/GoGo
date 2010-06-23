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

void Buffer::init_buffer(size_t _length)
{
	length_ = _length;

	if(_length > 0)
		data_ = new uint8_t[_length];
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

bool Buffer::operator==(const Buffer& other) const
{
	if(length() != other.length())
		return false;

	for(size_t i = 0; i < length(); ++i)
		if(data()[i] != other.data()[i])
			return false;

	return true;
}

Buffer::~Buffer()
{
	if(data_ != NULL)
		delete[] data_;
}
