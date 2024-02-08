// gmock 是模拟实现 而不是调用实现 是在其mock子类中实现的了父类中的方法 并根据不同的宏实现不同的功能

// 对方法期望行为的定义的语法格式如下：
// EXPECT_CALL(mock_obj, method(matcher1, matcher2, ...))  # mock_obj是你Mock类的对象 method是你Mock类中某个方法名
//     .With(multi_argument_matcher)
//     .Times(cardinality)        # 之前定义的method运行几次
//     .InSequence(sequences)     # 定义这个方法被执行顺序(优先级)
//     .After(expectations)
//     .WillOnce(action)          # 定义一次调用时所产生的行为
//     .WillRepeatedly(action)    # 缺省/重复行为
//     .RetiresOnSaturation();

// 如 调用mockTurtle的getX()方法 这个方法会至少调用5次 第1次被调用时返回100 第2次返回150 从第3次返回200
// EXPECT_CALL(mockTurtle, getX()).Times(testing::AtLeast(5)).
//                 WillOnce(testing::Return(100)).WillOnce(testing::Return(150)).
//                 WillRepeatedly(testing::Return(200))

// Matcher(匹配器)
// 通配符
// _              代表任意类型参数    定于在 ::testing 空间下
// A() or An()    是type类型的任意值  定于在 ::testing 空间下

// 一般比较
// Eq(value) 或者 value    argument == value，method中的形参必须是value
// Ge(value)               argument >= value，method中的形参必须大于等于value
// Gt(value)               argument > value
// Le(value)               argument <= value
// Lt(value)               argument < value
// Ne(value)               argument != value
// IsNull()                method的形参必须是NULL指针
// NotNull()               argument is a non-null pointer
// Ref(variable)           形参是variable的引用
// TypedEq(value)          形参的类型必须是type类型，而且值必须是value

// 浮点数的比较
// DoubleEq(a_double)                形参是一个double类型，比如值近似于a_double，两个NaN是不相等的
// FloatEq(a_float)                  同上，只不过类型是float
// NanSensitiveDoubleEq(a_double)    形参是一个double类型，比如值近似于a_double，两个NaN是相等的，这个是用户所希望的方式
// NanSensitiveFloatEq(a_float)      同上，只不过形参是float

// 字符串匹配
// 这里的字符串即可以是C风格的字符串，也可以是C++风格的。
// ContainsRegex(string)    形参匹配给定的正则表达式
// EndsWith(suffix)         形参以suffix截尾
// HasSubstr(string)        形参有string这个子串
// MatchesRegex(string)     从第一个字符到最后一个字符都完全匹配给定的正则表达式.
// StartsWith(prefix)       形参以prefix开始
// StrCaseEq(string)        参数等于string，并且忽略大小写
// StrCaseNe(string)        参数不是string，并且忽略大小写
// StrEq(string)            参数等于string
// StrNe(string)            参数不等于string

// 容器的匹配
// 很多STL的容器的比较都支持==这样的操作，对于这样的容器可以使用上述的Eq(container)来比较。但如果你想写得更为灵活，可以使用下面的这些容器匹配方法：
// Contains(e)                   在method的形参中，只要有其中一个元素等于e
// Each(e)                       参数各个元素都等于e
// ElementsAre(e0, e1, …, en)    形参有n+1的元素，并且挨个匹配
// ElementsAreArray(array)       或者ElementsAreArray(array, count)    和ElementsAre()类似，除了预期值/匹配器来源于一个C风格数组
// ContainerEq(container)        类型Eq(container)，就是输出结果有点不一样，这里输出结果会带上哪些个元素不被包含在另一个容器中
// Pointwise(m, container)
// EXPECT_CALL(mockFoo, setDoubleValues(Eq(1), Ge(1)));  参数1==1 参数2 >=1  mockFoo.setDoubleValues(1, 3);

// 成员匹配器
// Field(&class::field, m)        argument.field (或 argument->field, 当argument是一个指针时)与匹配器m匹配, 这里的argument是一个class类的实例.
// Key(e)                         形参(argument)比较是一个类似map这样的容器，然后argument.first的值等于e
// Pair(m1, m2)                   形参(argument)必须是一个pair，并且argument.first等于m1，argument.second等于m2.
// Property(&class::property, m)  argument.property()(或argument->property(),当argument是一个指针时)与匹配器m匹配, 这里的argument是一个class类的实例.
// EXPECT_CALL(mockFoo, get(Field(&Bar::num, Ge(0)))).Times(1);  mockFoo.get(bar); 说明Bar的成员变量num必须大于等于0

// 匹配函数或函数对象的返回值
// ResultOf(f, m)          f(argument) 与匹配器m匹配, 这里的f是一个函数或函数对象.

// 指针匹配器
// Pointee(m)              argument (不论是智能指针还是原始指针) 指向的值与匹配器m匹配.

// 复合匹配器
// AllOf(m1, m2, …, mn)    argument 匹配所有的匹配器m1到mn
// AnyOf(m1, m2, …, mn)    argument 至少匹配m1到mn中的一个
// Not(m)                  argument 不与匹配器m匹配
// EXPECT_CALL(foo, DoThis(AllOf(Gt(5), Ne(10))));   传入的参数必须 >5 并且 <= 10
// EXPECT_CALL(foo, DoThat(Not(HasSubstr("blah")), NULL));  第一个参数不包含“blah”这个子串

// 基数(Cardinalities)
// 基数用于Times()中来指定模拟函数将被调用多少次
// AnyNumber()           函数可以被调用任意次.
// AtLeast(n)            预计至少调用n次.
// AtMost(n)             预计至多调用n次.
// Between(m, n)         预计调用次数在m和n(包括n)之间.
// Exactly(n) 或 n       预计精确调用n次. 特别是, 当n为0时,函数应该永远不被调用.

// 行为(Actions)
// Actions(行为)用于指定Mock类的方法所期望模拟的行为：比如返回什么样的值、对引用、指针赋上怎么样个值，等等。 值的返回
// Return()             让Mock方法返回一个void结果
// Return(value)        返回值value
// ReturnNull()         返回一个NULL指针
// ReturnRef(variable)  返回variable的引用.
// ReturnPointee(ptr)   返回一个指向ptr的指针

// 另一面的作用(Side Effects)
// Assign(&variable, value)    将value分配给variable

// 使用函数或者函数对象(Functor)作为行为
// Invoke(f)                                 使用模拟函数的参数调用f, 这里的f可以是全局/静态函数或函数对象.
// Invoke(object_pointer, &class::method)    使用模拟函数的参数调用object_pointer对象的mothod方法.

// 复合动作
// DoAll(a1, a2, …, an)    每次发动时执行a1到an的所有动作.
// IgnoreResult(a)         执行动作a并忽略它的返回值. a不能返回void.
// int getParamter(string* a1, string* a2)  将a1指向a2的地址，并且得到方法的返回值
// EXPECT_CALL(mockP, getP(_, _)).Times(1).WillOnce(DoAll(Assign(&a, b), Return(1))); 用DoAll将Assign和Return结合起来
// mockP.getP(a, b);

// 序列(Sequences)
// 默认对于定义的期望行为是无序(Unordered)的，即当定义好了如下的期望行为：
// MockFoo mockFoo;
// EXPECT_CALL(mockFoo, getSize()).WillOnce(Return(1));
// EXPECT_CALL(mockFoo, getValue()).WillOnce(Return(string("Hello World")));
// 对于这样的期望行为的定义，我何时调用mockFoo.getValue()或者何时mockFoo.getSize()都可以的。
// 但有时候我们需要定义有序的(Ordered)的调用方式，即序列 (Sequences) 指定预期的顺序.
// 在同一序列里的所有预期调用必须按它们指定的顺序发生; 反之则可以是任意顺序.则为如下格式
// ::testing::InitGoogleMock(&argc, argv);
// Sequence s1, s2;       // 建立两个序列：s1、s2
// MockFoo mockFoo;
// EXPECT_CALL(mockFoo, getSize()).InSequence(s1, s2).WillOnce(Return(1));   说明getSize()的行为优先于s1、s2
// EXPECT_CALL(mockFoo, getValue()).InSequence(s1).WillOnce(Return(string("Hello World!"))); 说明getValue()的行为在序列s1中
// cout << "First:\t" << mockFoo.getSize() << endl;   把mockFoo.getSize()和mockFoo.getValue()的调用对调则出错
// cout << "Second:\t" << mockFoo.getValue() << endl;
// return EXIT_SUCCESS;




// Mock protected、private方法
// Google Mock也可以模拟protected和private方法，比较神奇啊（其实从这点上也可以看出，
// Mock类不是简单地继承原本的接口，然后自己把它提供的方法实现;Mock类其实就等于原本的接口）。
// 对protected和private方法的Mock和public基本类似，只不过在Mock类中需要将这些方法设置成public。
// Foo.h 带private方法的接口
// class Foo {
// private:
//         virtual void setValue(int value) {};
// public:
//         int value;
// };

// MockFoo.h
// class MockFoo: public Foo {
// public:
//         MOCK_METHOD1(setValue, void(int value));
// };


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using namespace testing;
using namespace std;

class A {
public:
    int set() {return 0;}
    int set(int num) {
        m_ival = num;
        return num;
    }
    void set(int num, float fv) {
        m_ival = num;
        m_fval = fv;
    }
    string set(int num, float &fv, string &tmp) {
        m_ival = num;
        m_fval = fv;
        m_str = tmp;
        fv =99.0;
        tmp = "return";
        // cout << "qqqqqqqqqqqqq" << endl;
        // printf("```````````` %s %f\n", tmp.c_str(), fv);
        return m_str;
    }
    virtual string set(int num, float &fv, string &tmp, int i2) = 0;
    int get() {return m_ival;}
    float getf() {return m_fval;}
    string getstr() {return m_str;}

    int m_ival;
    float m_fval;
    string m_str;
};

class MockA : public A {
public:
    MOCK_METHOD0(set, int());
    MOCK_METHOD1(set, int(int));
    MOCK_METHOD2(set, void(int, float));
    MOCK_METHOD3(set, string(int, float&, string&));
    MOCK_METHOD4(set, string(int, float&, string&, int));
    MOCK_METHOD0(get, int());
    MOCK_METHOD0(getf, float());

};

TEST(Atest, getint)
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
    m_A.set(20, 12.0);
    EXPECT_CALL(m_A, getf()).WillRepeatedly(Return(f));
    float ff = m_A.getf();
    EXPECT_NEAR(10.3, ff, 0.31);
}

TEST(Atest, setstring)
{
    // SetArgReferee<N>(value)行为实现的，这个行为对象是用于设置参数，N是参数的索引，从0开始。
    // SetArgPointee<N>(value)设置指针参数, SetArrayArgument<N>(first, last)，设置数组参数，数组范围[first,last)。
    MockA m_A;
    int a = 10;
    float f = 8.0;
    float f2 = 8.8;
    string str = "str_1";
    string str2 = "str_2";
    EXPECT_CALL(m_A, set(_,_,_)).WillOnce(DoAll(SetArgReferee<2>(str2),SetArgReferee<1>(f2), Return(str)));
    string str3 = m_A.set(20, f, str);
    cout << "str:" << str << " str2:" << str2 << " str3:" << str3 << " f:" << f<< " f2:" << f2 << endl;
    // str:str_2 str2:str_2 str3:str_1 f:8.8 f2:8.8
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
