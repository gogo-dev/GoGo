#include <test.h>
#include "../src/memory.h"

using namespace boost;

void test_memcpy()
{
	int sourceArray[] = {
		0x12345678, 0x87654321, 0x11111111, 0x22222222
	};

	int destArray[countof(sourceArray)] = { 0 };

	check_array_equal(memory::copy(destArray, sourceArray, sizeof(sourceArray)), sourceArray, sizeof(sourceArray));
}

#include <iostream>

void test_mempcpy()
{
	int sourceArray[] = {
		0xAABBCCDD, 0x11223344, 0xFFEEDDCC, 0xDEADBEEF
	};

	int destArray[countof(sourceArray)] = { 0 };

	int* result = memory::pcopy(destArray, sourceArray, sizeof(sourceArray));

	check_array_equal(sourceArray, destArray, sizeof(sourceArray));
	BOOST_CHECK(result == (destArray + countof(destArray)));
}

int test_main(int, char**)
{
	test_memcpy();
	test_mempcpy();

	return 0;
}
