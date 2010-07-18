#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

using namespace boost;

TEST(boost, can_use_header_only_lib)
{
	shared_ptr<int> s = shared_ptr<int>(new int);
}

TEST(boost, can_use_compiled_lib)
{
	thread t;
}
