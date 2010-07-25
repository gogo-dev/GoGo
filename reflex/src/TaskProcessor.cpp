#include <reflex/detail/TaskProcessor.h>

#include <boost/bind/bind.hpp>

using namespace boost;

typedef unique_lock<mutex> Locker;

namespace reflex {
namespace detail {

static void process_queue(Buffer<Task>& buf, bool& die)
{
	while(!die)
		buf.pop()();
}

static void kill_thread(bool& dieFlag)
{
	dieFlag = true;
}

TaskProcessor::TaskProcessor()
{
	numberOfProcessedTasks = 0;
	die = false;

	taskHandler = thread(bind(process_queue, ref(taskQueue), ref(die)));
}

void TaskProcessor::ScheduleTask(const Task& t)
{
	{
		Locker w(protection);
		++numberOfProcessedTasks;
	}

	taskQueue.push(t);
}

size_t TaskProcessor::UsageStatistics() const
{
	Locker r(protection);
	return numberOfProcessedTasks;
}

// By pushing a task that sets the die flag, we kill the thread.
TaskProcessor::~TaskProcessor()
{
	taskQueue.push(bind(kill_thread, ref(die)));
	taskHandler.join();
}

}
}
