#include <test.h>

#include "../src/Configuration.h"
#include "../src/Configuration.cpp"

#include <sstream>

using namespace std;
using namespace boost;

#define MAKE_CONFIG_IMPL(varName, contents, ssName) \
    istringstream ssName(contents);                 \
    Configuration varName(ssName)

#define MAKE_CONFIG(varName, contents) \
    MAKE_CONFIG_IMPL(varName, contents, ss##__COUNTER__)

static void test_perfectly_good_config_file_no_comments()
{
	const char* configFile =
		"a = b\n"
		"c=d\n"
		" e = f\n"
		"g = h \n"
	;

	MAKE_CONFIG(conf, configFile);

	check_equal(string("b"), conf.get_value<string>("a"));
	check_equal(string("d"), conf.get_value<string>("c"));
	check_equal(string("f"), conf.get_value<string>("e"));
	check_equal(string("h"), conf.get_value<string>("g"));
}

static void test_comments_cause_no_problems()
{
	const char* configFile =
		"# This is a comment\n"
		"\ta = b # Comment on this assignment."
	;

	MAKE_CONFIG(conf, configFile);

	check_equal(string("b"), conf.get_value<string>("a"));
}

int test_main(int, char**)
{
	test_perfectly_good_config_file_no_comments();
	test_comments_cause_no_problems();

	return 0;
}
