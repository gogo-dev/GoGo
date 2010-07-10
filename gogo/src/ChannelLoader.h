#pragma once

#include <gunz/Channel.h>
#include <gunz/MUIDSanta.h>

#include <string>
#include <vector>

std::vector<gunz::Channel::Traits> parse_channel_list(const std::string& rawXML, gunz::MUIDSanta* santa);
