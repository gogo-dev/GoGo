#pragma once
#include <string>
#include <boost/format.hpp>

class Logger
{
	public:
		virtual void info(const std::string& text) = 0;
		virtual void warning(const std::string& text) = 0;
		virtual void error(const std::string& text) = 0;
};