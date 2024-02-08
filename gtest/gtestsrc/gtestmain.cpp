#include "gtest/gtest.h"
#include <iostream>
using namespace std;



// TEST(test_suit_name, test_name)
// TEST宏的第一个参数是test_suit_name（测试套件），第二个参数是test_name（测试用例test_case）。区别如下
// 测试套件是为某个特殊目标而编制的一组测试输入、执行条件以及预期结果，以便测试某个程序路径或核实是否满足某个特定需求
// 测试用例是测试套件下的一个（组）测试。

// Google Test 是线程安全的，其线程安全特性要依赖 pthreads 库。

// gtest提供了三种设置运行参数的途径：
// 1 命令行参数
// 2 代码中指定FLAG
// 3 系统环境变量
// 优先级原则是，最后设置的那个会生效。
// 通常情况下，比较理想的优先级为：命令行参数 > 代码中指定FLAG > 系统环境变量

// 在main函数中，将命令行参数交给了gtest，由gtest来搞定命令行参数的问题。
// int _tmain(int argc, _TCHAR* argv[])
// {
//     testing::InitGoogleTest(&argc, argv);      <<--------

// 在代码中指定FLAG，可以使用testing::GTEST_FLAG这个宏来设置。
// 相对于命令行参数--gtest_output，   如 ./main --gtest_output=xml
// 可以使用testing::GTEST_FLAG(output) = "xml:";来设置。注意，不需要加--gtest前缀。
// 推荐将这句放置InitGoogleTest之前，这样就可以使得对于同样的参数，命令行参数优先级高于代码中指定。
// int _tmain(int argc, _TCHAR* argv[])
// {
//     testing::GTEST_FLAG(output) = "xml:";      <<--------
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }

// gtest设置系统环境变量，必须注意的是：
// 1. 系统环境变量全大写，比如对于--gtest_output，相应的系统环境变量为：GTEST_OUTPUT
// 2. 有一个命令行参数例外，那就是--gtest_list_tests，它是不接受系统环境变量的。（只是用来罗列测试案例名称）


// ./foo_test --help            # 详细的命令行参数说明       /? 或 -help
// --gtest_list_tests           # 不执行测试案例，而是输出一个案例的列表。
// --gtest_filter               # 对执行的测试案例进行过滤，支持通配符
//   ?    单个字符
//   *    任意字符
//   -    排除，如，-a 表示除了a
//   :    取或，如，a:b 表示a或b
//   ./foo_test                                      # 没有指定过滤条件，运行所有案例
//   ./foo_test --gtest_filter=*                     # 使用通配符*，表示运行所有案例
//   ./foo_test --gtest_filter=FooTest.*             # 运行所有"测试案例名称"FooTest"的案例
//   ./foo_test --gtest_filter=FooTe*.*1             # 运行所有"测试案例名称为FooTe开头"且"测试名称匹配后缀1"的案例
//   ./foo_test --gtest_filter=*F1*:*T1*             # 运行所有"测试案例名称或测试名称包含F1或T1"的案例。
//   ./foo_test --gtest_filter=-*DeathTest.*         # 运行所有非死亡测试案例。
//   ./foo_test --gtest_filter=FooTest.*-FooTest.Bar # 运行所有"测试案例名称为FooTest"的案例，但除了FooTest.Bar这个案例
// --gtest_also_run_disabled_tests  # 执行案例时，同时也执行被置为无效的测试案例。
//   设置测试案例无效的方法为：在测试案例名称或测试名称中添加DISABLED前缀，比如：
//   TEST(FooTest, DISABLED_DoesAbc) {  }   // Tests that Foo does Abc.
//   class DISABLED_BarTest : public testing::Test {  };
//   TEST_F(DISABLED_BarTest, DoesXyz) {  }  // Tests that Bar does Xyz.
// --gtest_repeat=[COUNT]       # 设置案例重复运行次数，非常棒的功能！比如：
//   --gtest_repeat=1000                          # 重复执行1000次，即使中途出现错误。
//   --gtest_repeat=-1                            # 无限次数执行
//   --gtest_repeat=1000 --gtest_break_on_failure # 重复执行1000次，且在第一个错误发生时立即停止。这个功能对调试非常有用。
//   --gtest_repeat=1000 --gtest_filter=FooBar    # 重复执行1000次测试案例名称为FooBar的案例。
// --gtest_color=(yes|no|auto)  # 输出命令行时是否使用一些五颜六色的颜色。默认是auto。
// --gtest_print_time           # 输出命令行时是否打印每个测试案例的执行时间。默认是不打印的。
// --gtest_output=xml[:DIRECTORY_PATH\|:FILE_PATH]  # 将测试结果输出到一个xml中。
//   --gtest_output=xml:              # 不指定输出路径时，默认为案例当前路径。
//   --gtest_output=xml:d:\           # 指定输出到某个目录
//   --gtest_output=xml:d:\foo.xml    # 指定输出到d:\foo.xml
//   如果不是指定了特定的文件路径，gtest每次输出的报告不会覆盖，而会以数字后缀的方式创建。
// --gtest_break_on_failure     # 调试模式下，当案例失败时停止，方便调试
// --gtest_throw_on_failure     # 当案例失败时以C++异常的方式抛出
// --gtest_catch_exceptions     # 是否捕捉异常。默认不捕捉，设置为一个非零的数开启捕捉，注意：这个参数只在Windows下有效。
//   如测试案例抛异常，可能会弹出一个对话框，同时也阻碍了测试案例的运行。如果想不弹这个框，可以通过设置这个参数来实现。



// 调用时，RUN_ALL_TESTS()宏：
// 1. 保存所有Google测试标记的状态。
// 2. 为第一个测试创建测试夹具对象。
// 3. 通过SetUp()初始化它。
// 4. 在fixture对象上运行测试。
// 5. 通过TearDown()清除夹具。
// 6. 删除夹具。
// 7. 恢复所有Google测试标志的状态。
// 8. 重复上述步骤进行下一个测试，直到所有测试运行结束。

// RUN_ALL_TESTS()运行所有定义的测试，如果所有测试成功则返回0，否则返回1。它们来自不同的测试用例，甚至是不同的源文件。
// 重要：不能忽略RUN_ALL_TESTS()的返回值，否则gcc将给您一个编译器错误。
//   return RUN_ALL_TESTS();    <<-------- main 中
//   此设计的基本原理是自动测试服务基于其退出代码而不是其stdout/stderr输出来确定测试是否已通过;
// 若测试夹具的构造函数在步骤2中产生致命故障，则步骤3-5没有意义，它们被跳过。同样，步骤3产生致命故障，则将跳过步骤4。
// 只能调用一次RUN_ALL_TESTS()。多次调用它会与一些高级Google测试功能（例如线程安全死亡测试）冲突，因此不受支持。

// ::testing::InitGoogleTest()函数解析Google测试标志的命令行，并删除所有已识别的标志。
//   在调用RUN_ALL_TESTS()之前必须调用此函数，否则标志将无法正确初始化。

// gtest提供了多种事件机制，方便在案例之前或之后做一些操作。总结一下gtest的事件一共有3种：
//   1. 全局的，所有案例执行前后。
//   2. TestSuite级别的，在某一批案例中第一个案例前，最后一个案例执行后。
//   3. TestCase级别的，每个TestCase前后。
// 1 全局事件
//   要写一个类，继承testing::Environment，实现里面的SetUp和TearDown方法。如 SubEnvironment
//   1.1 SetUp()方法在所有案例执行前执行
//   1.2 TearDown()方法在所有案例执行后执行
//   1.3 在main函数中通过testing::AddGlobalTestEnvironment方法将事件挂进来，告诉gtest添加这个全局事件，
//     可以有多个这样的类，然后将它们都挂上去；要在main 开始的时候调用
// 2 TestSuite事件
//   要写一个类，继承testing::Test，然后实现两个静态方法 见gtestFixture.cpp/gtestparam.cpp
//   2.1 SetUpTestCase()    在每个TestSuite之前执行
//   2.2 TearDownTestCase() 在每个TestSuite之后执行
//   需要使用TEST_F这个宏，第一个参数必须是我们上面类的名字，代表一个TestSuite
// 3 TestCase事件
//   挂在每个案例执行前后的，实现方式和上面的几乎一样，实现两个虚拟方法：见gtestFixture.cpp/gtestparam.cpp
//   1. SetUp()    在每个TestCase之前执行
//   2. TearDown() 在每个TestCase之后执行
class SubEnvironment : public testing::Environment{
public:
    virtual void SetUp(){std::cout << "SubEnvironment SetUP" << std::endl;}
    virtual void TearDown(){std::cout << "SubEnvironment TearDown" << std::endl;}
};
class SubEnvironment2 : public testing::Environment{
public:
    virtual void SetUp(){std::cout << "SubEnvironment SetUP2" << std::endl;}
    virtual void TearDown(){std::cout << "SubEnvironment TearDown2" << std::endl;}
};
int main(int argc,char* argv[])
{
    testing::AddGlobalTestEnvironment(new SubEnvironment);
    testing::AddGlobalTestEnvironment(new SubEnvironment2);
    //testing::GTEST_FLAG(output) = "xml:"; //若要生成xml结果文件
    testing::InitGoogleTest(&argc,argv); //初始化
    return RUN_ALL_TESTS();                     //跑单元测试
    //return 0;
}


