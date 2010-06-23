#include <cockpit/packet/Parameters.h>

#include <algorithm> // For std::swap
#include <cstddef>   // For size_t
#include <cassert>   // for assert, of course!

#include <util/memory.h>

using namespace std;
using namespace boost;

// This function can be used to serialize ANY
// built-in type.
template <typename T>
static Buffer serialize_built_in(T toSerialize)
{
	Buffer serialized(sizeof(toSerialize));
	memory::copy(serialized.data(), &toSerialize, sizeof(toSerialize));
	return serialized;
}

template <typename T, size_t N>
static Buffer serialize_built_in(const T (&toSerialize)[N])
{
	const size_t siz = sizeof(toSerialize) * N;

	Buffer serialized(siz);
	memory::copy(serialized.data(), toSerialize, siz);

	return serialized;
}

namespace cockpit {
namespace packet {

Parameter::Parameter()
	: type(-1)
{
}

uint8_t Parameter::get_type() const
{
	assert(
		(type != static_cast<uint8_t>(-1)) &&
		"A packet seems to have not registered a type. This is very bad and MUST be fixed."
	);

	return type;
}

int32::int32(int32_t _value)
	: value(_value)
{
	type = 0x00;
}

Buffer int32::serialize() const
{
	return serialize_built_in(value);
}

uint32::uint32(uint32_t _value)
	: value(_value)
{
	type = 0x01;
}

Buffer uint32::serialize() const
{
	return serialize_built_in(value);
}

floating_point::floating_point(float _value)
	: value(_value)
{
	type = 0x02;
}

Buffer floating_point::serialize() const
{
	return serialize_built_in(value);
}

boolean::boolean(bool _value)
	: value(_value)
{
	type = 0x03;
}

Buffer boolean::serialize() const
{
	return serialize_built_in(value);
}

blob_string::blob_string(const char* _value, boost::uint16_t _len)
	: value(_value)
{
	// The type is left uninitialized on purpose. This way, we
	// will be aware of any shenanigans with accessing a
	// blob_string's type, as it should NEVER be necessary.

	assert((_len != 0) && "Wat.");

	len = _len;
}

Buffer blob_string::serialize() const
{
	size_t bigSize = value.length() + 1;

	if(bigSize > len)
		return blob_string("[string too large]", len).serialize();

	Buffer serialized(len);

	uint8_t* rawPointer = serialized.data();

	rawPointer = memory::pcopy(rawPointer, value.c_str(), len);
	memory::zero(rawPointer, len - bigSize - 1);

	return serialized;
}


string::string(const char* _value)
	: value(_value)
{
	type = 0x04;
}

string::string(const std::string& _value)
	: value(_value)
{
	type = 0x04;
}

Buffer string::serialize() const
{
	static const uint16_t zero = 0;

	size_t actualSize = value.length() + 2; // Includes the length header and two null-terminators.
	uint16_t len = static_cast<uint16_t>(value.length());

	// TODO: Truncate the string instead. (Will this have a major
	// performance penalty?) (answer: probably not.)
	if(actualSize > 0xFFFF)
		return ::cockpit::packet::string("[string too large]").serialize();

	Buffer serialized(actualSize);

	uint8_t* rawPointer = serialized.data();

	rawPointer = memory::pcopy(rawPointer, &len, sizeof(len));
	rawPointer = memory::pcopy(rawPointer, value.c_str(), value.length());
	memory::copy(rawPointer, &zero, sizeof(zero));	// The null-terminators.

	return serialized;
}

// Note the omission of a type. It is the subclass' responsibility to
// define one.
float_tuple::float_tuple(float x, float y, float z)
	: value(x, y, z)
{
}

float_tuple::float_tuple(const tuple<float, float, float>& _value)
	: value(_value)
{
}

Buffer float_tuple::serialize() const
{
	float arrayValues[] = {
		get<0>(value),
		get<1>(value),
		get<2>(value)
	};

	return serialize_built_in(arrayValues);
}

position::position(float x, float y, float z)
	: float_tuple(x, y, z)
{
	type = 0x06;
}

position::position(const tuple<float, float, float>& _value)
	: float_tuple(_value)
{
	type = 0x06;
}

direction::direction(float x, float y, float z)
	: float_tuple(x, y, z)
{
	type = 0x07;
}

direction::direction(const tuple<float, float, float>& _value)
	: float_tuple(_value)
{
	type = 0x07;
}

color::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	value.part.red = red;
	value.part.green = green;
	value.part.blue = blue;
	value.part.alpha = alpha;

	type = 0x08;
}

color::color(uint32_t _value)
{
	value.part.red =   (_value >> 24) & 0xFF;
	value.part.green = (_value >> 16) & 0xFF;
	value.part.blue =  (_value >> 8 ) & 0xFF;
	value.part.alpha = (_value >> 0 ) & 0xFF;

	type = 0x08;
}

Buffer color::serialize() const
{
	return serialize_built_in(value.raw);
}

MUID::MUID(uint32_t low, uint32_t high)
{
	value.part.low = low;
	value.part.high = high;

	type = 0x09;
}

MUID::MUID(uint64_t full)
{
	value.quad = full;

	type = 0x09;
}

Buffer MUID::serialize() const
{
	return serialize_built_in(value.quad);
}

blob::blob(boost::uint32_t eleCount, boost::uint32_t eleSize)
{
	elementSize = eleSize;
	elementCount = eleCount;

	type = 0xA;
}

void blob::add_param(const Parameter &param)
{
	Buffer serialParam = param.serialize();
	elementData.reserve(elementData.size() + serialParam.length());

	for(size_t i = 0; i < serialParam.length(); ++i)
		elementData.push_back(serialParam.data()[i]);
}

Buffer blob::serialize() const
{
	uint32_t totalSize = (elementCount * elementSize) + 8;

	Buffer serialized(totalSize + 4);

	uint8_t* rawPointer = serialized.data();
	rawPointer = memory::pcopy(rawPointer, &totalSize, sizeof(uint32_t));
	rawPointer = memory::pcopy(rawPointer, &elementSize, sizeof(uint32_t));
	rawPointer = memory::pcopy(rawPointer, &elementCount, sizeof(uint32_t));

	memory::copy(rawPointer, &(elementData[0]), elementData.size());

	return serialized;
}

int8::int8(int8_t _value)
	: value(_value)
{
	type = 0x0B;
}

Buffer int8::serialize() const
{
	return serialize_built_in(value);
}

uint8::uint8(uint8_t _value)
	: value(_value)
{
	type = 0x0C;
}

Buffer uint8::serialize() const
{
	return serialize_built_in(value);
}

int16::int16(int16_t _value)
	: value(_value)
{
	type = 0x0D;
}

Buffer int16::serialize() const
{
	return serialize_built_in(value);
}

uint16::uint16(uint16_t _value)
	: value(_value)
{
	type = 0x0E;
}

Buffer uint16::serialize() const
{
	return serialize_built_in(value);
}

}
}

