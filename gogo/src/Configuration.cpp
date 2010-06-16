#include "Configuration.h"

#include <algorithm>

#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;

#ifndef countof
	#define countof(array) (sizeof(array)/sizeof((array)[0]))
#endif

#define COMMENT_TOKEN	"#"
#define SEPARATOR_TOKEN "="

// These characters are ignored in the parsing.
static const char whitespaceCharacters[] = {
	' ',
	'\t',
	'\n'
};

typedef tuple<size_t /* lineNumber */, string /* line */> Line;
typedef tuple<string /* key */, string /* value */> MapElem;

// Read up on MapReduce for info on what this is about.
template <typename ContainerType, typename Functor>
static void map_func(ContainerType& container, Functor func)
{
	for_each(container.begin(), container.end(), func);
}

static vector<Line> get_lines(istream& stream)
{
	vector<Line> ret;

	for(size_t i = 1; stream.good(); ++i)
	{
		string s;
		getline(stream, s, '\n');
		ret.push_back(make_tuple(i, s));
	}

	return ret;
}

static void strip_comments(Line& line)
{
	string& str = get<1>(line);
	str.assign(str.substr(0, str.find(COMMENT_TOKEN)));
}

static bool is_whitespace_char(char c)
{
	const char* begin = whitespaceCharacters;
	const char* end   = begin + countof(whitespaceCharacters);

	return find(begin, end, c) != end;
}

static void strip_whitespace(Line& line)
{
	string& src = get<1>(line);
	string result;

	result.reserve(src.length() + 1);

	for(const char* c = src.c_str(); *c != '\0'; ++c)
		if(!is_whitespace_char(*c))
			result += *c;

	src.assign(result);
}

static MapElem parse_pure(const Line& toParse)
{
	MapElem ret;

	string& key   = get<0>(ret);
	string& value = get<1>(ret);

	const size_t& lineNumber = get<0>(toParse);
	const string& str        = get<1>(toParse);

	size_t locOfSep = str.find(SEPARATOR_TOKEN);

	if(locOfSep == string::npos)
		throw SyntaxError("No separator found!", lineNumber);

	if(str.find(SEPARATOR_TOKEN, locOfSep + 1) != string::npos)
		throw SyntaxError("Too many " SEPARATOR_TOKEN " tokens.", lineNumber);

	key   = str.substr(0, locOfSep);
	value = str.substr(locOfSep + 1, string::npos);

	if(key == "")
		throw SyntaxError("No key found!", lineNumber);

	if(value == "")
		throw SyntaxError("No value found!", lineNumber);

	return ret;
}

static void parse(const Line& toParse, unordered_map<string, string>* target)
{
	// Ignore blank lines.
	if(get<1>(toParse).length() == 0)
		return;

	MapElem e = parse_pure(toParse);
	target->insert(make_pair(get<0>(e), get<1>(e)));
}

Configuration::Configuration(std::istream& stream)
{
	vector<Line> lines = get_lines(stream);

	map_func(lines, strip_comments);
	map_func(lines, strip_whitespace);
	map_func(lines, bind(parse, _1, &values));
}

SyntaxError::SyntaxError(const char* message, size_t _lineNumber)
	: runtime_error(message), lineNumber(_lineNumber)
{
}

Configuration::~Configuration()
{
}
