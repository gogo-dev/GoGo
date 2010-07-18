#include <gtest/gtest.h>

#include "../src/Configuration.h"
#include "../src/Configuration.cpp"

#include <boost/format.hpp>

#include <sstream>

using namespace std;
using namespace boost;

#define MAKE_CONFIG_IMPL(varName, contents, ssName) \
    istringstream ssName(contents);                 \
    Configuration varName(ssName)

#define MAKE_CONFIG(varName, contents) \
    MAKE_CONFIG_IMPL(varName, contents, ss__##__COUNTER__)

TEST(config, good_config_no_comments)
{
	const char* configFile =
		"a = b\n"
		"c=d\n"
		" e = f\n"
		"g = h \n"
	;

	MAKE_CONFIG(conf, configFile);

	EXPECT_EQ(string("b"), conf.get_value<string>("a"));
	EXPECT_EQ(string("d"), conf.get_value<string>("c"));
	EXPECT_EQ(string("f"), conf.get_value<string>("e"));
	EXPECT_EQ(string("h"), conf.get_value<string>("g"));
}

TEST(config, comments_get_stripped)
{
	const char* configFile =
		"# This is a comment\n"
		"\ta = b # Comment on this assignment."
	;

	MAKE_CONFIG(conf, configFile);

	EXPECT_EQ(string("b"), conf.get_value<string>("a"));
}

TEST(config, default_value_gets_used)
{
	const char* configFile = "key = value";

	MAKE_CONFIG(conf, configFile);

	EXPECT_EQ(string("default"), conf.get_value<string>("nonexistant", "default"));
	EXPECT_EQ(1, conf.get_value<int>("key", 1));
}

TEST(config, equals_sign_in_value)
{
	const char* configFile =
		"key = val=ue"
	;

	MAKE_CONFIG(conf, configFile);

	EXPECT_EQ(string("val=ue"), conf.get_value<string>("key"));
}

TEST(config, acceptance_test)
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

		EXPECT_EQ(string("clark"), conf.get_value<string>("db.username"));
		EXPECT_EQ(string("test"), conf.get_value<string>("db.password"));
		EXPECT_EQ(string("127.0.0.1"), conf.get_value<string>("db.ip"));
		EXPECT_EQ(9, conf.get_value<int>("penis.size"));

		EXPECT_THROW(conf.get_value<int>("db.username"), boost::bad_lexical_cast);
		EXPECT_THROW(conf.get_value<string>("nonexistant"), std::runtime_error);

	} catch(const SyntaxError& e) {
		FAIL() << (format("Syntax error:%2%: %1%") % e.what() % e.lineNumber).str();
	}
}
