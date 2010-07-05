#pragma once

#include <cockpit/ClientHandlerFactory.h>

#include <gunz/ChannelList.h>
#include <gunz/MUIDSanta.h>

namespace cockpit { class Logger; }
class GunzDB;

class GoGoFactory : public cockpit::ClientHandlerFactory
{
private:
	cockpit::Logger* logger;

	gunz::MUIDSanta santa;
	gunz::ChannelList channelList;

	GunzDB* database;

public:
	GoGoFactory(cockpit::Logger* logger, GunzDB* database);

	std::auto_ptr<cockpit::ClientHandler> create_client_handler();
};
