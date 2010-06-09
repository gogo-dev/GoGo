#pragma once

#include <cockpit/ClientHandlerFactory.h>
#include <cockpit/Logger.h>

class GoGoFactory : public cockpit::ClientHandlerFactory
{
private:
	cockpit::Logger* logger;

public:
	GoGoFactory(cockpit::Logger* logger);

	cockpit::ClientHandler* create_client_handler();
};
