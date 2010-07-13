#pragma once
#include <cockpit/ClientHandler.h>

#include <database/AccountInfo.h>
#include <database/CharacterInfo.h>

#include <gunz/Player.h>
#include <gunz/simple_types.h>

#include <string>

#include <boost/cstdint.hpp>
#include <boost/thread/mutex.hpp>

namespace cockpit {
	class Logger;
}

namespace gunz {
	class MUIDSanta;
	class ChannelList;
	class Channel;
	class Stage;
}

class GunzDB;

class GoGoClient : public cockpit::ClientHandler, public gunz::Player
{
private:
	cockpit::Logger* logger;
	cockpit::Transmitter* transmitter;
	cockpit::packet::Registry* registry;
	GunzDB* database;

	gunz::ChannelList* channelList;
	gunz::MUIDSanta* santa;

	gunz::MUID myMUID;
	AccountInfo myAccount;
	CharacterInfo myCharacter;
	gunz::Channel* myChannel;
	gunz::Stage* myStage;
	gunz::MatchPlace myPlace;

public:
	GoGoClient(cockpit::Logger* logger, gunz::ChannelList* channelList, gunz::MUIDSanta* santa, GunzDB* database);
	~GoGoClient();

	void initialize(cockpit::Transmitter* transmitter, cockpit::packet::Registry* registry);
	void OnMessage(MessageType type, const char* sender, const char* message);

	void OnFailedParse(boost::uint16_t commandID, const boost::uint8_t* parameters, boost::uint16_t length);
	void OnInvalidPacketType(boost::uint16_t commandID);
	void OnUnimplementedPacket(boost::uint16_t commandID);

	void OnMatchLogin(const std::string& username, const std::string& password, boost::int32_t commandVersion, boost::uint32_t nChecksumPack);
	void OnCharList();
	void OnCharCreate(gunz::MUID uidPlayer, boost::uint32_t charMarker, const std::string& charName, boost::uint32_t charSex, boost::uint32_t charHair, boost::uint32_t charFace, boost::uint32_t charCostume);
	void OnCharDelete(gunz::MUID uid, boost::uint32_t marker, const std::string& name);
	void OnCharInfo(boost::uint8_t marker);
	void OnCharSelect(gunz::MUID uid, boost::uint8_t marker);
	void OnRecommendedChannel();
	void OnChannelPlayerList (const gunz::MUID& playerId, const gunz::MUID& channelId, const boost::uint32_t&  page);

	boost::array<boost::uint8_t, 32>
	handshake(boost::asio::ip::tcp::socket& s) const;
};
