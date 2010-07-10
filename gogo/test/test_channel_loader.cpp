#include <test.h>
#include "../src/ChannelLoader.h"
#include "../src/ChannelLoader.cpp"

using namespace std;
using namespace boost;

static void test_default_channel_xml()
{
	gunz::MUIDSanta s;
	vector<gunz::Channel::Traits> result = parse_channel_list(
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
		"<xml id=\"channel\">\n"
			"<channel name=\"Free Channel\" maxplayers=\"255\" rule=\"novice\" />\n"
			"<channel name=\"Newbie Channel\" maxplayers=\"255\" rule=\"newbie\" minlevel='1' maxlevel='10' />\n"
			"<channel name=\"Rookie Channel\" maxplayers=\"255\" rule=\"rookie\" minlevel='11' maxlevel='20' />\n"
			"<channel name=\"Veteran Channel\" maxplayers=\"255\" rule=\"mastery\" minlevel='21' />\n"
			"<channel name=\"Elite Channel\" maxplayers=\"255\" rule=\"elite\" minlevel='35' />\n"
		"</xml>\n",
		&s
	);

	if(result.size() != unsigned(5))
	{
		BOOST_FAIL("Bad channel list size.");
		return;
	}

	check_equal(result[0].name, "Free Channel");
}

int test_main(int, char**)
{
	test_default_channel_xml();

	return 0;
}
