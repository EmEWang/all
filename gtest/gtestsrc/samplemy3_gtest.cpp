#include "gtest/gtest.h"
#include "samplemy3.h"

// 显式成功和失败
// SUCCEED表示执行到当前位置时，状态是正确的。不会产生其他消息
// FAIL() 会触发致命错误，整个case会终止
// ADD_FAILURE() and ADD_FAILURE_AT() 只是触发一般错误，case不会终止
// 注意: 你只能在返回值为void的函数里使用FAIL().
void checkValue(int value)
{
    switch(value)
    {
        case 1: SUCCEED();break;
        case 0: SUCCEED();break;
        case -1:SUCCEED();break;
        default:ADD_FAILURE();
    }
}
TEST(testExplicit, Explicit1)
{
    checkValue(1);
    // checkValue(2);

    // SUCCEED() << "~~~~~~~~~~~~";
    // FAIL() << "11111111111111111111";
    // ADD_FAILURE() << "22222222222222";
    // ADD_FAILURE_AT("file_path",123) << "33333333333333";
}


// 异常断言
// 这些用于验证一段代码抛出（或不抛出）给定类型的异常：
// Fatal assertion                           Nonfatal assertion                         Verifies
// ASSERT_THROW(statement, exception_type);  EXPECT_THROW(statement, exception_type);   statement throws an exception of the given type
// ASSERT_ANY_THROW(statement);              EXPECT_ANY_THROW(statement);               statement throws an exception of any type
// ASSERT_NO_THROW(statement);               EXPECT_NO_THROW(statement);                statement doesn't throw any exception
TEST(testException, Exception1)
{
    EXPECT_NO_THROW({int n = 5;});

    //不期望抛出异常 实际抛出
    // EXPECT_NO_THROW({throw 1;});

    //期望抛出异常 不实际抛出
    // EXPECT_ANY_THROW({int n = 1;});
}
TEST(testException, Exception2)
{
    EXPECT_NO_THROW(throwExp(1));
}



// 测试谓词
// 使用场景: 自定义判断函数 对函数进行的值进行测试
// 使用现有的布尔函数
// Fatal assertion                  Nonfatal assertion                  Verifies
// ASSERT_PRED1(pred1, val1);       EXPECT_PRED1(pred1, val1);          pred1(val1) returns true
// ASSERT_PRED2(pred2, val1, val2); EXPECT_PRED2(pred2, val1, val2);    pred2(val1, val2) returns true
TEST(testPRED, test1){
    int a=1,b=2,c=3;
    //EXPECT_TRUE(isEven3_(1,3, 4));
    EXPECT_PRED3(isEven3_, a, b, c);
    //EXPECT_PRED3(isEven3_, 2, 3, 4);
    // EXPECT_PRED3(isEven3, 1, 2, 4);
}


// 使用返回AssertionResult的函数
// 使用场景: 自定义判断函数,并输出额外信息
// AssertionResult对象表示断言的结果（无论它是成功还是失败，以及相关联的消息）。
//   您可以使用以下工厂函数之一创建AssertionResult：
// namespace testing {
// // Returns an AssertionResult object to indicate that an assertion has
// // succeeded.
// AssertionResult AssertionSuccess();

// // Returns an AssertionResult object to indicate that an assertion has
// // failed.
// AssertionResult AssertionFailure();
// }
// 然后，您可以使用<<运算符将消息流式传输到AssertionResult对象

::testing::AssertionResult IsEven3_Result(int n) {
  if ((n % 2) == 0)
    return ::testing::AssertionSuccess() << n << " is even";
  else
    return ::testing::AssertionFailure() << n << " is odd";
}
TEST(AssertionResult, test1){
    // EXPECT_TRUE(IsEven3_Result(1));
    EXPECT_TRUE(IsEven3_Result(2));
}




// 使用谓词格式化
// 使用场景: 错误时，完全自定义错误消息
// 如果你发现由（ASSERT | EXPECT）_PRED *和（ASSERT | EXPECT）_（TRUE | FALSE）生成的默认消息不令人满意，或者您的谓词的某些参数不支持流到ostream，您可以使用以下谓词 - 格式化程序断言 以完全自定义消息的格式化：
// Fatal assertion                                Nonfatal assertion                             Verifies
// ASSERT_PRED_FORMAT1(pred_format1, val1);       EXPECT_PRED_FORMAT1(pred_format1, val1);       pred_format1(val1) is successful
// ASSERT_PRED_FORMAT2(pred_format2, val1, val2); EXPECT_PRED_FORMAT2(pred_format2, val1, val2); pred_format2(val1, val2) is successful
// 这和前两组宏的区别是，不是一个谓词，（ASSERT | EXPECT）_PRED_FORMAT *采用谓词格式化器（pred_formatn），它是一个函数或函数签名：
// ::testing::AssertionResult PredicateFormattern(const char*expr1, const char*expr2, ... const char*exprn, T1val1, T2val2, ... Tnvaln);

::testing::AssertionResult  isGreaterThan10_format(const char* a_expr,const char* b_expr,int a ,int b)
{
     if (add3_(a,b)>=10)
        return ::testing::AssertionSuccess() ;
    // testing::Message msg;
    // msg << "添加 " <<a_expr <<"("<<a<< ")+"<< b_expr<<"("<<b<< ")小于10";
    // return testing::AssertionFailure(msg);
    // 以上三行 效果等于下一行
    return ::testing::AssertionFailure() << "添加 " <<a_expr <<"("<<a<< ")+"<< b_expr<<"("<<b<< ")小于10";
}
TEST(testPREDFormat, test1)
{
    int a=5;
    int b=1;
    // 自定义错误输出
    // EXPECT_PRED_FORMAT2(isGreaterThan10_format,a,b);
    // EXPECT_PRED_FORMAT2(isGreaterThan10_format,2,3);

    //EXPECT_PRED2(add3_, a, b);
}


// 语法 EXPECT_DEATH
// 使用场景: 检验程序的退出码，退出信号，退出时打印的字符串
// 有人问，程序的异常退出码可以用gtest测试吗？回答当然是可以的。
//   case_EXPECT_DEATH 里，GetNullPointer 获取空指针，程序异常退出前输出 Pointer XX is null，
//   则可以被gtest框架捕捉到。并进行判定。
// 要注意的是 EXPECT_DEATH 第二个参数是一个 matcher,是可以对字符串进行正则表达式 匹配。
//EXPECT_DEATH(statement, matcher);
// Fatal assertion                               Nonfatal assertion                            Verifies
// ASSERT_DEATH(statement, regex);               EXPECT_DEATH(statement, regex);               statement crashes with the given error
// ASSERT_DEATH_IF_SUPPORTED(statement, regex);  EXPECT_DEATH_IF_SUPPORTED(statement, regex);  if death tests are supported, verifies that statement crashes with the given error; otherwise verifies nothing
// ASSERT_EXIT(statement, predicate, regex);     EXPECT_EXIT(statement, predicate, regex);     statement exits with the given error and its exit code matches predicate
// 字符串检查支持正则表达式
TEST(DeathTest, case_EXPECT_DEATH)
{
   EXPECT_DEATH(
   {
        const char * p=NULL;
        fprintf(stderr,"Pointer %lx is null",(long)p);
        fflush(stderr);
        if (p[0]=='T')
            printf("Should not enter here");
   },
   " is null");
}
// death1(0) 崩溃怎通过
TEST(DeathTest, death1)
{
  EXPECT_DEATH( death1(0); , "");
}
// NormalExit 则是另外一个例子，当程序通过exit退出的错误码，也可以通过gtest 进行验证。
// 如果程序正常退出并且退出码与exit_code相同则返回 true
TEST(DeathTest, ExitedWithCode)
{
  EXPECT_EXIT( exit(123); ,::testing::ExitedWithCode(123), "");
}
TEST(DeathTest, ExitedWithCode2)
{
  EXPECT_EXIT( fprintf(stderr,"Pointer is null"); fflush(stderr); exit(123); ,::testing::ExitedWithCode(123), "Pointer is null");
}


// 设置程序退出时收到的Signal (只支持在Linux上使用)
TEST(DeathTest, KilledBySignal)
{
  EXPECT_EXIT( raise(11) ,::testing::KilledBySignal(11), "");
}

// 死亡测试运行方式
// 1. fast方式（默认的方式）
// testing::FLAGS_gtest_death_test_style = "fast";
// 2. threadsafe方式
// testing::FLAGS_gtest_death_test_style = "threadsafe";
// 你可以在 main() 里为所有的死亡测试设置测试形式，也可以为某次测试单独设置。Google Test会在每次测试之前保存这个标记并在测试完成后恢复，所以你不需要去管这部分工作 。如：
//
// TEST(MyDeathTest, TestOne) {
//   testing::FLAGS_gtest_death_test_style = "threadsafe";
//   // This test is run in the "threadsafe" style:
//   ASSERT_DEATH(ThisShouldDie(), "");
// }

// TEST(MyDeathTest, TestTwo) {
//   // This test is run in the "fast" style:
//   ASSERT_DEATH(ThisShouldDie(), "");
// }

// int main(int argc, char** argv) {
//   testing::InitGoogleTest(&argc, argv);
//   testing::FLAGS_gtest_death_test_style = "fast";
//   return RUN_ALL_TESTS();
// }
// 注意事项
// 1. 不要在死亡测试里释放内存。
// 2. 在父进程里再次释放内存。
// 3. 不要在程序中使用内存堆检查。


// 语法 SCOPED_TRACE
// 使用场景：判断失败时，显示帮助信息，包括文件和行号
// 本例中，如果case失败时，则在子函数SubFunction里，通过SCOPED_TRACE输出额外信息，便于跟踪调试
// SCOPED_TRACE 可以添加到子函数中，用来补充错误时的信息
// SCOPED_TRACE(message);
void SubFunction()
{
    SCOPED_TRACE("TEST: SubFunction");
    ASSERT_TRUE(0);
}
TEST(SCOPED_TRACE, test1)
{
    int flag  = 0;
    // SubFunction();
}
