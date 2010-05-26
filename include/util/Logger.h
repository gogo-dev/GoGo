#pragma once
#include <string>
#include <boost/format.hpp>

class Logger
{
	public:
		virtual void info(const std::string& text) = 0;
		virtual void warning(const std::string& text) = 0;
		virtual void error(const std::string& text) = 0;

		inline void info   (const boost::format& text) { return info   (text.str()); }
		inline void warning(const boost::format& text) { return warning(text.str()); }
		inline void error  (const boost::format& text) { return error  (text.str()); }
};