#include "ConsoleLogger.h"

#include <cstdio>
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// I hate to do this... but we need it for color output :(
#ifdef WIN32
	#include <windows.h>
#endif

using namespace std;
using namespace boost;

string ConsoleLogger::right_now()
{
	using namespace posix_time;
	return to_simple_string(second_clock::local_time());
}

void ConsoleLogger::print_line(const char* toOutput, color c, FILE* target)
{
	mutex::scoped_lock lock(consoleLock);

#ifdef WIN32 // Micro$hit

	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if     (c == RED)    SetConsoleTextAttribute(console, 12);
	else if(c == YELLOW) SetConsoleTextAttribute(console, 14);
	else if(c == WHITE)  SetConsoleTextAttribute(console, 15);

	fprintf(target, "%s\n", toOutput);

	SetConsoleTextAttribute(console, 15);

#elif __GNUC__  // POSIX
	if     (c == RED)    fprintf(target, "\033[1;31m%s\033[0m\n", toOutput);
	else if(c == YELLOW) fprintf(target, "\033[1;33m%s\033[0m\n", toOutput);
	else if(c == WHITE)  fprintf(target, "\033[0;37m%s\033[0m\n", toOutput);
#else
	#warning "You may want to add your operating system to this list so that you get color output. Alternatively, you can remove this error with a comment."
	fprintf(target, "%s\n", toOutput);
#endif
}

string ConsoleLogger::format_message(const char* text)
{
	return (format("[%1%]: %2%") % right_now() % text).str();
}

void ConsoleLogger::info(const char* text)
{
	print_line(format_message(text).c_str(), WHITE, stdout);
}

void ConsoleLogger::warning(const char* text)
{
	print_line(format_message(text).c_str(), YELLOW, stdout);
}

void ConsoleLogger::error(const char* text)
{
	print_line(format_message(text).c_str(), RED, stderr);
}
