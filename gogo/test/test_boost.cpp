#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

using namespace boost;

int main()
{
	shared_ptr<int> s = shared_ptr<int>(new int);
	thread t;

	return 0;
}
