#include <test.h>
#include "../src/packet/security.cpp"

static void test_int32_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		check_equal(extract_int32(buffer, &ptr, countof(buffer)), static_cast<int32_t>(0x00EFCDAB));
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), static_cast<int32_t>(0x44332211));
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), static_cast<int32_t>(0x88776655));
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), static_cast<int32_t>(0xCCBBAA99));
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), static_cast<int32_t>(0x00FFEEDD));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	BOOST_CHECK(succeeded);
}

static void test_int32_read_off_end()
{
	bool succeeded;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_int32(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	BOOST_CHECK(succeeded);
}

static void test_uint32_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x00EFCDAB));
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x44332211));
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x88776655));
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0xCCBBAA99));
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x00FFEEDD));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	BOOST_CHECK(succeeded);
}

static void test_uint32_read_off_end()
{
	bool succeeded;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_uint32(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	BOOST_CHECK(succeeded);
}

static void test_float_clean_extraction()
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
		extract_float(buffer, &ptr, countof(buffer));
		extract_float(buffer, &ptr, countof(buffer));
		extract_float(buffer, &ptr, countof(buffer));
		extract_float(buffer, &ptr, countof(buffer));
		extract_float(buffer, &ptr, countof(buffer));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	BOOST_CHECK(succeeded);
}

static void test_float_read_off_end()
{
	bool succeeded;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_float(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	BOOST_CHECK(succeeded);
}

static void test_bool_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		// We can't do comparisons, because floats are uncomparable and the most
		// un-standard thing evar.
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), true);
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), true);
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), true);
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), false);
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), true);
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), true);
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), true);
		check_equal(extract_bool(buffer, &ptr, countof(buffer)), false);

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	BOOST_CHECK(succeeded);
}

static void test_bool_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_bool(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	BOOST_CHECK(succeeded);
}

static void test_string_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, // Just some padding to see what happens =P
		0x06, 0x00, 't', 'e', 's', 't', 0x00, 0x00,
		0x03, 0x00, 'a', 0x00, 0x00,
		0x0E, 0x00, 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', 0x00, 0x00
	};

	const uint8_t* ptr = buffer + 1;	// Compensate for the padding.

	try {
		check_equal(extract_string(buffer, &ptr, countof(buffer)), string("test"));
		check_equal(extract_string(buffer, &ptr, countof(buffer)), string("a"));
		check_equal(extract_string(buffer, &ptr, countof(buffer)), string("hello world!"));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

// How does the string extractor respond to Kore?
// Kore sets the string's length header to greater
// than the actual length of the string, wreaking
// havoc with the stack.
static void test_string_kore()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x07, 0x00, 't', 'e', 's', 't', '\0', '\0'
	};

	const uint8_t* ptr = buffer;

	try {
		extract_string(buffer, &ptr, countof(buffer));
		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_string_non_null_terminated()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x04, 0x00, 't', 'e', 's', 't'
	};

	const uint8_t* ptr = buffer;

	try {
		extract_string(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_string_badly_null_terminated()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x06, 0x00, 't', 'e', 's', 't', '\0', 'a'
	};

	const uint8_t* ptr = buffer;

	try {
		extract_string(buffer, &ptr, countof(buffer));
		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_position_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_position(buffer, &ptr, countof(buffer));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_position_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_position(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_direction_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_direction(buffer, &ptr, countof(buffer));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_direction_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x00, 0x00, 0x00,
		0x11, 0x11, 0x11, 0x11,
		0x22, 0x22, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		extract_direction(buffer, &ptr, countof(buffer));
		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_color_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		check_equal(extract_color(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x00EFCDAB));
		check_equal(extract_color(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x44332211));
		check_equal(extract_color(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x88776655));
		check_equal(extract_color(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0xCCBBAA99));
		check_equal(extract_color(buffer, &ptr, countof(buffer)), static_cast<uint32_t>(0x00FFEEDD));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
	}

	BOOST_CHECK(succeeded);
}

static void test_color_read_off_end()
{
	bool succeeded;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer + 1;	// So we read off by one, of course!

	try {
		extract_color(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	BOOST_CHECK(succeeded);
}

static void test_MUID_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0xAB, 0xCD, 0xEF, 0x00, 0x11, 0x22, 0x33, 0x44,
		0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
		0xDD, 0xEE, 0xFF, 0x00
	};

	try {
		const uint8_t* ptr = buffer;

		check_equal(extract_MUID(buffer, &ptr, countof(buffer)), static_cast<uint64_t>(0x4433221100EFCDAB));
		check_equal(extract_MUID(buffer, &ptr, countof(buffer)), static_cast<uint64_t>(0xCCBBAA9988776655));

		check_equal(ptr, buffer + sizeof(buffer) - 4);

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_MUID_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x00, 0x11, 0x22, 0x33
	};

	const uint8_t* ptr = buffer;

	try {
		extract_MUID(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;	// The parse SHOULD fail, since we're reading off the end.
	}

	BOOST_CHECK(succeeded);
}

static void test_blob_clean_extraction()
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
		tuple<Buffer, size_t, size_t> blob(extract_blob(buffer, &ptr, countof(buffer)));

		check_equal(blob.get<1>(), static_cast<size_t>(2));
		check_equal(blob.get<2>(), static_cast<size_t>(4));
		check_equal(blob.get<0>().length(), static_cast<size_t>(8));
		check_equal(*reinterpret_cast<const uint64_t*>(blob.get<0>().data()), static_cast<uint64_t>(0x8877665544332211));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_blob_kore()
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
		extract_blob(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_blob_corrupt_size()
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
		extract_blob(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_blob_corrupt_count()
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
		extract_blob(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_int8_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer;

	try {
		check_equal(extract_int8(buffer, &ptr, countof(buffer)), static_cast<int8_t>(0x55));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_int8_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer + 1;

	try {
		extract_int8(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_uint8_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer;

	try {
		check_equal(extract_uint8(buffer, &ptr, countof(buffer)), static_cast<uint8_t>(0x55));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_uint8_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x55
	};

	const uint8_t* ptr = buffer + 1;

	try {
		extract_uint8(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_int16_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		check_equal(extract_int16(buffer, &ptr, countof(buffer)), static_cast<int16_t>(0x2211));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_int16_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11
	};

	const uint8_t* ptr = buffer;

	try {
		extract_int16(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

static void test_uint16_clean_extraction()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11, 0x22
	};

	const uint8_t* ptr = buffer;

	try {
		check_equal(extract_uint16(buffer, &ptr, countof(buffer)), static_cast<uint16_t>(0x2211));

		check_equal(ptr, buffer + sizeof(buffer));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
	}

	BOOST_CHECK(succeeded);
}

static void test_uint16_read_off_end()
{
	bool succeeded = false;

	const uint8_t buffer[] = {
		0x11
	};

	const uint8_t* ptr = buffer;

	try {
		extract_uint16(buffer, &ptr, countof(buffer));

		succeeded = false;
	} catch(ParseFailed) {
		succeeded = true;
	}

	BOOST_CHECK(succeeded);
}

int test_main(int, char**)
{
	test_int32_clean_extraction();
	test_int32_read_off_end();

	test_uint32_clean_extraction();
	test_uint32_read_off_end();

	test_float_clean_extraction();
	test_float_read_off_end();

	test_bool_clean_extraction();
	test_bool_read_off_end();

	test_string_clean_extraction();
	test_string_kore();
	test_string_non_null_terminated();
	test_string_badly_null_terminated();

	test_position_clean_extraction();
	test_position_read_off_end();

	test_direction_clean_extraction();
	test_direction_read_off_end();

	test_color_clean_extraction();
	test_color_read_off_end();

	test_MUID_clean_extraction();
	test_MUID_read_off_end();

	test_blob_clean_extraction();
	test_blob_kore();
	test_blob_corrupt_size();
	test_blob_corrupt_count();

	test_int8_clean_extraction();
	test_int8_read_off_end();

	test_uint8_clean_extraction();
	test_uint8_read_off_end();

	test_int16_clean_extraction();
	test_int16_read_off_end();

	test_uint16_clean_extraction();
	test_uint16_read_off_end();

	return 0;
}
