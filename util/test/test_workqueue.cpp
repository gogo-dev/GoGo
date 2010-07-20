#include <gtest/gtest.h>

#include <util/WorkQueue.h>

TEST(workqueue, no_edge_conditions)
{
	WorkQueue<int> q;

	q.push(3);
	q.push(2);
	q.push(1);

	EXPECT_EQ(3, q.pop());
	EXPECT_EQ(2, q.pop());
	EXPECT_EQ(1, q.pop());
}

TEST(workqueue, still_works_after_resize)
{
	WorkQueue<int> q;

	for(int i = 0; i < 1000; ++i)
		q.push(i);

	for(int i = 0; i < 1000; ++i)
		EXPECT_EQ(i, q.pop());
}
