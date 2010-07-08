#include <test.h>
#include <gunz/ChannelList.h>
#include <gunz/MUIDSanta.h>

#include <boost/bind.hpp>

using namespace boost;
using namespace gunz;

// That is, until we can get a REAL mock santa in da haus ;)
typedef MUIDSanta MockSanta;

bool has_uid_of(MUID uid, const ChannelTraits& ct)
{
	return uid == ct.uid;
}

#include <cstdio>

static void test_addition_and_removal()
{
	MockSanta santa;
	ChannelList cl(&santa);

	cl.AddChannel(ChannelTraits(1, "abc", 0, CR_ELITE, CT_GENERAL, 0, 0));
	cl.AddChannel(ChannelTraits(2, "def", 0, CR_ELITE, CT_GENERAL, 0, 0));

	std::vector<ChannelTraits> lst(cl.GetChannelList());

	check_equal(lst.size(), static_cast<size_t>(2));

	check_equal(cl.LookupChannel(bind(has_uid_of, 1, _1)).uid, static_cast<MUID>(1));
	check_equal(cl.LookupChannel(bind(has_uid_of, 2, _1)).uid, static_cast<MUID>(2));

	BOOST_CHECK(cl.RemoveChannel(1));
	check_equal(cl.GetChannelList().size(), static_cast<size_t>(1));

	BOOST_CHECK(cl.RemoveChannel(2));
	check_equal(cl.GetChannelList().size(), static_cast<size_t>(0));

	// There is no channel 3!
	BOOST_CHECK(!cl.RemoveChannel(3));
}

int test_main(int, char**)
{
	test_addition_and_removal();

	return 0;
}
