#include <gtest/gtest.h>

#include "../src/ChannelLoader.h"
#include "../src/ChannelLoader.cpp"

using namespace std;
using namespace boost;

// Handles everything but the edge cases. Lol.
TEST(channel_loader, default_xml)
{
	gunz::MUIDSanta s;
	vector<gunz::Channel::Traits> result = parse_channel_list(
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
		"<xml id=\"channel\">\n"
			"<channel name=\"Free Channel 1\" maxplayers=\"255\" rule=\"novice\" />\n"
			"<channel name=\"Free Channel 2\" maxplayers=\"255\" rule=\"novice\" />\n"
			"<channel name=\"Newbie Channel\" maxplayers=\"255\" rule=\"newbie\" maxlevel='10' />\n"
			"<channel name=\"Rookie Channel\" maxplayers=\"255\" rule=\"rookie\" minlevel='11' maxlevel='20' />\n"
			"<channel name=\"Veteran Channel\" maxplayers=\"255\" rule=\"mastery\" minlevel='21' />\n"
			"<channel name=\"Elite Channel\" maxplayers=\"255\" rule=\"elite\" minlevel='35' />\n"
		"</xml>\n",
		&s
	);

	ASSERT_EQ(unsigned(6), result.size());

	EXPECT_EQ(unsigned(1), result[0].uid);
	EXPECT_EQ("Free Channel 1", result[0].name);
	EXPECT_EQ(255, result[0].maxPlayers);
	EXPECT_EQ(gunz::Channel::CR_NOVICE, result[0].rule);
	EXPECT_EQ(gunz::Channel::CT_GENERAL, result[0].type);
	EXPECT_EQ(1, result[0].minLevel);
	EXPECT_EQ(255, result[0].maxLevel);

	EXPECT_EQ(unsigned(2), result[1].uid);
	EXPECT_EQ("Free Channel 2", result[1].name);
	EXPECT_EQ(255, result[1].maxPlayers);
	EXPECT_EQ(gunz::Channel::CR_NOVICE, result[1].rule);
	EXPECT_EQ(gunz::Channel::CT_GENERAL, result[1].type);
	EXPECT_EQ(1, result[1].minLevel);
	EXPECT_EQ(255, result[1].maxLevel);

	EXPECT_EQ(unsigned(3), result[2].uid);
	EXPECT_EQ("Newbie Channel", result[2].name);
	EXPECT_EQ(255, result[2].maxPlayers);
	EXPECT_EQ(gunz::Channel::CR_NEWBIE, result[2].rule);
	EXPECT_EQ(gunz::Channel::CT_GENERAL, result[2].type);
	EXPECT_EQ(1, result[2].minLevel);
	EXPECT_EQ(10, result[2].maxLevel);

	EXPECT_EQ(unsigned(4), result[3].uid);
	EXPECT_EQ("Rookie Channel", result[3].name);
	EXPECT_EQ(255, result[3].maxPlayers);
	EXPECT_EQ(gunz::Channel::CR_ROOKIE, result[3].rule);
	EXPECT_EQ(gunz::Channel::CT_GENERAL, result[3].type);
	EXPECT_EQ(11, result[3].minLevel);
	EXPECT_EQ(20, result[3].maxLevel);

	EXPECT_EQ(unsigned(5), result[4].uid);
	EXPECT_EQ("Veteran Channel", result[4].name);
	EXPECT_EQ(255, result[4].maxPlayers);
	EXPECT_EQ(gunz::Channel::CR_MASTERY, result[4].rule);
	EXPECT_EQ(gunz::Channel::CT_GENERAL, result[4].type);
	EXPECT_EQ(21, result[4].minLevel);
	EXPECT_EQ(255, result[4].maxLevel);

	EXPECT_EQ(unsigned(6), result[5].uid);
	EXPECT_EQ("Elite Channel", result[5].name);
	EXPECT_EQ(255, result[5].maxPlayers);
	EXPECT_EQ(gunz::Channel::CR_ELITE, result[5].rule);
	EXPECT_EQ(gunz::Channel::CT_GENERAL, result[5].type);
	EXPECT_EQ(35, result[5].minLevel);
	EXPECT_EQ(255, result[5].maxLevel);
}

TEST(channel_loader, invalid_channels)
{
	gunz::MUIDSanta s;
	vector<gunz::Channel::Traits> result = parse_channel_list(
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
		"<xml id=\"channel\">\n"
			"<channel maxplayers=\"255\" rule=\"novice\" />\n"	// Missing name
			"<channel name=\"Free Channel\" rule=\"novice\" />\n"	// Missing maxplayers
			"<channel name=\"Newbie Channel\" maxplayers=\"255\" rule=\"newby\" maxlevel='10' />\n"	// Misspelt rule
			"<channel name=\"Rookie Channel\" maxplayers=\"255\" rule=\"rookie\" minlevel='11' maxlevel='256' />\n"	// Maxlevel out of range
			"<channel name=\"Veteran Channel\" maxplayers=\"255\" rule=\"mastery\" minlevel='256' />\n"	// Minlevel out of range
			"<channel name=\"Elite Channel\" maxplayers=\"255\" rule=\"elite\" minlevel='35' maxlevel=34 />\n"	// Minlevel > maxlevel
		"</xml>\n",
		&s
	);

	EXPECT_EQ(unsigned(0), result.size());
}
