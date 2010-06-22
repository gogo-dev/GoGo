#include <test.h>
#include <cockpit/packet/Registry.h>

#include <cstddef>

void test_no_handler_for_call()
{
	cockpit::packet::Registry r;

	r.dispatch(531 /* Admin_Hide */, NULL, 0);
}

int test_main(int, char**)
{
	test_no_handler_for_call();

	return 0;
}
