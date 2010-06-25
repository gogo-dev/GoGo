#pragma once
#include <cstddef>
#include <vector>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/tuple/tuple.hpp>
#include <util/buffer.h>

/*
 * This file handles all the packet parameter type definitions. It is provided
 * as a convenience for packet construction, as the routine can be generalized
 * like crazy.
 */

namespace cockpit {
namespace packet {

	/**
		A common interface for all packet parameters. This allows recursive
		parameters to be used, such as blob.
	*/
	class Parameter
	{
	protected:
		// The type of the packet. Should ALWAYS be set at
		// construction time.
		boost::uint8_t type;

	public:
		/**
			Sets "type" to an invalid value, requiring it to be set to
			a valid one in a subclass.
		*/
		Parameter();

		/**
			Used for extracting a copy of the type value. Note that
			"type" is read-only except when the class is constructed.
			This ensures thread-safety.

			@return The packet type ID.
		*/
		boost::uint8_t get_type() const;

		/**
			Gets a serialized version of the subclass. Used for generic
			packet construction.

			@return The serialized parameter.
		*/
		virtual Buffer serialize() const = 0;

		virtual ~Parameter()
		{
		}
	};

	/**
		Just zeros. However many zeros you want!
	*/
	class zeros : public Parameter
	{
	private:
		boost::uint16_t count;

	public:
		zeros(boost::uint16_t count);
		Buffer serialize() const;
	};

	/**
		A signed, 32-bit integer value.
	*/
	class int32 : public Parameter
	{
	private:
		boost::int32_t value;

	public:
		int32(boost::int32_t value);
		Buffer serialize() const;
	};

	/**
		An unsigned, 32-bit integer value.
	*/
	class uint32 : public Parameter
	{
	private:
		boost::uint32_t value;

	public:
		uint32(boost::uint32_t value);
		Buffer serialize() const;
	};

	/**
		A 32-bit floating point value.
	*/
	class floating_point : public Parameter
	{
	private:
		float value;

	public:
		floating_point(float value);
		Buffer serialize() const;
	};

	/**
		A boolean value.
	*/
	class boolean : public Parameter
	{
	private:
		bool value;

	public:
		boolean(bool value);
		Buffer serialize() const;
	};

	/**
		A string value. This type is ONLY for use within blobs. Do NOT build a
		packet with this as a raw parameter. The internal structure is
		different. If you need string semantics, please use packet::string.
	*/
	class blob_string : public Parameter
	{
	private:
		std::string value;
		boost::uint16_t len;

	public:
		blob_string(const char* value, boost::uint16_t len);
		Buffer serialize() const;
	};

	/**
		A string value. This type is ONLY for use in raw packets. Do NOT build
		a blob with a packet::string as a member. If you need string semantics,
		please use packet::blob_string.
	*/
	class string : public Parameter
	{
	private:
		std::string value;

	public:
		string(const char* value);
		string(const std::string& value);

		Buffer serialize() const;
	};

	/**
		This is just a convenience class to fill in common parts of the
		packet::position and packet::direction classes. In reality, they're
		both implemented the exact same, but since they have different
		meanings, each gets its own class.
	*/
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

		~float_tuple()
		{
		}

	public:
		Buffer serialize() const;
	};

	/**
		A tuple of three floats [x, y, z], representing a game object's
		position.
	*/
	class position : public float_tuple
	{
	public:
		position(float x, float y, float z);
		position(const boost::tuple<float, float, float>& value);
	};

	/**
		A tuple of three floats [x, y, z], representing a game object's
		direction.
	*/
	class direction : public float_tuple
	{
	public:
		direction(float x, float y, float z);
		direction(const boost::tuple<float, float, float>& value);
	};

	/**
		An RGBA 32-bit color value.
	*/
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
		color(boost::uint8_t red, boost::uint8_t green,
			  boost::uint8_t blue, boost::uint8_t alpha);

		// The uint32_t must be in the form of [rrggbbaa].
		color(boost::uint32_t value);

		Buffer serialize() const;
	};

	/**
		An unsigned 64-bit value, used to represent a unique ID for a game
		object.
	*/
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

		Buffer serialize() const;
	};

	/**
		A meta-parameter, used to build dynamic structures. Sub-parameters must
		be added to a blob, which then recursively serializes then combines
		them.
	*/
	class blob : public Parameter
	{
	private:
		boost::uint32_t elementSize;
		boost::uint32_t elementCount;
		std::vector<boost::uint8_t> elementData;

	public:
		blob(boost::uint32_t elementCount, boost::uint32_t elementSize);
		void add_param(const Parameter& param);
		Buffer serialize() const;
	};

	/**
		A three dimensional vector represented as [x, y, z]. This is usually
		used to store velocity and acceleration.
	*/
	class vector : public Parameter
	{
	private:
		typedef boost::tuple<boost::uint16_t, boost::uint16_t, boost::uint16_t> Vec;
		Vec value;

	public:
		vector(boost::uint16_t x, boost::uint16_t y, boost::uint16_t z);
		vector(const Vec& value);

		Buffer serialize() const;
	};

	/**
		A signed, 8-bit integer value.
	*/
	class int8 : public Parameter
	{
	private:
		boost::int8_t value;

	public:
		int8(boost::int8_t value);
		Buffer serialize() const;
	};

	/**
		An unsigned, 8-bit integer value.
	*/
	class uint8 : public Parameter
	{
	private:
		boost::uint8_t value;

	public:
		uint8(boost::uint8_t value);
		Buffer serialize() const;
	};

	/**
		A signed, 16-bit integer value.
	*/
	class int16 : public Parameter
	{
	private:
		boost::int16_t value;

	public:
		int16(boost::int16_t value);
		Buffer serialize() const;
	};

	/**
		An unsigned, 16-bit integer value.
	*/
	class uint16 : public Parameter
	{
	private:
		boost::uint16_t value;

	public:
		uint16(boost::uint16_t value);
		Buffer serialize() const;
	};

}
}
