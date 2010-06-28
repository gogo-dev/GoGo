#pragma once
#include <string>

namespace gunz {

class Player
{
public:
	virtual void HandleChannelMessage(const std::string& speaker, const std::string& message) = 0;
	virtual void HandleGameMessage(const std::string& speaker, const std::string& message) = 0;
};

}
