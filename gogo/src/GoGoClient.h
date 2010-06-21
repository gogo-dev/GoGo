#pragma once

#include <boost/signals2.hpp>
#include <boost/cstdint.hpp>

#include <cockpit/ClientHandler.h>
#include <cockpit/Logger.h>
#include <string>

#include "Structures.h"

class MUIDSanta;

class GoGoClient : public cockpit::ClientHandler
{
private:
	cockpit::Logger* logger;
	cockpit::Transmitter* transmitter;
	cockpit::packet::Registry* registry;

	MUIDSanta* santa;
	MUID myMUID;

public:
	GoGoClient(cockpit::Logger* logger, MUIDSanta* santa);

	void initialize(cockpit::Transmitter* transmitter, cockpit::packet::Registry* registry);

	void OnMatchLogin(const std::string& username, const std::string& password, boost::int32_t commandVersion, boost::uint32_t nChecksumPack);

	boost::array<boost::uint8_t, 32>
	handshake(boost::asio::ip::tcp::socket& s) const;

	~GoGoClient();
};

