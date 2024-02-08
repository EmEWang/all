// 打造自己的单元测试框架


#include <iostream>
#include <vector>

using namespace std;

class TestCase
{
public:
    TestCase(const char* case_name) : testcase_name(case_name){}

    // 执行测试案例的方法
    virtual void Run() = 0;

    int nTestResult; // 测试案例的执行结果
    const char* testcase_name; // 测试案例名称
};

class UnitTest
{
public:
    // 获取单例
    static UnitTest* GetInstance();

    // 注册测试案例
    TestCase* RegisterTestCase(TestCase* testcase);

    // 执行单元测试
    int Run();

    TestCase* CurrentTestCase; // 记录当前执行的测试案例
    int nTestResult; // 总的执行结果
    int nPassed; // 通过案例数
    int nFailed; // 失败案例数
protected:
    std::vector<TestCase*> testcases_; // 案例集合
};

UnitTest* UnitTest::GetInstance()
{
    static UnitTest instance;
    return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
{
    testcases_.push_back(testcase);
    return testcase;
}

int UnitTest::Run()
{
    nTestResult = 1;
    for (std::vector<TestCase*>::iterator it = testcases_.begin();
        it != testcases_.end(); ++it)
    {
        TestCase* testcase = *it;
        CurrentTestCase = testcase;
        std::cout <<  "======================================" << std::endl;
        std::cout <<  "Run TestCase:" << testcase->testcase_name << std::endl;
        testcase->Run();
        std::cout <<  "End TestCase:" << testcase->testcase_name << std::endl;
        if (testcase->nTestResult)
        {
            nPassed++;
        }
        else
        {
            nFailed++;
            nTestResult = 0;
        }
    }

    std::cout <<  "======================================" << std::endl;
    std::cout <<  "Total TestCase : " << nPassed + nFailed << std::endl;
    std::cout <<  "Passed : " << nPassed << std::endl;
    std::cout <<  "Failed : " << nFailed << std::endl;
    return nTestResult;
}

#define TESTCASE_NAME(testcase_name) \
    testcase_name##_TEST

#define NANCY_TEST_(testcase_name) \
class TESTCASE_NAME(testcase_name) : public TestCase \
{ \
public: \
    TESTCASE_NAME(testcase_name)(const char* case_name) : TestCase(case_name){}; \
    virtual void Run(); \
private: \
    static TestCase* const testcase_; \
}; \
\
TestCase* const TESTCASE_NAME(testcase_name) \
    ::testcase_ = UnitTest::GetInstance()->RegisterTestCase( \
        new TESTCASE_NAME(testcase_name)(#testcase_name)); \
void TESTCASE_NAME(testcase_name)::Run()

#define NTEST(testcase_name) \
    NANCY_TEST_(testcase_name)


#define RUN_ALL_TESTS() \
    UnitTest::GetInstance()->Run();

 #define EXPECT_EQ(m, n) \
    if (m != n) \
    { \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0; \
        std::cout <<  "Failed" << std::endl; \
        std::cout <<  "Expect:" << m << std::endl; \
        std::cout <<  "Actual:" << n << std::endl; \
    }



int Foo(int a, int b)
{
    return a + b;
}

NTEST(FooTest_PassDemo)
{
    EXPECT_EQ(3, Foo(1, 2));
    EXPECT_EQ(2, Foo(1, 1));
}

NTEST(FooTest_FailDemo)
{
    EXPECT_EQ(4, Foo(1, 2));
    EXPECT_EQ(2, Foo(1, 2));
}

int main(int argc, char* argv[])
{
    return RUN_ALL_TESTS();
}








//宏展开后形式如下
// class FooTest_PassDemo_TEST : public TestCase
// {
// public:
//     FooTest_PassDemo_TEST(const char* case_name) : TestCase(case_name){};
//     virtual void Run();
// private:
//     static TestCase* const testcase_;
// };
// TestCase* const FooTest_PassDemo_TEST ::testcase_ =
// UnitTest::GetInstance()->RegisterTestCase( new FooTest_PassDemo_TEST("FooTest_PassDemo"));
// void FooTest_PassDemo_TEST::Run()
// {
//     if (3 != Foo(1, 2))
//     {
//         UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;
//         std::cout << "Failed" << std::endl;
//         std::cout << "Expect:" << 3 << std::endl;
//         std::cout << "Actual:" << Foo(1, 2) << std::endl;
//     };
//     if (2 != Foo(1, 1))
//     {
//         UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;
//         std::cout << "Failed" << std::endl;
//         std::cout << "Expect:" << 2 << std::endl;
//         std::cout << "Actual:" << Foo(1, 1) << std::endl;
//         };
// }

// class FooTest_FailDemo_TEST : public TestCase
// {
// public:
//     FooTest_FailDemo_TEST(const char* case_name) : TestCase(case_name){};
//     virtual void Run();
// private:
//     static TestCase* const testcase_;
// };
// TestCase* const FooTest_FailDemo_TEST ::testcase_ =
// UnitTest::GetInstance()->RegisterTestCase( new FooTest_FailDemo_TEST("FooTest_FailDemo"));
// void FooTest_FailDemo_TEST::Run()
// {
//     if (4 != Foo(1, 2))
//     {
//         UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;
//         std::cout << "Failed" << std::endl;
//         std::cout << "Expect:" << 4 << std::endl;
//         std::cout << "Actual:" << Foo(1, 2) << std::endl;
//     };
//     if (2 != Foo(1, 2))
//     {
//         UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;
//         std::cout << "Failed" << std::endl;
//         std::cout << "Expect:" << 2 << std::endl;
//         std::cout << "Actual:" << Foo(1, 2) << std::endl;
//     };
// }
// int main(int argc, char* argv[])
// {
//     return UnitTest::GetInstance()->Run();;
// }
