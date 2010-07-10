#include <gunz/Channel.h>
#include <gunz/MUIDSanta.h>

#include <tinyxml/tinyxml.h>

#include <boost/lexical_cast.hpp>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;
using namespace boost;

namespace {
	struct ParseFailed {};
}

static char my_tolower(char c)
{
	return static_cast<char>(tolower(c));
}

static void on_error(const char* message)
{
	fprintf(stderr, "%s\n", message);
}

static gunz::Channel::Rule parse_rule(const char* text)
{
	std::string fixed(text);
	for_each(fixed.begin(), fixed.end(), my_tolower);

	if(fixed == "novice")
		return gunz::Channel::CR_NOVICE;
	else if(fixed == "newbie")
		return gunz::Channel::CR_NEWBIE;
	else if(fixed == "rookie")
		return gunz::Channel::CR_ROOKIE;
	else if(fixed == "mastery")
		return gunz::Channel::CR_MASTERY;
	else if(fixed == "elite")
		return gunz::Channel::CR_ELITE;
	else
	{
		on_error("Invalid channel rule. Skipping...");
		throw ParseFailed();
	}
}

static uint8_t parse_maxPlayers(const char* text)
{
	try {
		return lexical_cast<uint8_t>(text);
	} catch(bad_lexical_cast) {
		on_error("Attribute \"maxplayers\" must be in the range of 0-255. Skipping...");
		throw ParseFailed();
	}
}

static uint8_t parse_level(const char* text)
{
	try {
		return lexical_cast<uint8_t>(text);
	} catch(bad_lexical_cast) {
		on_error("Invalid level specified. Levels must be in the range of 0-255. Skipping...");
		throw ParseFailed();
	}
}

// Retrives the channel list from an xml file's contents. An example of the
// grammar can be found in channel.xml
vector<gunz::Channel::Traits> parse_channel_list(const string& rawXML, gunz::MUIDSanta* santa)
{
	TiXmlDocument doc;
	doc.Parse(rawXML.c_str());

	vector<gunz::Channel::Traits> ret;

	TiXmlElement* root = doc.RootElement();

	const TiXmlNode* channelNode = NULL;
	while((channelNode = root->IterateChildren(channelNode)))
	{
		const TiXmlElement* channel = channelNode->ToElement();
		const char* name = channel->Attribute("name");
		const char* maxPlayers = channel->Attribute("maxplayers");
		const char* rule = channel->Attribute("rule");
		// Type is always CT_GENERAL at this point.
		const char* minLevel = channel->Attribute("minlevel");
		const char* maxLevel = channel->Attribute("maxlevel");

		if(name == NULL)
		{
			on_error("Channel missing attribute \"name\" found. Skipping...");
			continue;
		}

		if(maxPlayers == NULL)
		{
			on_error("Channel missing attribute \"maxplayers\" found. Skipping...");
			continue;
		}

		if(rule == NULL)
			rule = "novice";

		if(minLevel == NULL)
			minLevel = "0";
		if(maxLevel == NULL)
			maxLevel = "256";	// HACK: This assumes the max level is 255. If
			                    // that EVER changes, this line must be updated.

		try {
			ret.push_back(gunz::Channel::Traits(
				santa->get(),
				name,
				parse_maxPlayers(maxPlayers),
				parse_rule(rule),
				gunz::Channel::CT_GENERAL,
				parse_level(minLevel),
				parse_level(maxLevel)
			));
		} catch(ParseFailed) {
			continue;
		}
	}

	return ret;
}
