#include <reflex/Scheduler.h>

#include <utility>

namespace reflex {

Scheduler::Scheduler(size_t concurrencyLevel)
	: processors(new TaskProcessor[concurrencyLevel]), processorCount(concurrencyLevel)
{
}

// Returns the processor with the lowest total usage, ensuring fair usage.
TaskProcessor* Scheduler::GetTaskTarget()
{
	typedef std::pair<uintmax_t, TaskProcessor*> ProcessorUsage;

	ProcessorUsage lowest(processors[0].UsageStatistics(), processors);

	for(size_t i = 1; i < processorCount; ++i)
	{
		uintmax_t stats = processors[i].UsageStatistics();

		if(stats < lowest.first)
			lowest = ProcessorUsage(stats, processors + i);
	}

	return lowest.second;
}

Scheduler::~Scheduler()
{
	delete[] processors;
}

}
