#include "Configuration.h"

#include <gunz/simple_types.h>

#include <algorithm>
#include <map>
#include <string>

typedef std::map<std::string, gunz::ChannelRule> ChannelRuleRelMap;
typedef std::map<std::string, gunz::ChannelType> ChannelTypeRelMap;

ChannelRuleRelMap get_channel_rules();
ChannelTypeRelMap get_channel_types();
char my_tolower(char c);

template <typename ChannelMapType>
static typename ChannelMapType::mapped_type get_channel_attrib(const std::string& stringRep, const ChannelMapType& attribMap)
{
	std::for_each(stringRep.begin(), stringRep.end(), my_tolower);

	typename ChannelMapType::const_iterator loc = attribMap.find(stringRep);

	if(loc == attribMap.end())
		throw SyntaxError("Invalid Channel Rule found! Sorry, no line info.", 0);

	return loc->second;	
}
