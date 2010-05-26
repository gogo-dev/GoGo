#include <util/ConsoleLogger.h>

#include <cstdio>
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost;

string ConsoleLogger::right_now()
{
	using namespace posix_time;
	return to_simple_string(second_clock::local_time());
}

void ConsoleLogger::print_line(const char* toOutput)
{
	mutex::scoped_lock(consoleLock);
	printf("%s\n", toOutput);
}

void ConsoleLogger::print(const string& text)
{
	print_line((format("[%1%]: %2%") % right_now() % text).str().c_str());
}