#include <test.h>
#include <gunz/MUIDSanta.h>

using namespace gunz;

static void test_santa_starts_at_1()
{
	MUIDSanta s;

	check_equal(s.get(), static_cast<MUID>(1));
}

static void test_santa_hands_consecutive_numbers()
{
	MUIDSanta s;

	MUID first = s.get();
	MUID second = s.get();

	check_equal(second, first + 1);
}

int test_main(int, char**)
{
	test_santa_starts_at_1();
	test_santa_hands_consecutive_numbers();

	return 0;
}
