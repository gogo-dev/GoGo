#pragma once
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>

namespace boost { namespace asio { class io_service; } }

namespace cockpit {

class Logger;
class ClientHandlerFactory;

class MatchServer : boost::noncopyable
{
public:
	struct Data;

private:
	Data *const d;	// http://techbase.kde.org/Policies/Library_Code_Policy#D-Pointers

public:
	MatchServer(Logger* logger,
	            ClientHandlerFactory* factory,
	            boost::asio::io_service* io,
	            boost::uint16_t port);

	void run();

	~MatchServer();
};

}