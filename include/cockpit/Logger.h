#pragma once
#include <string>
#include <boost/format.hpp>

namespace cockpit {

/**
	The logger must be implemented by the application in order to be used with
	the rest of cockpit. If all else fails, you can always just make a
	"null logger" that drops all messages, although this is highly discouraged.
*/
class Logger
{
public:

	/**
		The debug target is used to log information that will only be helpful
		during development. During normal usage, these messages are just noise,
		and are optimized out by the compiler.
	*/
#ifdef DEBUG
	inline void debug(const char* message) { info(message); }
#else
	inline void debug(const char* message)
	{
		info(message);
	}
#endif

	/**
		The info target is used to log information that provides status updates
		to the user, but does not mean anything is going wrong. It's just for
		the curious.

		These are perfectly normal.
	*/
	virtual void info(const char* message) = 0;

	/**
		The warning target is used to log messages informing the user that
		something bad is happening, but there are steps that can be taken to
		prevent it from happening again. Except for any caveates mentioned in
		the message, the application will recover gracefully and continue
		functioning.

		These are bad; but can be rectified easily by the sysadmin.
	*/
	virtual void warning(const char* message) = 0;

	/**
		Whenever something goes wrong that is unrecoverable, and MatchServer
		will be terminated, this target will be called. The message will
		always contain exactly what actions were taken by the cockpit to save
		as much as it can before it kills something. These errors cannot be
		fixed without significant effort on the development team's part.

		These are very bad - you will want to file a bug report.
	*/
	virtual void error(const char* message) = 0;

	// The following two blocks are just convenience functions for the rest
	// of cockpit.

	inline void debug  (const std::string& message) { debug  (message.c_str()); }
	inline void info   (const std::string& message) { info   (message.c_str()); }
	inline void warning(const std::string& message) { warning(message.c_str()); }
	inline void error  (const std::string& message) { error  (message.c_str()); }

	inline void debug  (const boost::format& text) { debug  (text.str()); }
	inline void info   (const boost::format& text) { info   (text.str()); }
	inline void warning(const boost::format& text) { warning(text.str()); }
	inline void error  (const boost::format& text) { error  (text.str()); }

	virtual ~Logger()
	{
	}
};

}
