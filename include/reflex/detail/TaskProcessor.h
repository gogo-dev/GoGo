#pragma once

#include <reflex/detail/Buffer.h>

#include <cstddef>
#include <cstring>
#include <utility>

#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace reflex {
namespace detail {

typedef boost::function<void ()> Task;

class TaskProcessor
{
private:
	Buffer<Task> taskQueue;

	boost::uintmax_t numberOfProcessedTasks;
	mutable boost::mutex protection;

	boost::thread taskHandler;

	// When die is true, the taskHandler will shut down.
	bool die;

public:
	TaskProcessor();

	// Sets up a task to be run "one day".
	void ScheduleTask(const Task& t);

	// Gets a count of how many tasks have been processed since creation.
	size_t UsageStatistics() const;

	~TaskProcessor();
};

}
}
