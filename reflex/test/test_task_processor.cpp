#include <gtest/gtest.h>

#include <reflex/TaskProcessor.h>

#include <boost/bind/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

using namespace std;
using namespace boost;

using namespace reflex;

static void increment_counter(uint64_t& num)
{
	++num;
}

TEST(task_processor, single_task)
{
	uint64_t counter = 0;

	{
		TaskProcessor t;
		t.ScheduleTask(bind(increment_counter, ref(counter)));

		EXPECT_EQ(unsigned(1), t.UsageStatistics());
	}

	EXPECT_EQ(unsigned(1), counter);
}

// delays by a random amount between 0 and 1000 microseconds.
static void delay_random_amount(mt19937& algo)
{
	uniform_int<> dist(0, 100);

	this_thread::sleep(posix_time::microsec(variate_generator<mt19937&, uniform_int<> >(algo, dist)() * 10));
}

static void schedule_increment_50(TaskProcessor& t, uint64_t& counter)
{
	mt19937 algo;

	for(int i = 0; i < 50; ++i)
	{
		t.ScheduleTask(bind(increment_counter, ref(counter)));
		delay_random_amount(algo);
	}
}

TEST(task_processor, multiple_threads)
{
	uint64_t counter = 0;

	{
		TaskProcessor t;

		thread threads[3] = {
			thread(bind(schedule_increment_50, ref(t), ref(counter))),
			thread(bind(schedule_increment_50, ref(t), ref(counter))),
			thread(bind(schedule_increment_50, ref(t), ref(counter)))
		};

		for(int i = 0; i < 3; ++i)
			threads[i].join();
	}

	EXPECT_EQ(unsigned(150), counter);
}
