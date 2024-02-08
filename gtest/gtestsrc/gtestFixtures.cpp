#include "gtest/gtest.h"
#include <vector>
using namespace std;


// 如果若干个Test Case使用同一套数据，按就需要 Test Fixtures (夹具)
// 总体流程如下：
// 1 构建一个子类，protected或public 继承 ::testing::Test
//   可以定义成员变量，在各种测试中复用。
//   想从子类访问fixture成员 需要继承的成员变量(测试中用到的各种参数)放在 protected或public里面
//   SetUpTestCase() 和 TearDownTestCase() 在test_suit 前后分别会被调用
//   SetUp()或默认构造函数 作为初始化参数的方法。             在每个test_case 即TEST_F前会被调用
//   TearDown()或析构函数  释放你在SetUp()中分配的任何资源    在每个test_case 即TEST_F后会被调用
// 2 TEST_F 参数1必须为继承的类 参数2任意
//   每个test_case前创建新的类对象，test_case后删除之。

int g_index = 0;
// The fixture for testing class Foo
class vectorTest : public ::testing::Test {
protected:
  void SetUp() override {
    v0_.push_back(1);
    v1_.push_back(1);
    vs0_.push_back(1);
    g_index++;
    // std::cout << "~~~vectorTest SetUp()~~~" << std::endl;
  }

  void TearDown() override {
    // std::cout << "~~~vectorTest TearDown()~~~" << std::endl;
  }

public:
  // vectorTest(){std::cout << "~~~vectorTest vectorTest()~~~" << std::endl;}
  // ~vectorTest(){std::cout << "~~~vectorTest ~vectorTest()~~~" << std::endl;}
  static void SetUpTestCase() {
    vectorTest::vs0_.push_back(1);
    vectorTest::vs1_.push_back(1);
    vectorTest::vs2_.push_back(1);
    g_index++;
    // std::cout << "~~~vectorTest SetUpTestCase()~~~" << std::endl;
  }

  static void TearDownTestCase() {
    vectorTest::vs0_.clear();
    vectorTest::vs1_.clear();
    vectorTest::vs2_.clear();
    // std::cout << "~~~vectorTest TearDownTestCase()~~~" << std::endl;
  }

  vector<int> v0_;
  vector<int> v1_;
  vector<int> v2_;
  static vector<int> vs0_;
  static vector<int> vs1_;
  static vector<int> vs2_;
};

vector<int> vectorTest::vs0_;
vector<int> vectorTest::vs1_;
vector<int> vectorTest::vs2_;

// 当这些测试运行时，会发生以下情况：
// 1.Google Test构造了一个vectorTest对象(称之为t1)。
// 2.t1.SetUp()初始化t1。
// 3.第一个测试(IsEmptyInitially)在t1上运行。
// 4.t1.TearDown()在测试完成后清理。
// 5.t1被析构。
// 6.以上步骤在另一个QueueTest对象上重复，这次运行DequeueWorks测试。

TEST_F(vectorTest, IsEmptyInitially) {
  EXPECT_EQ(v0_.size(), 1);
  EXPECT_EQ(v1_.size(), 1);
  EXPECT_EQ(g_index, 2);
}
TEST_F(vectorTest, IsEmptyInitially2) {
  EXPECT_EQ(v0_.size(), 1);
  EXPECT_EQ(v1_.size(), 1);
  EXPECT_EQ(g_index, 3);
}

TEST_F(vectorTest, DequeueWorks) {
  int n = *v1_.begin();
  v1_.pop_back();
  EXPECT_EQ(n, 1);
  EXPECT_EQ(v0_.size(), 1);
  EXPECT_EQ(v1_.size(), 0);
  EXPECT_EQ(g_index, 4);
}
