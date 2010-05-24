#include "../src/PacketCrypt.h"
#include "../src/PacketCrypt.cpp"

#include <ostream>
#include <string>
#include <cassert>

#include <boost/cstdint.hpp>
#include <boost/test/minimal.hpp>

#include "test.h"

using namespace std;
using namespace boost;
using namespace packet;

// TODO(Jacob): Write the damn encryption tests!
static void test_encrypt()
{
	uint8_t arrA[] = {
		0x11, 0x22, 0x33, 0x44
	};

	uint8_t arrB[] = {
		0x55, 0x66, 0x77, 0x88
	};

	check_array_equal(arrA, arrB, countof(arrA));
}

static void test_decrypt()
{
}

int test_main(int, char**)
{
	// Don't forget to call your test functions from here!
	test_encrypt();
	test_decrypt();

	return 0;
}
