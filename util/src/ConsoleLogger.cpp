#include <util/ConsoleLogger.h>

#include <cstdio>
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// I hate to do this... but we need it for color output :(
#if WIN32
	#include <windows.h>
#endif

using namespace std;
using namespace boost;

string ConsoleLogger::right_now()
{
	using namespace posix_time;
	return to_simple_string(second_clock::local_time());
}

void ConsoleLogger::print_line(const char* toOutput, color c)
{
	mutex::scoped_lock(consoleLock);

#if WIN32	// Micro$hit

	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (c == RED)        SetConsoleTextAttribute(console, 12);
	else if(c == YELLOW) SetConsoleTextAttribute(console, 14);
	else if(c == WHITE)  SetConsoleTextAttribute(console, 15);

	printf("%s\n", toOutput);

	SetConsoleTextAttribute(console, 15);

#else		// POSIX
	if     (c == RED)    printf("\033[1;31m%s\033[0m\n", toOutput);
	else if(c == YELLOW) printf("\033[1;33m%s\033[0m\n", toOutput);
	else if(c == WHITE)  printf("\033[0;37m%s\033[0m\n", toOutput);
#endif
}

string ConsoleLogger::format_message(const string& text)
{
	return (format("[%1%]: %2%") % right_now() % text).str();
}

void ConsoleLogger::info(const string& text)
{
	print_line(format_message(text).c_str(), WHITE);
}

void ConsoleLogger::warning(const string& text)
{
	print_line(format_message(text).c_str(), YELLOW);
}

void ConsoleLogger::error(const string& text)
{
	print_line(format_message(text).c_str(), RED);
}
