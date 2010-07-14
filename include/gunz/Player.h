#pragma once
#include <gunz/simple_types.h>

#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <string>

namespace gunz {

/**
	A player represents a single entity in the gunz library. Pointers to
	players are basically the only communication with the outside world that
	the gunz library has.
*/
class Player
{
public:
	struct Traits
	{
		MUID muid;
		boost::uint32_t clanid;
		MatchPlace place;
		std::string characterName;
		std::string clanName;
		boost::uint8_t level;
		boost::uint8_t ugradeid;

		Traits(MUID muid, const std::string& characterName, const std::string& clanName, boost::uint8_t level, MatchPlace place, boost::uint8_t ugradeid, boost::uint32_t clanid);
		~Traits();
	};

private:
	Traits traits;
	mutable boost::shared_mutex protection;

public:
	Player(const Traits& traits);

	enum MessageType
	{
		MT_ANNOUNCE,
		MT_WHISPER,
		MT_CHANNEL,
		MT_STAGE
	};

	/**
		This callback is called when the player has recieved a message from any
		other player. This function must be reentrant, as other players could
		be chatting in potentially infinite threads.
	*/
	virtual void OnMessage(MessageType type, const char* sender, const char* message) = 0;

	// Reentrant accessor.
	Traits GetTraits() const;

protected:
	// Reentrant modifier.
	void ModifyTraits(const boost::function<void (Traits& traits)>& modifier);

	// Prevents a memory leak. DO NOT MAKE THIS PUBLIC.
	~Player()
	{
	}
};

}
