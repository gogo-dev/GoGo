#include "ChannelLoader.h"

char my_tolower(char c)
{
	return static_cast<char>(tolower(c));
}

ChannelRuleRelMap get_channel_rules()
{
	ChannelRuleRelMap relationships;
	
	relationships["novice"] = gunz::CR_NOVICE;
	relationships["newbie"] = gunz::CR_NEWBIE;
	relationships["rookie"] = gunz::CR_ROOKIE;
	relationships["mastery"] = gunz::CR_MASTERY;
	relationships["elite"] = gunz::CR_ELITE;
	
	return relationships;
}

ChannelTypeRelMap get_channel_types()
{
	ChannelTypeRelMap relationships;

	relationships["general"] = gunz::CT_GENERAL;
	relationships["private"] = gunz::CT_PRIVATE;
	relationships["user"] = gunz::CT_USER;
	relationships["clan"] = gunz::CT_CLAN;
	
	return relationships;
}
