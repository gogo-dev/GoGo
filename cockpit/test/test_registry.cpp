#include <gtest/gtest.h>

#include <cockpit/packet/Registry.h>

#include <cstddef>

TEST(dispatch, no_segfault_when_lacking_handler)
{
	cockpit::packet::Registry r;

	r.dispatch(531 /* Admin_Hide */, NULL, 0);
}

TEST(dispatch, no_segfault_with_no_OnFailedParse)
{
	cockpit::packet::Registry r;

	r.dispatch(0x1337, NULL, 0);
}
