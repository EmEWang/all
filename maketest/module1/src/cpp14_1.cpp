#include "cpp14_1.h"


auto func14_1(int i) {return i;}
auto func14_2(bool flag) {  // 1 函数内如果有多个return语句，它们必须返回相同的类型，否则编译失败
    if (flag) return 1;
    // else return 2.3; // error   // inconsistent deduction for auto return type: ‘int’ and then ‘double’
    // return {1, 2, 3}; // error returning initializer list   2 如果return语句返回初始化列表，返回值类型推导也会失败
    return 0;
}
auto func14_3(int i) { // 5 返回类型推导可以用在递归函数中，但递归调用必须以至少一个返回语句作为先导，以便编译器推导出返回类型
    if (i == 1)
        return i;              // return int
    else
        return func14_3(i - 1) + i; // ok
}
template<typename T> auto t14_1(T t) { return t; }
void test1_cpp14_1_return_deduction()
{
    using namespace std;
    // C++14对函数返回类型推导规则做了优化
    // 4 返回类型推导可以用在前向声明中，但是在使用它们之前，翻译单元中必须能够得到函数定义
    cout << func14_1(4) << endl;
    // ~/test$ g++ test.cc -std=c++11    C++11是不能通过编译的
    // test.cc:5:16: error: ‘func’ function uses ‘auto’ type specifier without trailing return type
    // auto func(int i) {
    //                 ^
    // test.cc:5:16: note: deduced return type only available with -std=c++14 or -std=gnu++14

    // 返回值类型推导也可以用在模板中
    cout << t14_1(4) << endl;
    cout << t14_1(3.4) << endl;

    struct A { // 3  如果函数是虚函数，不能使用返回值类型推导
    // error: virtual function cannot have deduced return type
    // virtual auto func() { return 1; }
    };
}

void test1_cpp14_1_lambda_auto()
{
    auto f = [] (int a) { return a; };   // 在C++11中，lambda表达式参数需要使用具体的类型声明
    auto f2 = [] (auto a) { return a; }; // 在C++14中，对此进行优化，lambda表达式参数可以直接是auto
    std::cout << f2(1)    << std::endl;
    std::cout << f2(2.3f) << std::endl;
}

template<class T> constexpr T pi = T(3.1415926535897932385L); // C++14支持变量模板
template<typename T, typename U> struct A {T t;U u;};
template<typename T> using B = A<T, int>;                     // C++14也支持别名模板
void test1_cpp14_1_template()
{
    std::cout << pi<int>    << std::endl; // 3
    std::cout << pi<double> << std::endl; // 3.14159

    B<double> b;
    b.t = 10;
    b.u = 20;
    std::cout << b.t << std::endl;
    std::cout << b.u << std::endl;
}


constexpr int f14_recursion(int n) { // C++14 和 C++11均可
    return n <= 1 ? 1 : (n * f14_recursion(n - 1));
}
constexpr int f14_recursion2(int n) { // C++11中不可，C++14中可以
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        ret += i;
    }
    return ret;
}
constexpr int f14_constexpt_return(bool flag) { // C++14 和 C++11均可
    return 0;
}
constexpr int f14_constexpt_return2(bool flag) { // C++11中不可，C++14中可以
    if (flag) return 1;
    else return 0;
}
void test1_cpp14_1_constexpr()
{
    // C++14相较于C++11对constexpr减少了一些限制
    // 1 C++11中constexpr函数可以使用递归，在C++14中可以使用局部变量和循环  f14_recursion
    // 2 C++11中constexpr函数必须必须把所有东西都放在一个单独的return语句中，而constexpr则无此限制 f14_constexpt_return
}


void test1_cpp14_1_mark_deprecated()
{
    // C++14中增加了deprecated标记，修饰类、变、函数等，当程序中使用到了被其修饰的代码时，编译时被产生警告，
    // 用户提示开发者该标记修饰的内容将来可能会被丢弃，尽量不要使用。
    // struct [[deprecated]] A { };  //  warning: ‘A’ is deprecated [-Wdeprecated-declarations]
    // A a;
}

void test1_cpp14_1_literal()
{
    // C++14引入了二进制字面量与整形字面量分隔符
    int a = 0b0001'0011'1010;
    double b = 3.14'1234'1234'1234;
}

#include <memory>
void test1_cpp14_1_make_unique()
{
    // C++11中有std::make_shared，却没有std::make_unique，在C++14已经改善。
    struct A {};
    std::unique_ptr<A> ptr = std::make_unique<A>();
}

#include <shared_mutex>
void test1_cpp14_1_shared_lock()
{
    // C++14通过std::shared_timed_mutex和std::shared_lock来实现读写锁，保证多个线程可以同时读，
    // 但是写线程必须独立运行，写操作不可以同时和读操作一起进行。
    struct ThreadSafe {
        mutable std::shared_timed_mutex mutex_;
        int value_;

        ThreadSafe() {value_ = 0;}

        int get() const {
            std::shared_lock<std::shared_timed_mutex> loc(mutex_);
            return value_;
        }

        void increase() {
            std::unique_lock<std::shared_timed_mutex> lock(mutex_);
            value_ += 1;
        }
    };
}

template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}
// std::integer_sequence和std::tuple的配合使用
template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}
template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(std::index_sequence<Is...>, F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}
template <typename S, typename F, typename T>
auto map_filter_tuple(F&& f, T& t) {
    return map_filter_tuple(S{}, std::forward<F>(f), t);
}
void test1_cpp14_1_integer_sequence()
{
    // C++11中有std::make_shared，却没有std::make_unique，在C++14已经改善。
    print_sequence(std::integer_sequence<int, 9, 2, 5, 1, 9, 1, 6>{});
}

void test1_cpp14_1_exchange()
{
    // template<class T, class U = T>
    // constexpr T exchange(T& obj, U&& new_value) {
    //     T old_value = std::move(obj);
    //     obj = std::forward<U>(new_value);
    //     return old_value;
    // }
    // 可以看见new_value的值给了obj，而没有对new_value赋值，这里相信您已经知道了它和swap的区别了吧！
    std::vector<int> v;
    std::exchange(v, {1,2,3,4});

    for (int a : v) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

