#pragma once
#include <boost/array.hpp>
#include <boost/shared_array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/cstdint.hpp>
#include <cockpit/Logger.h>

#include "Structures.h"
#include "MUIDSanta.h"

class Client
{
public:
	boost::asio::ip::tcp::socket socket;

private:
	boost::shared_array<unsigned char> recvbuffer;
	boost::uint8_t cryptkey[32];
	cockpit::Logger* logger;
	MUID clientid;
	MUIDSanta* santa;

public:
	Client(cockpit::Logger* logger, boost::asio::io_service& service, MUIDSanta* santa);
	void start();

	boost::array<boost::uint8_t, 26>
	make_handshake();
	static boost::array<boost::uint8_t, 26> test_handshake(boost::uint64_t);

	~Client();

private:
	void send_handshake();
	void OnRecv();
};
