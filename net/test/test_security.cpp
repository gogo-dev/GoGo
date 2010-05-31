#include <test.h>
#include "../src/security.cpp"

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

		check_equal(extract_int32(buffer, &ptr, countof(buffer)), (int32_t)0x00EFCDAB);
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), (int32_t)0x44332211);
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), (int32_t)0x88776655);
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), (int32_t)0xCCBBAA99);
		check_equal(extract_int32(buffer, &ptr, countof(buffer)), (int32_t)0x00FFEEDD);

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

		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), (uint32_t)0x00EFCDAB);
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), (uint32_t)0x44332211);
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), (uint32_t)0x88776655);
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), (uint32_t)0xCCBBAA99);
		check_equal(extract_uint32(buffer, &ptr, countof(buffer)), (uint32_t)0x00FFEEDD);


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
		0x05, 0x00, 't', 'e', 's', 't', '\0',
		0x02, 0x00, 'a', '\0',
		0x0D, 0x00, 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0'
	};

	const uint8_t* ptr = buffer + 1;	// Compensate for the padding.

	try {
		check_equal(extract_string(buffer, &ptr, countof(buffer)), string("test"));
		check_equal(extract_string(buffer, &ptr, countof(buffer)), string("a"));
		check_equal(extract_string(buffer, &ptr, countof(buffer)), string("hello world!"));

		succeeded = true;
	} catch(ParseFailed) {
		succeeded = false;
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
	test_string_kore();	// How does the string respond to Kore?
	test_string_non_null_terminated();
	test_string_badly_null_terminated();

	return 0;
}