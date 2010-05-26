#pragma once
#include "Logger.h"
#include <boost/thread/mutex.hpp>

class ConsoleLogger : public Logger
{
	private:
		boost::mutex consoleLock;

		enum color
		{
			RED,
			YELLOW,
			WHITE
		};

	private:
		static std::string right_now();
		void print_line(const char* toOutput, color c);
		static std::string format_message(const std::string& text);

	public:
		void info(const std::string& text);
		void warning(const std::string& text);
		void error(const std::string& text);
};