#pragma once
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>

namespace boost { namespace asio { class io_service; } }

namespace cockpit {

class Logger;
class ClientHandlerFactory;

class MatchServer : private boost::noncopyable
{
public:
	struct Data;

private:
	Data *const d;	// http://techbase.kde.org/Policies/Library_Code_Policy#D-Pointers

public:
	/**
		Creates the MatchServer from a valid logger, client handler factory,
		pre-initialized io service, and a port to listen on. When this function
		completes, the matchserver will not do anything except collect
		connect()ions that need to be accepted. To start everything going,
		call run().
	*/
	MatchServer(Logger* logger,
	            ClientHandlerFactory* factory,
	            boost::asio::io_service* io,
	            boost::uint16_t port);

	/**
		This function asynchronously starts up the MatchServer pipeline;
		accepting new connections and not afraiding of anything.
	*/
	void run();

	~MatchServer();
};

}