#pragma once
#include <string>

class Logger
{
	public:
		virtual void print(const std::string& text) = 0;
};