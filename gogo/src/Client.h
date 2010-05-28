#pragma once
#include <boost/asio.hpp>
#include <util/Logger.h>

#include "Structures.h"
#include "MUIDSanta.h"

class Client
{
public:
	boost::asio::ip::tcp::socket socket;

private:
	boost::uint8_t cryptkey[32];
	Logger* logger;
	MUID clientid;
	MUIDSanta* santa;

public:
	Client(Logger* logger, boost::asio::io_service& service, MUIDSanta* santa);
	void start();
	//Temp, used for testing!
	static Handshake& GetHandshake(std::string ip, boost::uint64_t clientid);

	~Client();

private:
	void send_handshake();
};
