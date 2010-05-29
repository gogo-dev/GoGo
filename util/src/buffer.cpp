#include <util/buffer.h>
#include <util/memory.h>

using namespace std;
using namespace boost;

Buffer::Buffer(size_t _length)
{
	length_ = _length;
	data_ = make_shared(new uint8_t[length_]);
}

Buffer::Buffer(const void* initialData, size_t _length)
{
	length_ = _length;
	memory::copy(data_.get(), initialData, length_);
}

Buffer::Buffer(const Buffer& other)
	: data_(other.data_), length_(other.length_)
{
}

uint8_t* Buffer::data()
{
	return data_.get();
}

size_t Buffer::length()
{
	return length_;
}
