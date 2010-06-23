#pragma once

#include <boost/signals2.hpp>
#include <boost/cstdint.hpp>

#include <cockpit/ClientHandler.h>
#include <cockpit/Logger.h>
#include <cockpit/packet/Parameters.h>
#include <database/GunzDB.h>
#include <database/AccountInfo.h>
#include <database/CharacterInfo.h>
#include <string>

#include "Structures.h"

class MUIDSanta;
using namespace boost;
class GoGoClient : public cockpit::ClientHandler
{
private:
	cockpit::Logger* logger;
	cockpit::Transmitter* transmitter;
	cockpit::packet::Registry* registry;
	GunzDB* database;

	MUIDSanta* santa;
	MUID myMUID;
	AccountInfo myAccount;
	CharacterInfo myCharacter;

public:
	GoGoClient(cockpit::Logger* logger, MUIDSanta* santa, GunzDB* database);
	~GoGoClient();

	void initialize(cockpit::Transmitter* transmitter, cockpit::packet::Registry* registry);

	void OnFailedParse(boost::uint16_t commandID, const boost::uint8_t* parameters, boost::uint16_t length);
	void OnInvalidPacketType(boost::uint16_t commandID);

	void OnMatchLogin(const std::string& username, const std::string& password, boost::int32_t commandVersion, boost::uint32_t nChecksumPack);
	void OnCharList();
	void OnCharCreate(MUID uidPlayer, uint32_t charMarker, std::string charName, uint32_t charSex, uint32_t charHair, uint32_t charFace, uint32_t charCostume);
	void OnCharInfo(uint8_t marker);

	boost::array<boost::uint8_t, 32>
	handshake(boost::asio::ip::tcp::socket& s) const;
};

