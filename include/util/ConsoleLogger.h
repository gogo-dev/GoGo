#pragma once
#include "Logger.h"
#include <boost/thread/mutex.hpp>

class ConsoleLogger : public Logger
{
	private:
		boost::mutex consoleLock;

	private:
		static std::string right_now();
		void print_line(const char* toOutput);

	public:
		void print(const std::string& text);
};