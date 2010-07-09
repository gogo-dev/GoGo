#include <test.h>
#include <gunz/ChannelList.h>
#include <gunz/MUIDSanta.h>

#include <boost/bind.hpp>

using namespace boost;
using namespace gunz;

// That is, until we can get a REAL mock santa in da haus ;)
typedef MUIDSanta MockSanta;

static bool has_uid_of(MUID uid, const Channel& ct)
{
	return uid == ct.GetTraits().uid;
}

static Channel make_from_uid(MUID uid)
{
	Channel::Traits traits;
	traits.uid = uid;
	return Channel(traits);
}

static void test_addition_and_removal()
{
	MockSanta santa;
	ChannelList cl;

	cl.Add(Channel(Channel::Traits(1, "abc", 0, Channel::CR_ELITE, Channel::CT_GENERAL, 0, 0)));
	cl.Add(Channel(Channel::Traits(2, "def", 0, Channel::CR_ELITE, Channel::CT_GENERAL, 0, 0)));

	const std::vector<Channel> lst(cl.Clone());

	check_equal(lst.size(), static_cast<size_t>(2));

	check_equal(cl.Find(bind(has_uid_of, 1, _1))->GetTraits().uid, static_cast<MUID>(1));
	check_equal(cl.Find(bind(has_uid_of, 2, _1))->GetTraits().uid, static_cast<MUID>(2));

	BOOST_CHECK(cl.Remove(make_from_uid(1)));
	check_equal(cl.Clone().size(), static_cast<size_t>(1));

	BOOST_CHECK(cl.Remove(make_from_uid(2)));
	check_equal(cl.Clone().size(), static_cast<size_t>(0));

	// There is no channel 3!
	BOOST_CHECK(!cl.Remove(make_from_uid(3)));
}

int test_main(int, char**)
{
	test_addition_and_removal();

	return 0;
}
