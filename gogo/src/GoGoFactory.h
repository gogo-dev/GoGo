#pragma once

#include <cockpit/ClientHandlerFactory.h>

#include <gunz/ChannelList.h>
#include <gunz/MUIDSanta.h>

#include <boost/function.hpp>

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
	/**
		The logger and database pointers are saved locally and passed out to
		individual clients, but the last parameter is a tad tricker.

		When the channel list is initialized, it has no channels! To set up
		the initial general channels, pass in a functor to do your dirty work!
	*/
	GoGoFactory(cockpit::Logger* logger, GunzDB* database, const boost::function<void (gunz::ChannelList*)>& initChannelList);

	std::auto_ptr<cockpit::ClientHandler> create_client_handler();
};
