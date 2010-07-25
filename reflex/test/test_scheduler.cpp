#include <gtest/gtest.h>

#include <reflex/Scheduler.h>

TEST(scheduler, construction)
{
	reflex::Scheduler s(8);

	EXPECT_TRUE(s.GetTaskTarget());
}
