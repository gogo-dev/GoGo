#pragma once

#include <cockpit/ClientHandler.h>
#include <cockpit/Logger.h>

class GoGoClient : public cockpit::ClientHandler
{
private:
	cockpit::Logger* logger;
	cockpit::Transmitter* transmitter;
	cockpit::packet::Registry* registry;

public:
	GoGoClient(cockpit::Logger* logger);

	void initialize(cockpit::Transmitter* transmitter, cockpit::packet::Registry* registry);

	boost::array<boost::uint8_t, 26>
	handshake(const boost::asio::ip::tcp::socket& s) const;

	~GoGoClient();
};

