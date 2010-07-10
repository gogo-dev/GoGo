#include <test.h>
#include "../src/ChannelLoader.h"
#include "../src/ChannelLoader.cpp"

using namespace std;
using namespace boost;

// Handles everything but the edge cases. Lol.
static void test_default_channel_xml()
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

	if(result.size() != unsigned(6))
		return BOOST_FAIL("Bad channel list size.");

	check_equal(result[0].uid, unsigned(1));
	check_equal(result[0].name, "Free Channel 1");
	check_equal(result[0].maxPlayers, 255);
	check_equal(result[0].rule, gunz::Channel::CR_NOVICE);
	check_equal(result[0].type, gunz::Channel::CT_GENERAL);
	check_equal(result[0].minLevel, 1);
	check_equal(result[0].maxLevel, 255);

	check_equal(result[1].uid, unsigned(2));
	check_equal(result[1].name, "Free Channel 2");
	check_equal(result[1].maxPlayers, 255);
	check_equal(result[1].rule, gunz::Channel::CR_NOVICE);
	check_equal(result[1].type, gunz::Channel::CT_GENERAL);
	check_equal(result[1].minLevel, 1);
	check_equal(result[1].maxLevel, 255);

	check_equal(result[2].uid, unsigned(3));
	check_equal(result[2].name, "Newbie Channel");
	check_equal(result[2].maxPlayers, 255);
	check_equal(result[2].rule, gunz::Channel::CR_NEWBIE);
	check_equal(result[2].type, gunz::Channel::CT_GENERAL);
	check_equal(result[2].minLevel, 1);
	check_equal(result[2].maxLevel, 10);

	check_equal(result[3].uid, unsigned(4));
	check_equal(result[3].name, "Rookie Channel");
	check_equal(result[3].maxPlayers, 255);
	check_equal(result[3].rule, gunz::Channel::CR_ROOKIE);
	check_equal(result[3].type, gunz::Channel::CT_GENERAL);
	check_equal(result[3].minLevel, 11);
	check_equal(result[3].maxLevel, 20);

	check_equal(result[4].uid, unsigned(5));
	check_equal(result[4].name, "Veteran Channel");
	check_equal(result[4].maxPlayers, 255);
	check_equal(result[4].rule, gunz::Channel::CR_MASTERY);
	check_equal(result[4].type, gunz::Channel::CT_GENERAL);
	check_equal(result[4].minLevel, 21);
	check_equal(result[4].maxLevel, 255);

	check_equal(result[5].uid, unsigned(6));
	check_equal(result[5].name, "Elite Channel");
	check_equal(result[5].maxPlayers, 255);
	check_equal(result[5].rule, gunz::Channel::CR_ELITE);
	check_equal(result[5].type, gunz::Channel::CT_GENERAL);
	check_equal(result[5].minLevel, 35);
	check_equal(result[5].maxLevel, 255);
}

static void test_bad_lines_get_dropped()
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

	check_equal(result.size(), unsigned(0));
}

int test_main(int, char**)
{
	test_default_channel_xml();
	test_bad_lines_get_dropped();

	return 0;
}
