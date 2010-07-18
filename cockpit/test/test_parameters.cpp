#include <gtest/gtest.h>
#include <gtest/array_check.h>

#include <cockpit/packet/Parameters.h>

using namespace boost;
using namespace cockpit::packet;

TEST(int32, serialization)
{
	int32 packit(0x12345678);

	uint8_t expected[] = {
		0x78, 0x56, 0x34, 0x12
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(int32, packet_type)
{
	EXPECT_EQ(0x00, int32(0).get_type());
}

TEST(uint32, serialization)
{
	uint32 packit(0x12345678);

	uint8_t expected[] = {
		0x78, 0x56, 0x34, 0x12
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());

	EXPECT_EQ(0x01, packit.get_type());
}

TEST(uint32, packet_type)
{
	EXPECT_EQ(0x01, uint32(0).get_type());
}

// Serialization testing skipped because floats are stupid and

// unrepresentable.
TEST(floating_point, packet_type)
{
	EXPECT_EQ(0x02, floating_point(0.3f).get_type());
}

TEST(boolean, serialization)
{
	cockpit::packet::boolean packit(true);

	uint8_t expected[] = {
		0x01
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(boolean, packet_type)
{
	EXPECT_EQ(0x03, cockpit::packet::boolean(false).get_type());
}

TEST(blob_string, serialization)
{
	blob_string packit("test", 10);

	uint8_t expected[] = {
		't', 'e', 's', 't', 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(string, serialization)
{
	cockpit::packet::string packit("test");

	uint8_t expected[] = {
		0x06, 0x00, 't', 'e', 's', 't', 0x00, 0x00
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(string, packet_type)
{
	EXPECT_EQ(0x04, cockpit::packet::string("").get_type());
}

// Fucking floating-points and their untestability. serialization() tests
// omitted for position and direction.

TEST(position, packet_type)
{
	EXPECT_EQ(0x06, position(1.0f, 2.0f, 3.0f).get_type());
}

TEST(direction, packet_type)
{
	EXPECT_EQ(0x07, direction(1.0f, 2.0f, 3.0f).get_type());
}

TEST(color, serialization_split)
{
	color packit(0x01, 0x02, 0x03, 0x04);

	uint8_t expected[] = {
		0x01, 0x02, 0x03, 0x04
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(color, serialization_condensed)
{
	color packit(0x01020304);

	uint8_t expected[] = {
		0x01, 0x02, 0x03, 0x04
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(color, packet_type)
{
	EXPECT_EQ(0x08, color(1, 2, 3, 4).get_type());
}

TEST(MUID, serialization_split)
{
	MUID packit(0x11223344, 0x55667788);

	uint8_t expected[] = {
		0x44, 0x33, 0x22, 0x11,
		0x88, 0x77, 0x66, 0x55
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(MUID, serialization_condensed)
{
	MUID packit(0x1122334455667788);

	uint8_t expected[] = {
		0x44, 0x33, 0x22, 0x11,
		0x88, 0x77, 0x66, 0x55
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(MUID, packet_type)
{
	EXPECT_EQ(0x09, MUID(0x1122334455667788).get_type());
}

TEST(blob, serialization)
{
	blob packit(1, 20);

	for(int i = 0; i < 20; ++i)
		packit.add_param(uint8(0));

	uint8_t expected[] = {
		28, 0, 0, 0, //totalSize
		20, 0, 0, 0, //elementSize
		1,  0, 0, 0, //elementCount

		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(blob, packet_type)
{
	EXPECT_EQ(0x0A, blob(0, 0).get_type());
}

TEST(int8, serialization)
{
	int8 packit(0x01);

	uint8_t expected[] = {
		0x01
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(int8, packet_type)
{
	EXPECT_EQ(0x0B, int8(0).get_type());
}

TEST(uint8, serialization)
{
	uint8 packit(0x01);

	uint8_t expected[] = {
		0x01
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(uint8, packet_type)
{
	EXPECT_EQ(0x0C, uint8(0).get_type());
}

TEST(int16, serialization)
{
	int16 packit(0x0123);

	uint8_t expected[] = {
		0x23, 0x01
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(int16, packet_type)
{
	EXPECT_EQ(0x0D, int16(0).get_type());
}

TEST(uint16, serialization)
{
	uint16 packit(0x0123);

	uint8_t expected[] = {
		0x23, 0x01
	};

	Buffer serialized = packit.serialize();

	check_arrays(expected, sizeof(expected), serialized.data(), serialized.length());
}

TEST(uint16, packet_type)
{
	EXPECT_EQ(0x0E, uint16(0).get_type());
}
