#include <test.h>
#include <cockpit/packet/Registry.h>

#include <cstddef>

static void test_no_handler_for_call()
{
	cockpit::packet::Registry r;

	r.dispatch(531 /* Admin_Hide */, NULL, 0);
}

static void test_invalid_command_id_and_no_OnFailedParse()
{
	cockpit::packet::Registry r;

	r.dispatch(0x1337, NULL, 0);
}

int test_main(int, char**)
{
	test_no_handler_for_call();
	test_invalid_command_id_and_no_OnFailedParse();

	return 0;
}
