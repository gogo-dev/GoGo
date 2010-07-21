#include <gtest/gtest.h>

#include <util/WorkQueue.h>

#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>

using namespace boost;

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

	for(int i = 0; i < 1000; ++i)
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
		for(int i = 0; i < 1000; ++i)
			q.push(i);

		for(int i = 0; i < 1000; ++i)
			EXPECT_EQ(i, q.pop());
	}
}

#define ELEMENTS_IN_QUEUE	8

static void producer(WorkQueue<int>& q)
{
	for(int i = 0; i < ELEMENTS_IN_QUEUE; ++i)
		q.push(i);
}

static void consumer(WorkQueue<int>& q)
{
	for(int i = 0; i < ELEMENTS_IN_QUEUE; ++i)
		EXPECT_EQ(i, q.pop());
}

TEST(work_queue, concurrent_accesses)
{
	WorkQueue<int> q;

	thread p(bind(producer, ref(q)));
	thread c(bind(consumer, ref(q)));

	p.join();
	c.join();
}
