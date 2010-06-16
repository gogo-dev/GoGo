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
	'\t'
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

	for(size_t i = 0; stream.good(); ++i)
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
	str = str.substr(0, str.find(COMMENT_TOKEN));
}

static bool is_whitespace_char(char c)
{
	for(size_t i = 0; i < countof(whitespaceCharacters); ++i)
		if(c == whitespaceCharacters[i])
			return true;

	return false;
}

static void strip_whitespace(Line& line)
{
	string& src = get<1>(line);
	string result;

	result.reserve(src.length() + 1);

	for(const char* c = src.c_str(); *c != '\0'; ++c)
		if(!is_whitespace_char(*c))
			result += *c;

	src = result;
}

static void strip_empty_lines(vector<Line>& lines)
{
	vector<vector<Line>::iterator> toErase;

	for(vector<Line>::iterator i = lines.begin(); i != lines.end(); ++i)
		if(get<1>(*i).length() == 0)
			toErase.push_back(i);

	for(vector<vector<Line>::iterator>::iterator i = toErase.begin(); i != toErase.end(); ++i)
		lines.erase(*i);
}

/*
	So how are we parsing a preprocessed (no comments) line, anyhow?

	1) Scan to equals sign. If not present, syntax error.
	2) keyEnd = Scan left of seperator until no more spaces.
	4) key = substr(0, [beginning of spaces]);
	5) if len(key) == 0, syntax error.
	6) Scan right of seperator until no more spaces.
	7) value = substr([end of spaces], string::npos);
	8) if len(value) == 0, syntax error.
	9) Return (key, value).
*/
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
	MapElem e = parse_pure(toParse);
	target->insert(make_pair(get<0>(e), get<1>(e)));
}

Configuration::Configuration(std::istream& stream)
{
	vector<Line> lines = get_lines(stream);

	map_func(lines, strip_comments);
	map_func(lines, strip_whitespace);
	strip_empty_lines(lines);
	map_func(lines, bind(parse, _1, &values));
}

SyntaxError::SyntaxError(const char* message, size_t _lineNumber)
	: runtime_error(message), lineNumber(_lineNumber)
{
}

Configuration::~Configuration()
{
}
