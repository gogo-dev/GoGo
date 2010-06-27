#pragma once

#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/Logger.h>
#include <database/GunzDB.h>
#include <gunz/MUIDSanta.h>

class GoGoFactory : public cockpit::ClientHandlerFactory
{
private:
	cockpit::Logger* logger;
	MUIDSanta santa;
	GunzDB* database;

public:
	GoGoFactory(cockpit::Logger* logger, GunzDB* database);

	std::auto_ptr<cockpit::ClientHandler> create_client_handler();
};
