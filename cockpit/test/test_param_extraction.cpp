#include <gtest/gtest.h>

#include "../src/packet/security.cpp"

TEST(int32, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x08, 0x99, 0xAA, 0xBB, 0x0C,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		EXPECT_EQ(extract_int32(buffer, &ptr, sizeof(buffer)), 0x00EFCDAB);
		EXPECT_EQ(extract_int32(buffer, &ptr, sizeof(buffer)), 0x44332211);
		EXPECT_EQ(extract_int32(buffer, &ptr, sizeof(buffer)), 0x08776655);
		EXPECT_EQ(extract_int32(buffer, &ptr, sizeof(buffer)), 0x0CBBAA99);
		EXPECT_EQ(extract_int32(buffer, &ptr, sizeof(buffer)), 0x00FFEEDD);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	EXPECT_TRUE(succeeded);
}

TEST(int32, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_int32(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	EXPECT_TRUE(succeeded);
}

TEST(uint32, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		EXPECT_EQ(extract_uint32(buffer, &ptr, sizeof(buffer)), 0x00EFCDAB);
		EXPECT_EQ(extract_uint32(buffer, &ptr, sizeof(buffer)), 0x44332211);
		EXPECT_EQ(extract_uint32(buffer, &ptr, sizeof(buffer)), 0x88776655);
		EXPECT_EQ(extract_uint32(buffer, &ptr, sizeof(buffer)), 0xCCBBAA99);
		EXPECT_EQ(extract_uint32(buffer, &ptr, sizeof(buffer)), 0x00FFEEDD);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	EXPECT_TRUE(succeeded);
}

TEST(uint32, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_uint32(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	EXPECT_TRUE(succeeded);
}

TEST(float, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		// We can't do comparisons, because floats are uncomparable and the most
		// un-standard thing evar.
		extract_float(buffer, &ptr, sizeof(buffer));
		extract_float(buffer, &ptr, sizeof(buffer));
		extract_float(buffer, &ptr, sizeof(buffer));
		extract_float(buffer, &ptr, sizeof(buffer));
		extract_float(buffer, &ptr, sizeof(buffer));

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	EXPECT_TRUE(succeeded);
}

TEST(float, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_float(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	EXPECT_TRUE(succeeded);
}

TEST(bool, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		// We can't do comparisons, because floats are uncomparable and the most
		// un-standard thing evar.
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), true);
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), true);
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), true);
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), false);
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), true);
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), true);
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), true);
		EXPECT_EQ(extract_bool(buffer, &ptr, sizeof(buffer)), false);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	EXPECT_TRUE(succeeded);
}

TEST(bool, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_bool(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	EXPECT_TRUE(succeeded);
}

TEST(string, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, // Just some padding to see what happens =P
		0x06, 0x00, 't', 'e', 's', 't', 0x00, 0x0B,
		0x03, 0x00, 'a', 0x00, 0x0B,
		0x0E, 0x00, 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', 0x00, 0x0B
	};

	const uint8_t* ptr = buffer + 1;	// Compensate for the padding.

	try {
		EXPECT_EQ(extract_string(buffer, &ptr, sizeof(buffer)), string("test"));
		EXPECT_EQ(extract_string(buffer, &ptr, sizeof(buffer)), string("a"));
		EXPECT_EQ(extract_string(buffer, &ptr, sizeof(buffer)), string("hello world!"));

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

// How does the string extractor respond to Kore?
// Kore sets the string's length header to greater
// than the actual length of the string, wreaking
// havoc with the stack.
TEST(string, kore)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x07, 0x00, 't', 'e', 's', 't', '\0', '\0'
	};

	const uint8_t* ptr = buffer;

	try {
		extract_string(buffer, &ptr, sizeof(buffer));
		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(string, non_null_terminated)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x04, 0x00, 't', 'e', 's', 't'
	};

	const uint8_t* ptr = buffer;

	try {
		extract_string(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

// Gunz does this. How gay is that?
TEST(string, badly_null_terminated)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x06, 0x00, 't', 'e', 's', 't', '\0', 'a'
	};

	const uint8_t* ptr = buffer;

	try {
		EXPECT_EQ(string("test"), extract_string(buffer, &ptr, sizeof(buffer)));
		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(position, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_position(buffer, &ptr, sizeof(buffer));

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(position, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_position(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(direction, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_direction(buffer, &ptr, sizeof(buffer));

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(direction, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_direction(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(color, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		EXPECT_EQ(extract_color(buffer, &ptr, sizeof(buffer)), 0x00EFCDAB);
		EXPECT_EQ(extract_color(buffer, &ptr, sizeof(buffer)), 0x44332211);
		EXPECT_EQ(extract_color(buffer, &ptr, sizeof(buffer)), 0x88776655);
		EXPECT_EQ(extract_color(buffer, &ptr, sizeof(buffer)), 0xCCBBAA99);
		EXPECT_EQ(extract_color(buffer, &ptr, sizeof(buffer)), 0x00FFEEDD);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	EXPECT_TRUE(succeeded);
}

TEST(color, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_color(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	EXPECT_TRUE(succeeded);
}

TEST(MUID, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		EXPECT_EQ(extract_MUID(buffer, &ptr, sizeof(buffer)), 0x00EFCDAB44332211);
		EXPECT_EQ(extract_MUID(buffer, &ptr, sizeof(buffer)), 0x88776655CCBBAA99);

		EXPECT_EQ(ptr, buffer + sizeof(buffer) - 4);

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(MUID, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer;

	try {
		extract_MUID(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	EXPECT_TRUE(succeeded);
}

TEST(blob, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x10, 0x00, 0x00, 0x00,	// totalSize
		0x04, 0x00, 0x00, 0x00, // elementSize
		0x02, 0x00, 0x00, 0x00, // elementCount
		0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88
	};

	const uint8_t* ptr = buffer;

	try {
		//    data    count    size
		tuple<Buffer, size_t, size_t> blob(extract_blob(buffer, &ptr, sizeof(buffer)));

		EXPECT_EQ(blob.get<1>(), 2);
		EXPECT_EQ(blob.get<2>(), 4);
		EXPECT_EQ(blob.get<0>().length(), 8);
		EXPECT_EQ(*reinterpret_cast<const uint64_t*>(blob.get<0>().data()), 0x8877665544332211);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(blob, kore)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x0D, 0x00, 0x00, 0x00, // totalSize
		0x02, 0x00, 0x00, 0x00, // elementSize
		0x02, 0x00, 0x00, 0x00, // elementCount
		0x00, 0x00, 0x00, 0x00
	};

	const uint8_t* ptr = buffer;

	try {
		extract_blob(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(blob, corrupt_size)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x0C, 0x00, 0x00, 0x00, // totalSize
		0x03, 0x00, 0x00, 0x00, // elementSize
		0x02, 0x00, 0x00, 0x00, // elementCount
		0x00, 0x00, 0x00, 0x00
	};

	const uint8_t* ptr = buffer;

	try {
		extract_blob(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(blob, corrupt_count)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x0C, 0x00, 0x00, 0x00, // totalSize
		0x02, 0x00, 0x00, 0x00, // elementSize
		0x03, 0x00, 0x00, 0x00, // elementCount
		0x00, 0x00, 0x00, 0x00
	};

	const uint8_t* ptr = buffer;

	try {
		extract_blob(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(int8, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer;

	try {
		EXPECT_EQ(extract_int8(buffer, &ptr, sizeof(buffer)), 0x55);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(int8, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer + 1;

	try {
		extract_int8(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(uint8, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer;

	try {
		EXPECT_EQ(extract_uint8(buffer, &ptr, sizeof(buffer)), 0x55);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(uint8, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer + 1;

	try {
		extract_uint8(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(int16, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		EXPECT_EQ(extract_int16(buffer, &ptr, sizeof(buffer)), 0x2211);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(int16, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11
	};

	const uint8_t* ptr = buffer;

	try {
		extract_int16(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

TEST(uint16, clean_extraction)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		EXPECT_EQ(extract_uint16(buffer, &ptr, sizeof(buffer)), 0x2211);

		EXPECT_EQ(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	EXPECT_TRUE(succeeded);
}

TEST(uint16, read_off_end)
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11
	};

	const uint8_t* ptr = buffer;

	try {
		extract_uint16(buffer, &ptr, sizeof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	EXPECT_TRUE(succeeded);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
