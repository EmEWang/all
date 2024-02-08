#include <gtest/gtest.h>
//#include "src.h"
#include "src.cpp"

// g++ testall.cpp -o testall -lgtest -pthread

TEST(FooTest, HandleNoneZeroInput) {
   EXPECT_EQ(2, Foo(4,10));
   EXPECT_EQ(6, Foo(30,18));
}
TEST(Action, input1) {
   EXPECT_EQ(0, Action(1,1));
   EXPECT_EQ(-1, Action(1,2));
   EXPECT_EQ(1, Action(3,2));
}
TEST(Device, input1) {
   EXPECT_EQ(0, Action(1,1));
   EXPECT_EQ(-1, Action(1,2));
   EXPECT_EQ(1, Action(3,2));
   EXPECT_EQ(1, Action(3,0));
}
TEST(Add, input1) {
   EXPECT_EQ(1, Add(1,1));
   EXPECT_EQ(0, Add(1,0));
   EXPECT_EQ(0, Add(3,-2));
   EXPECT_EQ(1, Add(3,0));
   EXPECT_EQ(1, Add(3,-2));
}

int main(int argc,char*argv[]) {
   testing::InitGoogleTest(&argc,argv);
   return RUN_ALL_TESTS();
}
