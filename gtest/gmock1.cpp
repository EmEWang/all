// gmock 是模拟实现 而不是调用实现 也就是在其mock子类中实现的了父类中的方法
//   并根据不同的宏实现不同的功能

// #include <cstdlib>
// #include <gmock/gmock.h>
// #include <gtest/gtest.h>
// #include <iostream>
// #include <string>

// using namespace std;
// using ::testing::Return;

// class foointerface{
//     public:
//     virtual ~foointerface(){}
//     virtual string getArbitraryString() = 0;
// };


// class mockfoo : public foointerface{
//     public:
//     MOCK_METHOD0(getArbitraryString, string());
// };

// int main(int argc, char** argv) {
//         ::testing::InitGoogleMock(&argc, argv);
//         // ::testing::InitGoogleTest(&argc, argv);

//         string value = "Hello World!";
//         string returnValue;
//         mockfoo mockFoo;
//         EXPECT_CALL(mockFoo, getArbitraryString()).Times(1).
//                 WillOnce(Return(value));
//         returnValue = mockFoo.getArbitraryString();
//         cout << "Returned Value: " << returnValue << endl;

// return RUN_ALL_TESTS();
//         return EXIT_SUCCESS;
// }

// TEST(Atest, getnum)
// {
//     mockfoo m_A;
//     int a = 10;
//     string str = "123abc";
//     EXPECT_CALL(m_A, getArbitraryString()).WillRepeatedly(Return(str));
//     string returnValue = m_A.getArbitraryString();
//     EXPECT_EQ("123abc", returnValue);
// }



#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using namespace testing;
using namespace std;

class A {
public:
    int set(int num)
    {
        value = num;
        return num;
    }
    int get()
    {
        return value;
    }

    void set(int num, float fv)
    {
        value = num;
        fvalue = fv;
    }
    float getf()
    {
        return fvalue;
    }

    string set(int num, float &fv, string &tmp)
    {
        value = num;
        fvalue = fv;
        str = tmp;

        fv =99.0;
        tmp = "zzz";

        cout << "qqqqqqqqqqqqq" << endl;
        printf("```````````` %s %f\n", tmp.c_str(), fv);

        return str;
    }

    int value;
    float fvalue;
    string str;
};

class MockA : public A {
public:
    MOCK_METHOD1(set, int(int num));
    MOCK_METHOD0(get, int());
    MOCK_METHOD2(set, void(int num, float fv));
    MOCK_METHOD0(getf, float());
    MOCK_METHOD3(set, string(int, float&, string&));

};

// - 表示任何参数 定于在 ::testing 空间下
TEST(Atest, getnum)
{
    MockA m_A;
    int a = 10;
    EXPECT_CALL(m_A, set(_)).WillRepeatedly(Return(a));
    int k = m_A.set(200);
    EXPECT_EQ(10, k);
}

TEST(Atest, getfloat)
{
    MockA m_A;
    int a = 10;
    float f = 10.0;
    EXPECT_CALL(m_A, set(_,_)).Times(2);
    m_A.set(20, 11.0);
    m_A.set(20, 11.0);
    EXPECT_CALL(m_A, getf()).WillRepeatedly(Return(f));
    float ff = m_A.getf();
    EXPECT_NEAR(11, ff, 1.1);
}

TEST(Atest, setstring)
{
    MockA m_A;
    int a = 10;
    float f = 8.0;
    float f2 = 8.0;
    string str = "qqq";
    string str2 = "www";
    EXPECT_CALL(m_A, set(_,_,_)).WillOnce(DoAll(SetArgReferee<2>(str2),SetArgReferee<1>(f2), Return(str)));
    string str3 = m_A.set(20, f, str);
    cout << "str:" << str << " str2" << str2 << " str3" << str3 << " f:" << f<< " f2:" << f2 << endl;
}



int main(int argc, char *argv[]) {
    // only print if compile flag set
#ifdef EX2
  std::cout << "Hello Compile Flag EX2!" << std::endl;
#endif

#ifdef EX3
  std::cout << "Hello Compile Flag EX3!" << std::endl;
#endif
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
