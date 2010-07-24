#include <gtest/gtest.h>

#include <reflex/Buffer.h>

#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>

using namespace boost;

using namespace reflex;

// The number of elements to be put in the queue for each test.
#define STRESS_LEVEL	1000

TEST(work_queue, construction)
{
	Buffer<int> q;
}

TEST(work_queue, no_edge_conditions)
{
	Buffer<int> q(2);

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
	Buffer<int> q(2);

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
	Buffer<int> q(2);

	// Do it three times to test growing AND shrinking.
	for(int z = 0; z < 3; ++z)
	{
		for(int i = 0; i < STRESS_LEVEL; ++i)
			q.push(i);

		for(int i = 0; i < STRESS_LEVEL; ++i)
			EXPECT_EQ(i, q.pop());
	}
}

TEST(work_queue, can_use_auto_ptr)
{
	Buffer<std::auto_ptr<int> > q;

	q.push(std::auto_ptr<int>(new int(3)));
	EXPECT_EQ(3, *q.pop());
}

static void producer(Buffer<int>& q, int numToPush)
{
	for(int i = 0; i < numToPush; ++i)
		q.push(i);
}

static void consumer(Buffer<int>& q, int numToPop)
{
	for(int i = 0; i < numToPop; ++i)
		q.pop();
}

TEST(work_queue, single_producer_single_consumer)
{
	Buffer<int> q;

	thread p1(bind(producer, ref(q), STRESS_LEVEL));
	thread c(bind(consumer, ref(q), STRESS_LEVEL));

	p1.join();
	c.join();
}

TEST(work_queue, multiple_producer_single_consumer)
{
	Buffer<int> q;

	thread p1(bind(producer, ref(q), STRESS_LEVEL));
	thread p2(bind(producer, ref(q), STRESS_LEVEL));
	thread p3(bind(producer, ref(q), STRESS_LEVEL));

	thread c(bind(consumer, ref(q), STRESS_LEVEL*3));

	p1.join();
	p2.join();
	p3.join();

	c.join();
}
