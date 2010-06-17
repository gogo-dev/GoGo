#pragma once
#include <cstddef>

#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>

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
		and a port to listen on. When this function completes, the matchserver
		will not do anything except collect connect()ions that need to be
		accepted. To start everything going, call run(). By default, c*2 threads
		are created where "c" is the number of cores on your computer. You can
		set this yourself with the other constructor.
	*/
	MatchServer(Logger* logger,
	            ClientHandlerFactory* factory,
	            boost::uint16_t port);

	/**
		This constructor is the exact same as the other one, except instead of
		using a predefined thread count, lets the consumer select their very own.

		@see The other constructor.
	*/
	MatchServer(Logger* logger,
	            ClientHandlerFactory* factory,
	            boost::uint16_t port,
	            std::size_t numThreads);

	/**
		This function asynchronously starts up the MatchServer pipeline;
		accepting new connections and not afraiding of anything. It will return
		immediately, giving control back to the programmer. Have faith that the
		matchserver is running in one or more external threads while you go
		about your business.
	*/
	void start();

	/**
		If the matchserver is currently running, calling this method will
		signal the shutdown of all the threads. Afterwards, run() can be called
		to restart the server. Alternatively, you can just use the restart()
		function.
	*/
	void stop();

	/**
		Restarts MatchServer. Drops all connections and restarts the acceptance
		loop.
	*/
	inline void restart()
	{
		stop();
		start();
	}

	/**
		Waits for MatchServer to be done (never? possibly.) before returning.
	*/
	void wait();

	/**
		Terminates all connections, and cleans up nicely. All pointers passed
		in the constructor are the parents responsibility to deallocate, as
		MatchServer will NOT do it for you.
	*/
	~MatchServer();
};

}
