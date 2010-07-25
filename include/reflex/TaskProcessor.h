#pragma once

#include <reflex/detail/Buffer.h>

#include <cstddef>
#include <cstring>

#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace reflex {

typedef boost::function<void ()> Task;

class TaskProcessor
{
private:
	detail::Buffer<Task> taskQueue;
	boost::thread taskHandler;

	// When die is true, the taskHandler will shut down.
	bool die;

public:
	TaskProcessor();

	/**
		Sets up a task to be run "one day". The function will be called after
		all previously-scheduled tasks have been run.
	*/
	void ScheduleTask(const Task& t);

	/**
		Gets a count of how many tasks have been processed since creation. This
		is used in the scheduling algorithm to detect the processor with the
		lowest load.
	*/
	size_t UsageStatistics() const;

	~TaskProcessor();
};

}
