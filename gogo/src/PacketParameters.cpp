#include "PacketParameters.h"

#include <algorithm> // For std::swap
#include <cstring>   // For size_t
#include <cassert>   // for assert, of course!

#include <util.h>

using namespace std;
using namespace boost;

// On a little-endian architecture, the 0x01 will be stored in the first byte.
static inline bool machine_little_endian()
{
	int number = 1;
	return *(const unsigned char*)(&number) == 0x01;
}

template <typename IntType>
static IntType reverse_endianness(IntType num)
{
	// The lowest and highest bytes.
	unsigned char* low = reinterpret_cast<unsigned char*>(&num);
	unsigned char* high = low + sizeof(IntType) - 1;

	while(low < high)
	{
		swap(*low, *high);
		--high;
		++low;
	}

	return num;
}

// Use this function to reverse the endianness of a number so it can be used to
// send to a windows machine from ANY computer.
template <typename IntType>
static IntType fix_endianness(IntType num)
{
	// Gunz requires all packets to be little-endian. On most platforms,
	// this is a realistic goal. On some, however, bits are stored in
	// big-endian format. This will need to be remedied... by this function!

	// Of course, the swapping can be skipped if we're already
	// little-endian.
	if(machine_little_endian())
		return num;
	else
		return reverse_endianness(num);
}

namespace packet
{
	Parameter::Parameter()
		: type(-1)
	{
	}

	uint8_t Parameter::get_type() const
	{
		assert(
			(type != -1) &&
			"A packet seems to have not registered a type. This is very bad and MUST be fixed."
		);

		return type;
	}

	int32::int32(int32_t _value)
		: value(_value)
	{
		type = 0x00;
	}

	serial_parameter int32::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value));

		uint8_t* rawPointer = &(serialized[0]);
		int32_t correctedValue = fix_endianness(value);

		memory::copy(rawPointer, &correctedValue, sizeof(value));

		return serialized;
	}

	uint32::uint32(uint32_t _value)
		: value(_value)
	{
		type = 0x01;
	}

	serial_parameter uint32::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value));

		uint8_t* rawPointer = &(serialized[0]);
		uint32_t correctedValue = fix_endianness(value);

		memory::copy(rawPointer, &correctedValue, sizeof(value));

		return serialized;
	}

	floating_point::floating_point(float _value)
		: value(_value)
	{
		type = 0x02;
	}

	serial_parameter floating_point::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value));

		uint8_t* rawPointer = &(serialized[0]);

		// I'm going to go out on a limb here and say floats have bad endian-ness.
		float correctedValue = fix_endianness(value);

		memory::copy(rawPointer, &correctedValue, sizeof(value));

		return serialized;
	}

	boolean::boolean(bool _value)
		: value(_value)
	{
		type = 0x03;
	}

	serial_parameter boolean::serialize() const
	{
		serial_parameter serialized;
		serialized.push_back(value ? 0x01 : 0x00);
		return serialized;
	}

	string::string(const char* _value)
		: value(_value)
	{
		hasFixedLength = false;

		type = 0x04;
	}

	string::string(const std::string& _value)
		: value(_value)
	{
		hasFixedLength = false;

		type = 0x04;
	}

	string::string(const char* _value, boost::uint16_t len)
		: value(_value), paramLen(len), hasFixedLength(true)
	{
		assert((len != 0) && "Wat.");

		type = 0x04;
	}

	uint8_t* string::output_length_header(uint16_t len, serial_parameter* out)
	{
		assert(out->capacity() >= sizeof(len));

		uint16 result = uint16(len);
		memory::copy(out, &(result.serialize()[0]), sizeof(len));

		return &((*out)[sizeof(len)]);
	}

	serial_parameter string::serialize_fixed(uint16_t len) const
	{
		if(len > paramLen)
			return ::packet::string("[string too large]").serialize();

		serial_parameter serialized;
		serialized.resize(paramLen);

		uint8_t* rawPointer = &(serialized[0]);

		rawPointer = memory::pcopy(rawPointer, value.c_str(), len);
		memory::set(rawPointer, 0x00, paramLen - len);

		return serialized;
	}

	serial_parameter string::serialize_dynamic(uint16_t len) const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(uint16_t) + len);

		uint8_t* rawPointer = &(serialized[0]);

		rawPointer = memory::pcopy(rawPointer, &len, sizeof(len));
		memory::copy(rawPointer, value.c_str(), len);

		return serialized;
	}

	serial_parameter string::serialize() const
	{
		size_t bigSize = value.size() + 1;

		// TODO: Truncate the string instead. (Will this have a major performance penalty?)
		if(bigSize > 0xFFFF)
			return ::packet::string("[string too large]").serialize();

		return hasFixedLength
				? serialize_fixed(static_cast<uint16_t>(bigSize))
				: serialize_dynamic(static_cast<uint16_t>(bigSize));
	}

	// Note the omission of a type. It is the subclasses responsibility to define one.
	float_tuple::float_tuple(float x, float y, float z)
		: value(x, y, z)
	{
	}

	float_tuple::float_tuple(const tuple<float, float, float>& _value)
		: value(_value)
	{
	}

	serial_parameter float_tuple::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(float) * 3);

		uint8_t* rawPointer = &(serialized[0]);

		float correctedValues[] = {
			fix_endianness(value.get<0>()),
			fix_endianness(value.get<1>()),
			fix_endianness(value.get<2>())
		};

		memory::copy(rawPointer, correctedValues, sizeof(correctedValues));

		return serialized;
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
		value.part.red = (_value >> 24) & 0xFF;
		value.part.green = (_value >> 16) & 0xFF;
		value.part.blue = (_value >> 8) & 0xFF;
		value.part.alpha = (_value >> 0) & 0xFF;

		type = 0x08;
	}

	serial_parameter color::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value));

		uint8_t* rawPointer = &(serialized[0]);

		uint32_t fixedValue = fix_endianness(value.raw);

		memory::copy(rawPointer, &(fixedValue), sizeof(fixedValue));

		return serialized;
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

	serial_parameter MUID::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value.quad));

		uint8_t* rawPointer = &(serialized[0]);

		uint64_t fixedValue = fix_endianness(value.quad);

		memory::copy(rawPointer, &fixedValue, sizeof(fixedValue));

		return serialized;
	}

	blob::blob(boost::uint32_t eleCount, boost::uint32_t eleSize)
	{
		totalSize = (eleCount * eleSize) + 8;
		elementSize = eleSize;
		elementCount = eleCount;

		type = 0xA;
	}

	void blob::addParam(const packet::Parameter &param)
	{
		serial_parameter serialParam = param.serialize();
		elementData.reserve(elementData.size() + serialParam.size());

		for(serial_parameter::iterator i = serialParam.begin(); i < serialParam.end();  ++i)
			elementData.push_back(*i);
	}

	serial_parameter blob::serialize() const
	{
		serial_parameter serialized;
		serialized.resize (totalSize + 12);

		uint8_t* rawPointer = &(serialized[0]);
		rawPointer = memory::pcopy(rawPointer, &totalSize, sizeof(uint32_t));
		rawPointer = memory::pcopy(rawPointer, &elementSize, sizeof(uint32_t));
		rawPointer = memory::pcopy(rawPointer, &elementCount, sizeof(uint32_t));

		for (uint32_t i = 0; i < elementData.size(); ++i)
			rawPointer = memory::pcopy(rawPointer, &(elementData[i]), sizeof(uint8_t));

		return serialized;
	}
	vector::vector(uint16_t x, uint16_t y, uint16_t z)
		: value(x, y, z)
	{
		type = 0x0B;
	}

	vector::vector(const Vec& _value)
		: value(_value)
	{
		type = 0x0B;
	}

	serial_parameter vector::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(uint16_t) * 3);

		uint8_t* rawPointer = &(serialized[0]);

		uint16_t fixedValues[] = {
			fix_endianness(value.get<0>()),
			fix_endianness(value.get<1>()),
			fix_endianness(value.get<2>())
		};

		memory::copy(rawPointer, fixedValues, sizeof(fixedValues));

		return serialized;
	}

	uint8::uint8(uint8_t _value)
		: value(_value)
	{
		type = 0x0C;
	}

	serial_parameter uint8::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value));

		serialized[0] = value;

		return serialized;
	}

	int16::int16(int16_t _value)
		: value(_value)
	{
		type = 0x0D;
	}

	serial_parameter int16::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value));

		uint8_t* rawPointer = &(serialized[0]);

		int16_t fixedValue = fix_endianness(value);

		memory::copy(rawPointer, &fixedValue, sizeof(value));

		return serialized;
	}

	uint16::uint16(uint16_t _value)
		: value(_value)
	{
		type = 0x0E;
	}

	serial_parameter uint16::serialize() const
	{
		serial_parameter serialized;
		serialized.resize(sizeof(value));

		uint8_t* rawPointer = &(serialized[0]);

		uint16_t fixedValue = fix_endianness(value);

		memory::copy(rawPointer, &fixedValue, sizeof(value));

		return serialized;
	}
}
