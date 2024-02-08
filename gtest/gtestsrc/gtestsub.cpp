#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {  // Demonstrate some basic assertions.
  EXPECT_STRNE("hello", "world");  // Expect two strings not to be equal.
  EXPECT_EQ(7 * 6, 42);  // Expect equality.
}