#pragma once
#include <cockpit/ClientHandler.h>

#include <database/AccountInfo.h>
#include <database/CharacterInfo.h>

#include <string>

#include <boost/cstdint.hpp>
#include <boost/thread/mutex.hpp>

namespace cockpit {
	class Logger;
}

namespace gunz { class MUIDSanta; }
class GunzDB;

typedef boost::uint64_t MUID;

using namespace boost;
class GoGoClient : public cockpit::ClientHandler
{
private:
	cockpit::Logger* logger;
	cockpit::Transmitter* transmitter;
	cockpit::packet::Registry* registry;
	GunzDB* database;

	gunz::MUIDSanta* santa;
	MUID myMUID;
	AccountInfo myAccount;
	CharacterInfo myCharacter;

public:
	GoGoClient(cockpit::Logger* logger, gunz::MUIDSanta* santa, GunzDB* database);
	~GoGoClient();

	void initialize(cockpit::Transmitter* transmitter, cockpit::packet::Registry* registry);

	void OnFailedParse(boost::uint16_t commandID, const boost::uint8_t* parameters, boost::uint16_t length);
	void OnInvalidPacketType(boost::uint16_t commandID);
	void OnUnimplementedPacket(boost::uint16_t commandID);

	void OnMatchLogin(const std::string& username, const std::string& password, boost::int32_t commandVersion, boost::uint32_t nChecksumPack);
	void OnCharList();
	void OnCharCreate(MUID uidPlayer, uint32_t charMarker, const std::string& charName, uint32_t charSex, uint32_t charHair, uint32_t charFace, uint32_t charCostume);
	void OnCharDelete(MUID uid, uint32_t marker, const std::string& name);
	void OnCharInfo(uint8_t marker);
	void OnCharSelect(MUID uid, uint8_t marker);

	boost::array<boost::uint8_t, 32>
	handshake(boost::asio::ip::tcp::socket& s) const;
};
