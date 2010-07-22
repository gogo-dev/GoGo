#include <gtest/gtest.h>

#include <util/WorkQueue.h>

#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>

using namespace boost;

// The number of elements to be put in the queue for each test.
#define STRESS_LEVEL	1000

TEST(work_queue, construction)
{
	WorkQueue<int> q;
}

TEST(work_queue, no_edge_conditions)
{
	WorkQueue<int> q(2);

	q.push(3);
	q.push(2);
	q.push(1);

	EXPECT_EQ(3, q.pop());
	EXPECT_EQ(2, q.pop());
	EXPECT_EQ(1, q.pop());
}

// Elements are continuously added and removed, wrapping aruond the structure
// like a snake!
TEST(work_queue, snake)
{
	WorkQueue<int> q(2);

	for(int i = 0; i < STRESS_LEVEL; ++i)
	{
		q.push(i);
		q.push(i);
		EXPECT_EQ(i, q.pop());
		EXPECT_EQ(i, q.pop());
	}
}

TEST(work_queue, still_works_after_resize)
{
	WorkQueue<int> q(2);

	// Do it three times to test growing AND shrinking.
	for(int z = 0; z < 3; ++z)
	{
		for(int i = 0; i < STRESS_LEVEL; ++i)
			q.push(i);

		for(int i = 0; i < STRESS_LEVEL; ++i)
			EXPECT_EQ(i, q.pop());
	}
}

// TODO: Make WorkQueue work with auto_ptr by pushing all common implementation
// details up into a base class. This will also speed up compile times greatly.
/*
TEST(work_queue, can_use_auto_ptr)
{
	WorkQueue<std::auto_ptr<int> > q;

	q.push(new int(3));
	EXPECT_EQ(3, *q.pop());
}
*/

static void producer(WorkQueue<int>& q, int numToPush = STRESS_LEVEL)
{
	for(int i = 0; i < numToPush; ++i)
		q.push(i);
}

static void consumer(WorkQueue<int>& q, int numToPop)
{
	for(int i = 0; i < numToPop; ++i)
		q.pop();
}

TEST(work_queue, single_producer_single_consumer)
{
	WorkQueue<int> q;

	thread p1(bind(producer, ref(q), STRESS_LEVEL));
	thread c(bind(consumer, ref(q), STRESS_LEVEL));

	p1.join();
	c.join();
}

TEST(work_queue, multiple_producer_single_consumer)
{
	WorkQueue<int> q;

	thread p1(bind(producer, ref(q), STRESS_LEVEL));
	thread p2(bind(producer, ref(q), STRESS_LEVEL));
	thread p3(bind(producer, ref(q), STRESS_LEVEL));

	thread c(bind(consumer, ref(q), STRESS_LEVEL*3));

	p1.join();
	p2.join();
	p3.join();

	c.join();
}
