#include <cockpit/packet/Parameters.h>

#include <test.h>

using namespace boost;
using namespace cockpit::packet;

static void test_int32()
{
	int32 packit(0x12345678);

	uint8_t expected[] = {
		0x78, 0x56, 0x34, 0x12
	};

	check_array_equal(packit.serialize().data(), expected, countof(expected));
	BOOST_CHECK(packit.get_type() == 0x00);
}

static void test_uint32()
{
	uint32 packit(0x12345678);

	uint8_t expected[] = {
		0x78, 0x56, 0x34, 0x12
	};

	check_array_equal(packit.serialize().data(), expected, countof(expected));
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
	cockpit::packet::boolean packit(true);

	uint8_t expected[] = {
		0x01
	};

	check_array_equal(packit.serialize().data(), expected, countof(expected));
	BOOST_CHECK(packit.get_type() == 0x03);
}

static void test_blob_string()
{
	blob_string packit("test", 10);
	Buffer serialized = packit.serialize();

	uint8_t expected[] = {
		't', 'e', 's', 't', 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00
	};

	check_equal(serialized.length(), countof(expected));
	check_array_equal(packit.serialize().data(), expected, countof(expected));
}

static void test_string()
{
	cockpit::packet::string packit("test");
	Buffer serialized = packit.serialize();

	uint8_t expected[] = {
		0x06, 0x00, 't', 'e', 's', 't', 0x00, 0x00
	};

	check_equal(serialized.length(), sizeof(expected));

	check_array_equal(serialized.data(), expected, countof(expected));
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

	check_array_equal(packit1.serialize().data(), expected, countof(expected));
	check_array_equal(packit2.serialize().data(), expected, countof(expected));
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

	check_array_equal(packit1.serialize().data(), expected, countof(expected));
	check_array_equal(packit2.serialize().data(), expected, countof(expected));
}

static void test_blob()
{
	uint8_t expected[] = {
		28, 0, 0, 0, //totalSize
		20, 0, 0, 0, //elementSize
		1,  0, 0, 0, //elementCount

		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0
	};

	blob packit(1, 20);

	for(int i = 0; i < 20; ++i)
		packit.add_param(uint8(0));

	check_array_equal(packit.serialize().data(), expected, countof(expected));

}

static void test_int8()
{
	int8 packit(0x01);

	BOOST_CHECK(packit.get_type() == 0x0B);

	int8_t expected[] = {
		0x01
	};

	check_array_equal(packit.serialize().data(), expected, countof(expected));
}

static void test_uint8()
{
	uint8 packit(0x01);

	BOOST_CHECK(packit.get_type() == 0x0C);

	uint8_t expected[] = {
		0x01
	};

	check_array_equal(packit.serialize().data(), expected, countof(expected));
}

static void test_int16()
{
	int16 packit(0x0123);

	BOOST_CHECK(packit.get_type() == 0x0D);

	uint8_t expected[] = {
		0x23, 0x01
	};

	check_array_equal(packit.serialize().data(), expected, countof(expected));
}

static void test_uint16()
{
	uint16 packit(0x0123);

	BOOST_CHECK(packit.get_type() == 0x0E);

	uint8_t expected[] = {
		0x23, 0x01
	};

	check_array_equal(packit.serialize().data(), expected, countof(expected));
}

int test_main(int, char**)
{
	// Any time a test function is added, don't forget to call it from here :)
	test_int32();
	test_uint32();
	test_floating_point();
	test_boolean();

	test_blob_string();
	test_string();
	test_position();
	test_direction();
	test_color();
	test_MUID();
	test_blob();
	test_int8();
	test_uint8();
	test_int16();
	test_uint16();

	return 0;
}
