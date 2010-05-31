#include <net/PacketParameters.h>

#include <algorithm> // For std::swap
#include <cstddef>   // For size_t
#include <cassert>   // for assert, of course!

#include <util/memory.h>

using namespace std;
using namespace boost;

// On a little-endian architecture, the 0x01 will be stored in the first byte.
static inline bool machine_little_endian()
{
	int number = 1;
	return *reinterpret_cast<const unsigned char*>(&number) == 0x01;
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
		(type != uint8_t(-1)) &&
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
		Buffer serialized(sizeof(value));

		uint8_t* rawPointer = serialized.data();
		int32_t correctedValue = fix_endianness(value);

		memory::copy(rawPointer, &correctedValue, sizeof(value));

		return serialized;
	}

	uint32::uint32(uint32_t _value)
		: value(_value)
	{
		type = 0x01;
	}

	Buffer uint32::serialize() const
	{
		Buffer serialized(sizeof(value));

		uint8_t* rawPointer = serialized.data();
		uint32_t correctedValue = fix_endianness(value);

		memory::copy(rawPointer, &correctedValue, sizeof(value));

		return serialized;
	}

	floating_point::floating_point(float _value)
		: value(_value)
	{
		type = 0x02;
	}

	Buffer floating_point::serialize() const
	{
		Buffer serialized(sizeof(value));

		uint8_t* rawPointer = serialized.data();

		// I'm going to go out on a limb here and say floats have
		// bad endian-ness.
		float correctedValue = fix_endianness(value);

		memory::copy(rawPointer, &correctedValue, sizeof(value));

		return serialized;
	}

	boolean::boolean(bool _value)
		: value(_value)
	{
		type = 0x03;
	}

	Buffer boolean::serialize() const
	{
		Buffer serialized(sizeof(uint8_t));
		memory::copy(serialized.data(), &value, sizeof(uint8_t));
		return serialized;
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
		memory::set(rawPointer, 0x00, len - bigSize - 1);

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
		size_t bigSize = value.size() + 1;
		uint16_t len = static_cast<uint16_t>(bigSize);

		// TODO: Truncate the string instead. (Will this have a major
		// performance penalty?) (answer: probably not.)
		if(bigSize > 0xFFFF)
			return ::packet::string("[string too large]").serialize();

		Buffer serialized(sizeof(uint16_t) + len);

		uint8_t* rawPointer = serialized.data();

		rawPointer = memory::pcopy(rawPointer, &len, sizeof(len));
		memory::copy(rawPointer, value.c_str(), len);

		return serialized;
	}

	// Note the omission of a type. It is the subclasses responsibility to
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
		Buffer serialized(sizeof(float) * 3);

		uint8_t* rawPointer = serialized.data();

		float correctedValues[] = {
			fix_endianness(value.get<0>()),
			fix_endianness(value.get<1>()),
			fix_endianness(value.get<2>())
		};

		memory::copy(rawPointer, correctedValues,
				sizeof(correctedValues));

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

	Buffer color::serialize() const
	{
		Buffer serialized(sizeof(value));
		uint8_t* rawPointer = serialized.data();

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

	Buffer MUID::serialize() const
	{
		Buffer serialized(sizeof(value.quad));
		uint8_t* rawPointer = serialized.data();

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
		Buffer serialParam = param.serialize();
		elementData.reserve(elementData.size() + serialParam.length());

		for(size_t i = 0; i < serialParam.length(); ++i)
			elementData.push_back(serialParam.data()[i]);
	}

	Buffer blob::serialize() const
	{
		Buffer serialized(totalSize + 12);

		uint8_t* rawPointer = serialized.data();
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

	Buffer vector::serialize() const
	{
		Buffer serialized(sizeof(uint16_t) * 3);

		uint8_t* rawPointer = serialized.data();

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

	Buffer uint8::serialize() const
	{
		Buffer serialized(sizeof(value));
		serialized.data()[0] = value;
		return serialized;
	}

	int16::int16(int16_t _value)
		: value(_value)
	{
		type = 0x0D;
	}

	Buffer int16::serialize() const
	{
		Buffer serialized(sizeof(value));
		uint8_t* rawPointer = serialized.data();

		int16_t fixedValue = fix_endianness(value);
		memory::copy(rawPointer, &fixedValue, sizeof(value));

		return serialized;
	}

	uint16::uint16(uint16_t _value)
		: value(_value)
	{
		type = 0x0E;
	}

	Buffer uint16::serialize() const
	{
		Buffer serialized(sizeof(value));
		uint8_t* rawPointer = serialized.data();

		uint16_t fixedValue = fix_endianness(value);

		memory::copy(rawPointer, &fixedValue, sizeof(value));

		return serialized;
	}
}
