#include "gtest/gtest.h"
#include <iostream>
using namespace std;

// 调用时，RUN_ALL_TESTS（）宏：
//   1. 保存所有Google测试标记的状态。
//   2. 为第一个测试创建测试夹具对象。
//   3. 通过SetUp（）初始化它。
//   4. 在fixture对象上运行测试。
//   5. 通过TearDown（）清除夹具。
//   6. 删除夹具。
//   7. 恢复所有Google测试标志的状态。
//   8. 重复上述步骤进行下一个测试，直到所有测试运行结束。

// 定义测试后 使用RUN_ALL_TESTS（）运行它们，如果所有测试成功则返回0，否则返回1。
//   RUN_ALL_TESTS（）运行链接单元中的所有测试 - 它们可以来自不同的测试用例，甚至是不同的源文件。
// 重要：您不能忽略RUN_ALL_TESTS（）的返回值，否则gcc将给您一个编译器错误。
//   此设计的基本原理是自动测试服务基于其退出代码而不是其stdout / stderr输出来确定测试是否已通过;
//   因此您的main（）函数必须返回RUN_ALL_TESTS（）的值。
// 此外，如果测试夹具的构造函数在步骤2中产生致命故障，则步骤3-5没有意义，因此它们被跳过。
//   类似地，如果步骤3产生致命故障，则将跳过步骤4。
// 此外，您应该只调用一次RUN_ALL_TESTS（）。
//   多次调用它会与一些高级Google测试功能（例如线程安全死亡测试）冲突，因此不受支持

// :: testing :: InitGoogleTest（）函数解析Google测试标志的命令行，并删除所有已识别的标志。
//   这允许用户通过各种标志控制测试程序的行为，我们将在AdvancedGuide中介绍。
//   在调用RUN_ALL_TESTS（）之前必须调用此函数，否则标志将无法正确初始化。

// gtest提供了多种事件机制，非常方便我们在案例之前或之后做一些操作。总结一下gtest的事件一共有3种：
// 1. 全局的，所有案例执行前后。
// 2. TestSuite级别的，在某一批案例中第一个案例前，最后一个案例执行后。
// 3. TestCase级别的，每个TestCase前后。
// 1 全局事件
// 要实现全局事件，必须写一个类，继承testing::Environment类，实现里面的SetUp和TearDown方法。如SubEnvironment
// 1. SetUp()方法在所有案例执行前执行
// 2. TearDown()方法在所有案例执行后执行
// 还需要告诉gtest添加这个全局事件，我们需要在main函数中通过testing::AddGlobalTestEnvironment方法将事件挂进来，
//   也就是说，我们可以写很多个这样的类，然后将他们的事件都挂上去
//   也就是在main 开始的时候 testing::AddGlobalTestEnvironment(new SubEnvironment);
// 2 TestSuite事件
// 我们需要写一个类，继承testing::Test，然后实现两个静态方法
// 1. SetUpTestCase() 方法在第一个TestCase之前执行
// 2. TearDownTestCase() 方法在最后一个TestCase之后执行
// 需要使用TEST_F这个宏，第一个参数必须是我们上面类的名字，代表一个TestSuite
// 见gtestFixture.cpp
// 3 TestCase事件
// TestCase事件是挂在每个案例执行前后的，实现方式和上面的几乎一样，不过需要实现的是SetUp方法和TearDown方法：
// 1. SetUp()方法在每个TestCase之前执行
// 2. TearDown()方法在每个TestCase之后执行
// 见gtestFixture.cpp
class SubEnvironment : public testing::Environment
{
public:
    virtual void SetUp()
    {
        std::cout << "SubEnvironment SetUP" << std::endl;
    }
    virtual void TearDown()
    {
        std::cout << "SubEnvironment TearDown" << std::endl;
    }
};

int main(int argc,char* argv[])
{
    testing::AddGlobalTestEnvironment(new SubEnvironment);
    //testing::GTEST_FLAG(output) = "xml:"; //若要生成xml结果文件
    testing::InitGoogleTest(&argc,argv); //初始化
    return RUN_ALL_TESTS();                     //跑单元测试
    //return 0;
}


// gtest也为我们提供了一系列的运行参数
// 对于运行参数，gtest提供了三种设置的途径：
// 1. 系统环境变量
// 2. 命令行参数
// 3. 代码中指定FLAG
// 因为提供了三种途径，就会有优先级的问题， 有一个原则是，最后设置的那个会生效。
// 不过总结一下，通常情况下，比较理想的优先级为：
//   命令行参数 > 代码中指定FLAG > 系统环境变量
// 为什么我们编写的测试案例能够处理这些命令行参数呢？
//   是因为我们在main函数中，将命令行参数交给了gtest，由gtest来搞定命令行参数的问题。
// int _tmain(int argc, _TCHAR* argv[])
// {
// //     testing::InitGoogleTest(&argc, argv);  <<--------

// 这样，我们就拥有了接收和响应gtest命令行参数的能力。
//   如果需要在代码中指定FLAG，可以使用testing::GTEST_FLAG这个宏来设置。
//   比如相对于命令行参数--gtest_output，   如 ./main --gtest_output=xml
//   可以使用testing::GTEST_FLAG(output) = "xml:";来设置。
//   注意到了，不需要加--gtest前缀了。
//   同时，推荐将这句放置InitGoogleTest之前，这样就可以使得对于同样的参数，命令行参数优先级高于代码中指定。
// int _tmain(int argc, _TCHAR* argv[])
// {
//     testing::GTEST_FLAG(output) = "xml:";      <<--------
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
// 最后再来说下第一种设置方式-系统环境变量。如果需要gtest的设置系统环境变量，必须注意的是：
// 1. 系统环境变量全大写，比如对于--gtest_output，响应的系统环境变量为：GTEST_OUTPUT
// 2.  有一个命令行参数例外，那就是--gtest_list_tests，它是不接受系统环境变量的。（只是用来罗列测试案例名称）


// 这里就直接将所有命令行参数总结和罗列一下。如果想要获得详细的命令行说明，直接运行你的案例，
//   输入命令行参数：/? 或 --help 或 -help

// 1. 测试案例集合
// 命令行参数	说明
// --gtest_list_tests	   使用这个参数时，将不会执行里面的测试案例，而是输出一个案例的列表。

// --gtest_filter          对执行的测试案例进行过滤，支持通配符
// ?    单个字符
// *    任意字符
// -    排除，如，-a 表示除了a
// :    取或，如，a:b 表示a或b
// 比如下面的例子：
// ./foo_test 没有指定过滤条件，运行所有案例
// ./foo_test --gtest_filter=* 使用通配符*，表示运行所有案例
// ./foo_test --gtest_filter=FooTest.* 运行所有“测试案例名称(testcase_name)”为FooTest的案例
// ./foo_test --gtest_filter=*Null*:*Constructor* 运行所有“测试案例名称(testcase_name)”或“测试名称(test_name)”包含Null或Constructor的案例。
// ./foo_test --gtest_filter=-*DeathTest.* 运行所有非死亡测试案例。
// ./foo_test --gtest_filter=FooTest.*-FooTest.Bar 运行所有“测试案例名称(testcase_name)”为FooTest的案例，但是除了FooTest.Bar这个案例

// --gtest_also_run_disabled_tests
// 执行案例时，同时也执行被置为无效的测试案例。关于设置测试案例无效的方法为：
// 在测试案例名称或测试名称中添加DISABLED前缀，比如：
//
// // Tests that Foo does Abc.
// TEST(FooTest, DISABLED_DoesAbc) {  }

// class DISABLED_BarTest : public testing::Test {  };

// // Tests that Bar does Xyz.
// TEST_F(DISABLED_BarTest, DoesXyz) {  }

// --gtest_repeat=[COUNT]
// 设置案例重复运行次数，非常棒的功能！比如：
// --gtest_repeat=1000      重复执行1000次，即使中途出现错误。
// --gtest_repeat=-1          无限次数执行。。。。
// --gtest_repeat=1000 --gtest_break_on_failure     重复执行1000次，并且在第一个错误发生时立即停止。这个功能对调试非常有用。
// --gtest_repeat=1000 --gtest_filter=FooBar     重复执行1000次测试案例名称为FooBar的案例。


// 2. 测试案例输出
// 命令行参数	                 说明
// --gtest_color=(yes|no|auto)	输出命令行时是否使用一些五颜六色的颜色。默认是auto。
// --gtest_print_time	输出命令行时是否打印每个测试案例的执行时间。默认是不打印的。

// --gtest_output=xml[:DIRECTORY_PATH\|:FILE_PATH]  将测试结果输出到一个xml中。
// 1.--gtest_output=xml:    不指定输出路径时，默认为案例当前路径。
// 2.--gtest_output=xml:d:\ 指定输出到某个目录
// 3.--gtest_output=xml:d:\foo.xml 指定输出到d:\foo.xml
// 如果不是指定了特定的文件路径，gtest每次输出的报告不会覆盖，而会以数字后缀的方式创建。xml的输出内容后面介绍吧。


// 3. 对案例的异常处理
// 命令行参数	             说明
// --gtest_break_on_failure	调试模式下，当案例失败时停止，方便调试
// --gtest_throw_on_failure	当案例失败时以C++异常的方式抛出

// --gtest_catch_exceptions
// 是否捕捉异常。gtest默认是不捕捉异常的，因此假如你的测试案例抛了一个异常，很可能会弹出一个对话框，这非常的不友好，同时也阻碍了测试案例的运行。如果想不弹这个框，可以通过设置这个参数来实现。如将--gtest_catch_exceptions设置为一个非零的数。
// 注意：这个参数只在Windows下有效。
