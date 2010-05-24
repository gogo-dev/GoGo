#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "test.h"

using namespace boost;

int test_main(int, char**)
{
	shared_ptr<int> s = shared_ptr<int>(new int);
	thread t;

	return 0;
}
