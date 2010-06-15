#pragma once

#include <boost/signals2.hpp>

#include <cockpit/ClientHandler.h>
#include <cockpit/Logger.h>

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

	std::vector<boost::signals2::connection> activeHandlers;

private:
	void register_handler(const boost::signals2::connection& connection);

public:
	GoGoClient(cockpit::Logger* logger, MUIDSanta* santa);

	void initialize(cockpit::Transmitter* transmitter, cockpit::packet::Registry* registry);

	boost::array<boost::uint8_t, 32>
	handshake(boost::asio::ip::tcp::socket& s) const;

	~GoGoClient();
};

