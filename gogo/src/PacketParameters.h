#pragma once
#include <vector>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/tuple/tuple.hpp>
#include <cstring>

/*
 * This file handles all the packet parameter type definitions. It is provided
 * as a convenience for packet construction, as the routine can be generalized
 * like crazy.
 */

namespace packet
{
	// Represents a raw segment of a packet.
	typedef std::vector<boost::uint8_t> serial_parameter;

	class Parameter
	{
	protected:
		// The type of the packet. Should ALWAYS be set at
		// construction time.
		boost::uint8_t type;

	public:
		Parameter();

		// Used for extracting a copy of the type value. Note that
		// "type" is read-only except when the class is constructed.
		// This ensures thread-safety.
		boost::uint8_t get_type() const;

		// Grabs a stringified version of the subclass. Used for ezpz
		// packet construction.
		virtual serial_parameter serialize() const = 0;
	};

	class int32 : public Parameter
	{
	private:
		boost::int32_t value;

	public:
		int32(boost::int32_t value);
		serial_parameter serialize() const;
	};

	class uint32 : public Parameter
	{
	private:
		boost::uint32_t value;

	public:
		uint32(boost::uint32_t value);
		serial_parameter serialize() const;
	};

	class floating_point : public Parameter
	{
	private:
		float value;

	public:
		floating_point(float value);
		serial_parameter serialize() const;
	};

	class boolean : public Parameter
	{
	private:
		bool value;

	public:
		boolean(bool value);
		serial_parameter serialize() const;
	};

	class string : public Parameter
	{
	private:
		std::string value;
		boost::uint16_t paramLen;
		bool hasFixedLength;

	private:
		// Outputs the "length" of the blob to the top of the serial_parameter.
		// NOTE: The parameter MUST have enough room for the header.
		// This will return a pointer to where you can begin outputting the payload,
		// immediately after the length header.
		static boost::uint8_t* output_length_header(boost::uint16_t len, serial_parameter* out);

		serial_parameter serialize_fixed(boost::uint16_t len) const;
		serial_parameter serialize_dynamic(boost::uint16_t len) const;

	public:
		string(const char* value);
		string(const std::string& value);
		string(const char* value, boost::uint16_t len);
		serial_parameter serialize() const;
	};

	class float_tuple : public Parameter
	{
	private:
		boost::tuple<float, float, float> value;

	// This class must not be instantiated directly. Use one of its
	// descendants (position or direction). It is provided merely as a
	// convenience.
	protected:
		float_tuple(float x, float y, float z);
		float_tuple(const boost::tuple<float, float, float>& value);

	public:
		serial_parameter serialize() const;
	};

	class position : public float_tuple
	{
	public:
		position(float x, float y, float z);
		position(const boost::tuple<float, float, float>& value);
	};

	class direction : public float_tuple
	{
	public:
		direction(float x, float y, float z);
		direction(const boost::tuple<float, float, float>& value);
	};

	class color : public Parameter
	{
	private:
		union
		{
			struct
			{
				boost::uint8_t red;
				boost::uint8_t green;
				boost::uint8_t blue;
				boost::uint8_t alpha;
			} part;
			boost::uint32_t raw;
		} value;

	public:
		color(
			boost::uint8_t red, boost::uint8_t green,
			boost::uint8_t blue, boost::uint8_t alpha);

		// The uint32_t must be in the form of [rrggbbaa].
		color(boost::uint32_t value);
		serial_parameter serialize() const;
	};

	class MUID : public Parameter
	{
	private:
		union
		{
			struct
			{
				boost::uint32_t high;
				boost::uint32_t low;
			} part;
			boost::uint64_t quad;
		} value;

	public:
		MUID(boost::uint32_t low, boost::uint32_t high);
		MUID(boost::uint64_t full);
		// TODO(Clark): A constructor for the common MUID class.
		serial_parameter serialize() const;
	};

	class blob : public Parameter
	{
	private:
		boost::uint32_t totalSize;
		boost::uint32_t elementSize;
		boost::uint32_t elementCount;
		std::vector<boost::uint8_t> elementData;

	private:
		static boost::uint8_t *mempcpy (void *src, const void *dest, size_t len);

	public:
		blob(boost::uint32_t eleCount, boost::uint32_t eleSize);
		void addParam (const packet::Parameter& param);
		serial_parameter serialize() const;
	};


	// This refers to the [x, y, z] vector, not the expandable array.
	class vector : public Parameter
	{
	private:
		typedef boost::tuple<boost::uint16_t, boost::uint16_t, boost::uint16_t> Vec;
		Vec value;

	public:
		vector(boost::uint16_t x, boost::uint16_t y, boost::uint16_t z);
		vector(const Vec& value);

		serial_parameter serialize() const;
	};

	class uint8 : public Parameter
	{
	private:
		boost::uint8_t value;

	public:
		uint8(boost::uint8_t value);
		serial_parameter serialize() const;
	};

	class int16 : public Parameter
	{
	private:
		boost::int16_t value;

	public:
		int16(boost::int16_t value);
		serial_parameter serialize() const;
	};

	class uint16 : public Parameter
	{
	private:
		boost::uint16_t value;

	public:
		uint16(boost::uint16_t value);
		serial_parameter serialize() const;
	};
}
