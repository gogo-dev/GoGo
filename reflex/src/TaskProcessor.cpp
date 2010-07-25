#include <reflex/detail/TaskProcessor.h>

#include <boost/bind/bind.hpp>

using namespace boost;

typedef unique_lock<mutex> Locker;

namespace reflex {
namespace detail {

static void process_queue(Buffer<Task>& buf, bool& die)
{
	function<void ()> nextTask;

	for(;;)
	{
		nextTask = buf.pop();

		nextTask();

		if(die)
			return;
	}
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

// By pushing a blank task, we ensure the task handler checks the die flag
// instead of busy-waiting indefinately.
TaskProcessor::~TaskProcessor()
{
	taskQueue.push(bind(kill_thread, ref(die)));
	taskHandler.join();
}

}
}
