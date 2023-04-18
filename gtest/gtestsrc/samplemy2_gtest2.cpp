#include <gtest/gtest.h>
#include "samplemy2.h"

TEST(Add, Addtest2) {
   EXPECT_EQ(12, Add(11,1));
}

TEST(classCalc, test1) {
    ASSERT_EQ(7, Calc().add(3, 4));
    ASSERT_EQ(150, Calc().add(50, 100));

}
