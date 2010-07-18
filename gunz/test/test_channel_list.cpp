#include <gtest/gtest.h>

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

TEST(channel_list, addition_and_removal)
{
	MockSanta santa;
	ChannelList cl;

	cl.Add(Channel(Channel::Traits(1, "abc", 0, Channel::CR_ELITE, Channel::CT_GENERAL, 0, 0)));
	cl.Add(Channel(Channel::Traits(2, "def", 0, Channel::CR_ELITE, Channel::CT_GENERAL, 0, 0)));

	const std::vector<Channel> lst(cl.Clone());

	EXPECT_EQ(unsigned(2), lst.size());

	EXPECT_EQ(MUID(1), cl.Find(bind(has_uid_of, 1, _1))->GetTraits().uid);
	EXPECT_EQ(MUID(2), cl.Find(bind(has_uid_of, 2, _1))->GetTraits().uid);

	EXPECT_TRUE(cl.Remove(make_from_uid(1)));
	EXPECT_EQ(unsigned(1), cl.Clone().size());

	EXPECT_TRUE(cl.Remove(make_from_uid(2)));
	EXPECT_EQ(unsigned(0), cl.Clone().size());

	// There is no channel 3!
	EXPECT_FALSE(cl.Remove(make_from_uid(3)));
}
