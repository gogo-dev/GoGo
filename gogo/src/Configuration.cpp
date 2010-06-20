#include "Configuration.h"

#include <util/SmallVector.h>
#include <vector>
#include <algorithm>
#include <memory>

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

typedef SmallVector<Line, 128> VecOfLines;

// Read up on MapReduce for info on what this is about.
template <typename ContainerType, typename Functor>
static void map_func(ContainerType& container, Functor func)
{
	for_each(container.begin(), container.end(), func);
}

template <typename Predicate>
static string filter(const string& cIn, Predicate pred)
{
	string cOut;
	cOut.reserve(cIn.length());

	string::const_iterator i   = cIn.begin();
	string::const_iterator end = cIn.end();

	for(; i != end; ++i)
		if(pred(*i)) cOut += *i;

	return cOut;
}

static string my_getline(istream& stream, char sep)
{
	string line;
	getline(stream, line, sep);
	return line;
}

static VecOfLines get_lines(istream& stream)
{
	VecOfLines lines;

	for(size_t i = 1; stream.good(); ++i)
		lines.push_back(make_tuple(i, my_getline(stream, '\n')));

	return lines;
}

static Line strip_comments(const Line& in)
{
	const string& str = get<1>(in);
	return make_tuple(get<0>(in), str.substr(0, str.find(COMMENT_TOKEN)));
}

static bool is_not_whitespace_char(char c)
{
	const char* begin = whitespaceCharacters;
	const char* end   = begin + countof(whitespaceCharacters);

	return find(begin, end, c) == end;
}

static Line strip_whitespace(const Line& in)
{
	return make_tuple(get<0>(in), filter(get<1>(in), is_not_whitespace_char));
}

static MapElem parse_pure(const Line& toParse)
{
	const size_t& lineNumber = get<0>(toParse);
	const string& str        = get<1>(toParse);

	const size_t locOfSep = str.find(SEPARATOR_TOKEN);

	if(locOfSep == string::npos)
		throw SyntaxError("No separator found!", lineNumber);

	const MapElem ret = make_tuple(str.substr(0, locOfSep), str.substr(locOfSep + 1, string::npos));

	if(get<0>(ret) == "")
		throw SyntaxError("No key found!", lineNumber);

	// We purposely allow blank values. Those are totally legit.

	return ret;
}

static bool is_blank(const Line& line)
{
	return get<1>(line).length() == 0;
}

static void parse(const Line& toParse, unordered_map<string, string>* target)
{
	if(is_blank(toParse))
		return;

	const MapElem e = parse_pure(toParse);
	target->insert(make_pair(get<0>(e), get<1>(e)));
}

#if BOOST_HAS_RVALUE_REFS
static unordered_map<string, string> init_config(VecOfLines&& lines)
#else
static unordered_map<string, string> init_config(VecOfLines lines)
#endif
{
	unordered_map<string, string> values;

	transform(lines.begin(), lines.end(), lines.begin(), strip_comments);
	transform(lines.begin(), lines.end(), lines.begin(), strip_whitespace);

	map_func(lines, bind(parse, _1, &values));

	return values;
}

Configuration::Configuration(std::istream& stream)
	: values(init_config(get_lines(stream)))
{
}

Configuration::Configuration(const Configuration& rhs)
	: values(rhs.values)
{
}

#if BOOST_HAS_RVALUE_REFS
Configuration::Configuration(std::istream&& stream)
	: values(init_config(get_lines(stream)))
{
}

Configuration::Configuration(const Configuration&& rhs)
	: values(std::move(rhs.values))
{
	// If you know where std::move is, please add the #include and remove
	// my guess of <memory>
}
#endif

SyntaxError::SyntaxError(const char* message, size_t _lineNumber)
	: runtime_error(message), lineNumber(_lineNumber)
{
}

Configuration::~Configuration()
{
}
