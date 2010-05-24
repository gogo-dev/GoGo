#include <ostream>
#include <vector>

#include <boost/cstdint.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/test/minimal.hpp>

#include "../src/PacketParameters.h"
#include "../src/PacketParameters.cpp"

using namespace boost;
using namespace packet;

// Counts the number of elements in an array.
#define countof(arr) \
	(sizeof(arr)/sizeof((arr)[0]))

static std::vector<uint8_t> arr_to_vec(const uint8_t* arr, size_t len)
{
	std::vector<uint8_t> retVal;

	for(size_t i = 0; i < len; ++i)
		retVal.push_back(arr[i]);

	return retVal;
}

static tuple<char, char> hexify(uint8_t num)
{
	static const char* hexChars = "0123456789ABCDEF";
	return make_tuple(
		hexChars[(num >> 8) & 0x0F],
		hexChars[(num >> 0) & 0x0F]);
}

//template <typename Elem>
std::ostream& operator<<(std::ostream& stream,
                         const std::vector<unsigned char>& toOutput)
{
	stream << "[";

	for(std::vector<unsigned char>::const_iterator i = toOutput.begin(); i != toOutput.end(); ++i)
	{
		tuple<char, char> splitNum = hexify(*i);
		stream << " " << splitNum.get<0>() << splitNum.get<1>();
	}

	stream << " ]";

	return stream;
}


static void test_int32()
{
	int32 packit(0x12345678);

	uint8_t expected[] = {
		0x78, 0x56, 0x34, 0x12
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
	BOOST_CHECK(packit.get_type() == 0x00);
}

static void test_uint32()
{
	uint32 packit(0x12345678);

	uint8_t expected[] = {
		0x78, 0x56, 0x34, 0x12
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
	BOOST_CHECK(packit.get_type() == 0x01);
}

static void test_floating_point()
{
	// Serialization testing skipped because floats are stupid and
	// unrepresentable.
	floating_point packit(0.3f);

	BOOST_CHECK(packit.get_type() == 0x02);
}

static void test_boolean()
{
	packet::boolean packit(true);

	uint8_t expected[] = {
		0x01
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
	BOOST_CHECK(packit.get_type() == 0x03);
}

static void test_string()
{
	packet::string packit("test");

	uint8_t expected[] = {
		0x05, 0x00, 't', 'e', 's', 't', 0x00
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
	BOOST_CHECK(packit.get_type() == 0x04);
}

static void test_position()
{
	// Fucking floating-points and their untestability. serialization() tests omitted.
	BOOST_CHECK(position(1.0f, 2.0f, 3.0f).get_type() == 0x06);
}

static void test_direction()
{
	// Same story as for test_position.
	BOOST_CHECK(direction(1.0f, 2.0f, 3.0f).get_type() == 0x07);
}

static void test_color()
{
	color packit1(0x01, 0x02, 0x03, 0x04);
	color packit2(0x01020304);

	BOOST_CHECK(packit1.get_type() == 0x08);

	uint8_t expected[] = {
		0x01, 0x02, 0x03, 0x04
	};

	BOOST_CHECK(packit1.serialize() == arr_to_vec(expected, countof(expected)));
	BOOST_CHECK(packit2.serialize() == arr_to_vec(expected, countof(expected)));
}

static void test_MUID()
{
	MUID packit1(0x11223344, 0x55667788);
	MUID packit2(0x1122334455667788);

	BOOST_CHECK(packit1.get_type() == 0x09);

	uint8_t expected[] = {
		0x88, 0x77, 0x66, 0x55,
		0x44, 0x33, 0x22, 0x11
	};

	BOOST_CHECK(packit1.serialize() == arr_to_vec(expected, countof(expected)));
	BOOST_CHECK(packit2.serialize() == arr_to_vec(expected, countof(expected)));
}

static void test_blob()
{
	// TODO(Clark): Write the tests for the blob class.
}

static void test_vector()
{
	packet::vector packit(0x0011, 0x2233, 0x4455);

	BOOST_CHECK(packit.get_type() == 0x0B);

	uint8_t expected[] = {
		0x11, 0x00, 0x33, 0x22, 0x55, 0x44
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
}

static void test_uint8()
{
	uint8 packit(0x01);

	BOOST_CHECK(packit.get_type() == 0x0C);

	uint8_t expected[] = {
		0x01
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
}

static void test_int16()
{
	int16 packit(0x0123);

	BOOST_CHECK(packit.get_type() == 0x0D);

	uint8_t expected[] = {
		0x23, 0x01
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
}

static void test_uint16()
{
	uint16 packit(0x0123);

	BOOST_CHECK(packit.get_type() == 0x0E);

	uint8_t expected[] = {
		0x23, 0x01
	};

	BOOST_CHECK(packit.serialize() == arr_to_vec(expected, countof(expected)));
}

int test_main(int, char**)
{
	// Any time a test function is added, don't forget to call it from here :)
	test_int32();
	test_uint32();
	test_floating_point();
	test_boolean();
	test_string();
	test_position();
	test_direction();
	test_color();
	test_MUID();
	test_blob();
	test_vector();
	test_uint8();
	test_int16();
	test_uint16();

	return 0;
}
