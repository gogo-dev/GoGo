#include <gtest/gtest.h>
#include <gtest/array_check.h>

#include <util/memory.h>

using namespace boost;

#define countof(x)	(sizeof(x)/sizeof((x)[0]))

TEST(memory, memcpy)
{
	int sourceArray[] = {
		0x12345678, 0x87654321, 0x11111111, 0x22222222
	};

	int destArray[countof(sourceArray)] = { 0 };

	int* result = memory::copy(destArray, sourceArray, sizeof(sourceArray));

	EXPECT_EQ(destArray, result);

	check_arrays(sourceArray, destArray);
}

TEST(memory, mempcpy)
{
	int sourceArray[] = {
		0xAABBCCDD, 0x11223344, 0xFFEEDDCC, 0xDEADBEEF
	};

	int destArray[countof(sourceArray)] = { 0 };

	int* result = memory::pcopy(destArray, sourceArray, sizeof(sourceArray));

	EXPECT_EQ(destArray + countof(destArray), result);

	check_arrays(sourceArray, destArray);
}

TEST(memory, memset)
{
	uint8_t sourceArray[] = {
		0x11, 0x11, 0x11, 0x11, 0x11
	};

	uint8_t expected[] = {
		0x00, 0x00, 0x00, 0x00, 0x11
	};

	uint8_t* result = memory::set(sourceArray, 0x00, 4);

	EXPECT_EQ(sourceArray, result);

	check_arrays(sourceArray, expected);
}
