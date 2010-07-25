#pragma once

#include <reflex/TaskProcessor.h>

namespace reflex {

class Scheduler
{
private:
	TaskProcessor* processors;
	size_t processorCount;

public:
	/**
		@param  concurrencyLevel The number of internal threads to run.
	*/
	Scheduler(size_t concurrencyLevel);

	/**
		Gets an instance of a TaskProcessor that you can use for scheduling
		your tasks. The scheduler will automatically pick the one with the
		lowest load.
	*/
	TaskProcessor* GetTaskTarget();

	~Scheduler();
};

}
