#ifndef __MODULE3_STLTEMPLATE_H__
#define __MODULE3_STLTEMPLATE_H__

#include <stdio.h>

#include <iostream>
#include <vector>

#include <algorithm>
#include <functional>
#include <type_traits>

using namespace std;

template<typename T>
void printtype(T t)
{
    printf("type:%s\n", typeid(t).name());
}
template<typename T>
void printtype()
{
    printf("type:%s\n", typeid(T).name());
}

// 同步C和C++ 流的输入输出 默认同步 也就是C++流不缓存 每个c++流的操作 作用到相应的c流缓存中
// 标准C++流: std::cin, std::cout, std::cerr, std::clog, std::wcin, std::wcout, std::wcerr and std::wclog.
// 标准C流  : stdin, stdout and stderr.
// For a standard stream str, synchronized with the C stream f, the following pairs of functions have identical effect:
// 1) std::fputc(f, c) and str.rdbuf()->sputc(c)
// 2) std::fgetc(f) and str.rdbuf()->sbumpc()
// 3) std::ungetc(c, f) and str.rdbuf()->sputbackc(c)
// https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
inline void sync_with_stdiotest()
{
    // static bool sync_with_stdio( bool sync = true );
    std::ios::sync_with_stdio(true);
    std::cout << "a\n";
    std::printf("b\n");
    std::cout << "c\n";

    std::ios::sync_with_stdio(false);
    std::cout << "1\n";
    std::printf("2\n");
    std::cout << "3\n";
}



// 模板参数的按值传递和引用传递
template<typename Fn,typename ...Args>
auto call_by_value(Fn &&fn,Args... args)
{
    return fn(args...);
}
inline void func(int &a)
{
    a = 1;
}
inline void reftest()
{
    int a = 0;
    call_by_value(func,a);           // 模板 默认按值传递
    std::cout << a << std::endl;

    call_by_value(func,std::ref(a)); // ref 底层以指针形式存储 实现引用方式传递
    std::cout << a << std::endl;
    // typename std::enable_if<true>::type;
}



// bind函数与占位符
inline bool great_than(int first,int second)
{
    printf("first %d second %d\n", first, second);
    return first > second;
}
inline void bindtest(){
    std::vector<int> data = {1,2,3,4,5};
    //找到第一个大于3的元素
    auto it = std::find_if(std::cbegin(data),std::cend(data),std::bind(great_than,std::placeholders::_1,3));
    printf("第一个大于3的元素 %d\n", *it);
}



// std::placeholders 占位符。表示新的函数对象中参数的位置。当调用新的函数对象时，新函数对象会调用被调用函数，
//  并且其参数会传递到被调用函数参数列表中持有与新函数对象中位置对应的占位符。
//  _1用于代替回调函数中的第一个参数， _2用于代替回调函数中的第二个参数
inline void func2(int a, int b)
{
    printf("[1] %d [2] %d \n", a, b);
}
inline void func3(int a, int b, int c)
{
    printf("[1] %d [2] %d [3] %d\n", a, b, c);
}
struct class2: public binary_function<int, int, void>
{
    // typedef int 	first_argument_type;   // binary_function 有这些定义 若不继承必须自己定义
    // typedef int 	second_argument_type;
    // typedef bool 	result_type;
    void operator ()(int a, int b)const{   // const 必须有 要不然编译不过
        printf("[1] %d [2] %d \n", a, b);
        // return a < b;
    }
};
inline void placeholderstest(){
    {
        auto f1 = std::bind(func3, 11, std::placeholders::_1, 13);
        f1(1,2,3,4,5);             // 占位符 返回的类型 参数不限 只需要有占位符位置的参数即可
        f1(2);
    }

    {
        typedef std::function<void (int)> fun_1;    // 仿函数
        fun_1 f1 = std::bind(func3, 111, std::placeholders::_1, 113);
        f1(12);
    }

    {
        // bind1st 必须用二元谓词 函数不行
        // 其返回值为 binder1st 类型 重载 的() 必须为 const
        auto it = std::bind1st(class2(), 11);      // 类型为 binder1st
        std::bind1st(class2(), 11)(1);             // 调用
        // binder1st<class2 >(class2(), 10)(5);    // 直接用类型调用
        // binder1st<less<int> >(less<int>(), 10)(5);
        // std::cout << typeid(it).name() << std::endl;
    }

    {
        // bind2nd 必须用二元谓词
        auto it = std::bind2nd(class2(), 22);
        std::bind2nd(class2(), 11)(1);
    }

    // std::is_placeholder 用于判断T是否为占位符，它有一个成员变量value。
    //   如果T是placeholder类型，value的值为1代表 _1，2代表 _2；如果T不是，则value为0。
    {
        using namespace std::placeholders;  // introduces _1
        std::cout << std::is_placeholder<decltype(_1)>::value << '\n';
        std::cout << std::is_placeholder<decltype(_2)>::value << '\n';
        std::cout << std::is_placeholder<int>::value << '\n';
    }

    // std::is_bind_expression 判断是否是bind表达式，有value成员，返回值是true或false
    {
        using namespace std::placeholders;  // introduces _1
        auto increase_int = std::bind (std::plus<int>(),_1,1);
        std::cout << std::boolalpha;
        std::cout << std::is_bind_expression<decltype(increase_int)>::value << '\n';
    }
}



// decltype推导四规则
// 如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么的decltype（e）就是e所命名的实体的类型。
//   此外，如果e是一个被重载的函数，则会导致编译错误。
// 否则 ，假设e的类型是T，如果e是一个将亡值，那么decltype（e）为T&&
// 否则，假设e的类型是T，如果e是一个左值，那么decltype（e）为T&。
// 否则，假设e的类型是T，则decltype（e）为T。
inline void decltypetest()
{
    int i = 4;
    int arr[5] = { 0 };
    int *ptr = arr;
    struct S{ double d; }s ;
    void Overloaded(int);
    void Overloaded(char);//重载的函数
    int && RvalRef();
    const bool Func(int);

    //规则一：推导为其类型
    decltype (arr) var1; //int 标记符表达式
    decltype (ptr) var2;//int *  标记符表达式
    decltype(s.d) var3;//doubel 成员访问表达式
    //decltype(Overloaded) var4;//重载函数。编译错误。

    //规则二：将亡值。推导为类型的右值引用。
    decltype (RvalRef()) var5 = 1;

    //规则三：左值，推导为类型的引用。
    decltype ((i))var6 = i;     //int&
    decltype (true ? i : i) var7 = i; //int&  条件表达式返回左值。
    decltype (++i) var8 = i; //int&  ++i返回i的左值。
    decltype(arr[5]) var9 = i;//int&. []操作返回左值
    decltype(*ptr)var10 = i;//int& *操作返回左值
    decltype("hello")var11 = "hello"; //const char(&)[9]  字符串字面常量为左值，且为const左值。

    //规则四：以上都不是，则推导为本类型
    decltype(1) var12;//const int
    decltype(Func(1)) var13=true;//const bool
    decltype(i++) var14 = i;//int i++返回右值
}



// std::enable_if 顾名思义，满足条件时类型有效
// template <bool, typename T=void>
// struct enable_if {
// };

// template <typename T>
// struct enable_if<true, T> {
//   using type = T;
// };
// 由上可知，只有当第一个模板参数为 true 时，type 才有定义，否则使用 type 会产生编译错误，并且默认模板参数可以让你不必指定类型。

// 用法一：类型偏特化
// 在使用模板编程时，经常会用到根据模板参数的某些特性进行不同类型的选择，或者在编译时校验模板参数的某些特性。例如：
template <typename T, typename Enable=void>
struct check;

template <typename T>
struct check<T, typename std::enable_if<T::value>::type> {
  static constexpr bool value = T::value;
};
// 上述的 check 只希望选择 value==true 的 T，否则就报编译时错误。

// 用法二：控制函数返回类型
// 对于模板函数，有时希望根据不同的模板参数返回不同类型的值，进而给函数模板也赋予类型模板特化的性质。典型的例子可以参看 tuple 的获取第 k 个元素的 get 函数：
// template <std::size_t k, class T, class... Ts>
// typename std::enable_if<k==0, typename element_type_holder<0, T, Ts...>::type&>::type
// get(tuple<T, Ts...> &t) {
//   return t.tail;
// }

// template <std::size_t k, class T, class... Ts>
// typename std::enable_if<k!=0, typename element_type_holder<k, T, Ts...>::type&>::type
// get(tuple<T, Ts...> &t) {
//   tuple<Ts...> &base = t;
//   return get<k-1>(base);
// }
// 由于函数模板不能偏特化，通过 enable_if 便可以根据 k 值的不同情况选择调用哪个 get，进而实现函数模板的多态。

// 用法三：校验函数模板参数类型
// 有时定义的模板函数，只希望特定的类型可以调用，参考 cppreference 官网示例，很好的说明了如何限制只有整型可以调用的函数定义：
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd(T t) {
  return bool(t%2);
}

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even(T t) {
  return !is_odd(t);
}
// 一个通过返回值，一个通过默认模板参数，都可以实现校验模板参数是整型的功能。

// What does "typename =" mean in the template parameters?
// That's an optional template parameter with no name and a default value.
// It's used to apply the enable_if condition; it will create a compiler error if the condition is not met.
// You can use exactly the same syntax for normal method arguments.

template <typename T, typename = int>  // 若 typename = xxx 则编译不过 提示 error: ‘xxx’ does not name a type
bool is_xxx(T t) {
    std::cout << "is_even2:" << t << endl;
    return true;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_xxx2(T t) {
    std::cout << "is_even2:" << t << endl;
    return true;
}
inline void enable_iftest()
{
    // typename std::enable_if<true>::type vl;
    // typename T = typename std::enable_if<std::is_integral<int>::value>::type;
    printtype<void>();
    std::cout << std::boolalpha;
    std::cout << std::is_integral<int>::value;
    std::cout << " type " << typeid(typename std::enable_if<std::is_integral<int>::value>::type).name();
    std::cout << " type " << typeid(typename std::enable_if<true>::type).name();
    std::cout << std::endl;
    // is_even2<int>(1);
}


// 2进制格式转10进制
template <int N>
struct binary {
  static constexpr int value = binary<N / 10>::value << 1 | N % 10;
};
// 特化
template <>
struct binary<0> {
  static constexpr int value = 0;
};
inline void binarytest()
{
    std::cout << binary<101>::value << std::endl;       // 5
    std::cout << binary<1110>::value << std::endl;      // 14
    std::cout << binary<10110>::value << std::endl;     // 22

}

namespace detail {  //函数模板  只应用到其返回类型并没有实际调用 不用写实现 也就是 {} 内的部分
  template <typename T> std::type_identity<T&> try_add_lvalue_reference(int);
  template <typename T> std::type_identity<T>  try_add_lvalue_reference(...);

  template <typename T> std::type_identity<T&&> try_add_rvalue_reference(int);
  template <typename T> std::type_identity<T>   try_add_rvalue_reference(...);
}

template <typename T>
struct add_lvalue_reference2 : decltype(detail::try_add_lvalue_reference<T>(0)) {};
template <typename T>
struct add_rvalue_reference2 : decltype(detail::try_add_rvalue_reference<T>(0)) {};

inline void binarytest2()   // 需要 -std=c++2a
{
    std::cout << std::is_same<char&, add_lvalue_reference2<char>::type>::value << std::endl;    // 1
    std::cout << std::is_same<void,  add_lvalue_reference2<void>::type>::value << std::endl;
}

namespace json {

template <typename T, typename U, typename... Rest>
struct is_one_of : bool_constant<is_one_of<T, U>::value || is_one_of<T, Rest...>::value> {};

template <typename T, typename U>
struct is_one_of<T, U> : is_same<T, U> {};

template <typename T, typename U, typename... Rest>
inline constexpr bool is_one_of_v = is_one_of<T,U, Rest...>::value;


template <typename T>
std::enable_if_t<
    is_one_of_v<
        std::decay_t<T>,    // std::decay means remove reference, and remove cv
        int, long, long long, unsigned,
        unsigned long, unsigned long long,
        float, double, long double>,
    std::string>
dumps(const T &value) {
  return std::to_string(value);
}
}




#endif