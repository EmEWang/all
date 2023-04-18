#include "gtest/gtest.h"
#include <vector>
using namespace std;


// 如果若干个Test Case 要公用参数，按就需要使用 Test Fixtures
// 总体流程如下：
// 构建一个类，继承 ::testing::Test 使用protected 或public 继承 想从子类访问fixture成员
// 需要继承的成员变量（测试中用到的各种参数）都放在 protected 里面 public也可以
// 使用 SetUp 作为初始化参数的方法。 或者编写 默认构造函数
// 如果需要，写一个析构函数或TearDown（）函数来释放你在SetUp（）中分配的任何资源
// 如果需要，也可以定义成员变量，在各种测试中复用。
// 使用 TEST_F 且第一个参数必须为 定义的测试类
// 在自定义的类中可以继续继承

// The fixture for testing class Foo
class vectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
     v1_.push_back(1);
     v2_.push_back(2);
     v2_.push_back(3);
     std::cout << "~~~vectorTest SetUp~~~" << std::endl;
  }

  static void SetUpTestCase()
  {
    std::cout << "~~~vectorTest SetUpTestCase~~~" << std::endl;
  }

  static void TearDownTestCase()
  {
    std::cout << "~~~vectorTest TearDownTestCase~~~" << std::endl;
  }


  void TearDown() override
  {
    std::cout << "~~~vectorTest TearDown~~~" << std::endl;
  }

  vector<int> v0_;
  vector<int> v1_;
  vector<int> v2_;
};


// 当这些测试运行时，会发生以下情况：
//   1.Google Test构造了一个vectorTest对象（我们称之为t1）。
//   2.t1.SetUp（）初始化t1。
//   3.第一个测试（IsEmptyInitially）在t1上运行。
//   4.t1.TearDown（）在测试完成后清理。
//   5.t1被析构。
//   6.以上步骤在另一个QueueTest对象上重复，这次运行DequeueWorks测试。

TEST_F(vectorTest, IsEmptyInitially) {
  EXPECT_EQ(v0_.size(), 0);
  EXPECT_EQ(v1_.size(), 1);
}

TEST_F(vectorTest, DequeueWorks) {
  int n = *v1_.begin();
  v1_.pop_back();
  EXPECT_EQ(n, 1);
  EXPECT_EQ(v1_.size(), 0);

  EXPECT_EQ(v2_.size(), 2);
}
