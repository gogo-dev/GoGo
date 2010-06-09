#pragma once
#include <cockpit/Logger.h>
#include <boost/thread/mutex.hpp>

class ConsoleLogger : public cockpit::Logger
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
		static std::string format_message(const char* text);

	public:
		void info(const char* text);
		void warning(const char* text);
		void error(const char* text);

		virtual ~ConsoleLogger()
		{
		}
};
