#pragma once

#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/Logger.h>
#include "MUIDSanta.h"

class GoGoFactory : public cockpit::ClientHandlerFactory
{
private:
	cockpit::Logger* logger;
	MUIDSanta santa;

public:
	GoGoFactory(cockpit::Logger* logger);

	cockpit::ClientHandler* create_client_handler();
};
