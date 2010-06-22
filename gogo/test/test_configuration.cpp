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
    MAKE_CONFIG_IMPL(varName, contents, ss__##__COUNTER__)

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

static void test_default_value_usage()
{
	const char* configFile = "key = value";

	MAKE_CONFIG(conf, configFile);

	check_equal(string("default"), conf.get_value<string>("nonexistant", "default"));
	check_equal(1, conf.get_value<int>("key", 1));
}

static void test_equals_sign_in_value()
{
	const char* configFile =
		"key = val=ue"
	;

	try {
		MAKE_CONFIG(conf, configFile);

		check_equal(string("val=ue"), conf.get_value<string>("key"));
	} catch(const SyntaxError&) {
		BOOST_FAIL("Seperator token detection is not behaving correctly.");
	}
}

static void acceptance_test()
{
	const char* configFile =
		"# Some comment header explaining what these variables are.\n"
		"\tdb.username = clark\n"
		"\tdb.password = test\n"
		"\tdb.ip = 127.0.0.1\n"
		"\n"
		"# Just random stuff...\n"
		"penis.size = 9 # In inches, of course.\n"
	;

	try {
		MAKE_CONFIG(conf, configFile);

		check_equal(string("clark"), conf.get_value<string>("db.username"));
		check_equal(string("test"), conf.get_value<string>("db.password"));
		check_equal(string("127.0.0.1"), conf.get_value<string>("db.ip"));
		check_equal(9, conf.get_value<int>("penis.size"));

		try {
			conf.get_value<int>("db.username");
			BOOST_FAIL("Exception should be thrown!");
		} catch(const boost::bad_lexical_cast&) {
		}

		try {
			conf.get_value<string>("nonexistant");
			BOOST_FAIL("Exception should be thrown.");
		} catch(const std::runtime_error&) {
		}

	} catch(const SyntaxError& e) {
		BOOST_FAIL((format("Syntax error:%2%: %1%") % e.what() % e.lineNumber).str().c_str());
	}
}

int test_main(int, char**)
{
	test_perfectly_good_config_file_no_comments();
	test_comments_cause_no_problems();
	test_default_value_usage();
	test_equals_sign_in_value();

	acceptance_test();

	return 0;
}
