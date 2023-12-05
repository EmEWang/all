#ifndef __MODULE1_CPP11_3_H__
#define __MODULE1_CPP11_3_H__

#include <stdio.h>

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

// 主要用于测试c++11
// 模板
// *** C 可变参数
// *** 模板 可变参数
// *** 函数模板特化
// *** 函数模板特化2
// *** 类模版特化
// *** std::enable_if


// *** C 可变参数
#include <cstdarg>
inline void vari_int(int count, ...)  // 1 手动使用变量列表
{
    va_list val;
    va_start(val,count);

    for (int i = 0; i < count; i++)
    {
        int t = va_arg(val, int);
        printf("%d ", t);
    }

    va_end(val);
    printf("\n");
}
inline void vari_print(const char*format, ...)  // 2 传递变量列表
{
    va_list val;
    va_start(val, format);
    vfprintf(stdout, format, val);
    va_end(val);
}
#define __vari_print(format, ...) \
printf(format, ##__VA_ARGS__)    // 3 使用gcc的预定义宏__VA_ARGS__传递变量列表 即... ##可省
inline void vari_print2(int type, const char* format, ...)
{
    va_list al;
    va_start(al, format);
    if (type)
    {
        fprintf(stdout, format, va_arg(al, const char*));
    }
    va_start(al, format);
    if (type)
    {
        fprintf(stdout, "----\n");
        fprintf(stdout, format, va_arg(al, const char*));
    }
    va_end(al);
}


// *** 模板 可变参数
// 方法1 递归调用 结束是参数迭代完 空的参数法结束
inline void vari_fun()
{
    cout << endl;
}
template <typename F, typename... T>
void vari_fun(F f, T... args)
{
    cout << f << " ";
    vari_fun(args...);
}

// 方法2 初始化数组方式 其展开格式如下
//  int arr[] = { (dispaly(1),0), (dispaly("http://www.biancheng.net"),0), (dispaly(2.34),0) };
template <typename T>
void vari_fun2(T t)
{
    cout << t << " ";
}
template <typename... T>
void vari_fun2(T... args)
{
    int arr[] = {(vari_fun2(args), 0)...};
    cout << endl;
}

// 可变参数类模板
template<typename... T> class vari_class;                               // 声明
template<> class vari_class<>{public: void print(){cout << endl;}};     // 继承递归出口 泛化特例
template<typename T, typename... args>
class vari_class<T, args...>:public vari_class<args...>                 // public继承
{
public:
    vari_class(T t, args... arg):m_data(t),vari_class<args...>(arg...)  // 构造
    {}
    void print()                                                        // 显示内容
    {
        cout << m_data << " ";                                          // 显示当前类中的内容
        vari_class<args...>::print();                                   // 显示基类中的内容
    }

private:
    T m_data;
};





#include <cstring>
// *** 函数模板特化
// 函数模版
template <class T>
int compare(const T left, const T right)
{
    std::cout <<"in template<class T> compare..." << std::endl;
    return (left - right);
}
// 特化函数模版
template <>
inline int compare<const char*>(const char* left, const char* right)  // inline 否则重复定义
{
    std::cout <<"in special template< > compare..." << std::endl;
    return strcmp(left, right);
}

// 特化的函数模版, 两个特化的模版本质相同, 因此编译器会报错
// error: redefinition of 'int compare(T, T) [with T = const char*]'|
//template < >
//int compare(const char* left, const char* right)
//{
//    return strcmp(left, right);
//}

// 这个其实本质是函数重载
inline int compare(char* left, char* right)
{
    std::cout <<"in overload function compare..." <<std::endl;

    return strcmp(left, right);
}


// *** 函数模板特化2
// 函数模版
template <class T, class U>
int compare2(const T left, const U right)
{
    std::cout <<"in template <class T, class U> compare2..." << std::endl;
    return (left - right);
}
// 函数模版偏特化 特化部分
template <class U>
int compare2(const char* left, const U right)
{
    std::cout <<"in special template<class U> compare2..." << std::endl;
    return 22;
}
// 特化的函数模版
template <>
inline int compare2(const char* left, const char* right)  // inline 否则重复定义
{
    std::cout <<"in special template< > compare2..." << std::endl;
    return strcmp(left, right);
}


// *** 类模版特化
// 一是特化为绝对类型；
// 二是特化为引用，指针类型；
// 三是特化为另外一个类模板。

// 1 特化为绝对类型  直接为某个特定类型做特化
template<class T>
class Compare
{
public:
    static bool IsEqual(const T& lh, const T& rh)
    {
        std::cout <<"in the general class..." <<std::endl;
        return lh == rh;
    }
};
// specialize for float
template<>
class Compare<float>
{
public:
    static bool IsEqual(const float& lh, const float& rh)
    {
        std::cout <<"in the float special class..." <<std::endl;
        return std::abs(lh - rh) < 10e-3;
    }
};
// specialize for double
template<>
class Compare<double>
{
public:
    static bool IsEqual(const double& lh, const double& rh)
    {
        std::cout <<"in the double special class..." <<std::endl;
        return std::abs(lh - rh) < 10e-6;
    }
};
// 如果期望使用偏特化，那么
// template<class T1, class T2>
// class A
// {}
// template<class T1>
// class A<T1, int>
// {}

// 2 特化为引用，指针类型
// 这种特化其实是就不是一种绝对的特化， 它只是对类型做了某些限定，但仍然保留了其一定的模板性，
//   这种特化给我们提供了极大的方便， 如这里， 我们就不需要对int*, float*, double*等等类型分别做特化了。
// 这其实是第二种方式的扩展，其实也是对类型做了某种限定，而不是绝对化为某个具体类型
// specialize for T*
template<class T>
class Compare<T*>
{
public:
    static bool IsEqual(const T* lh, const T* rh)
    {
        return Compare<T>::IsEqual(*lh, *rh);
    }
};

// 3 这就把IsEqual的参数限定为一种vector类型， 但具体是vector还是vector， 我们可以不关心，
//   因为对于这两种类型，我们的处理方式是一样的，我们可以把这种方式称为“半特化”。
// specialize for vector<T>
template<class T>
class Compare<vector<T> >
{
public:
    static bool IsEqual(const vector<T>& lh, const vector<T>& rh)
    {
        if(lh.size() != rh.size()) return false;
        else
        {
            for(int i = 0; i < lh.size(); ++i)
            {
                if(lh[i] != rh[i]) return false;
            }
        }
        return true;
    }
};
// 可以将其“半特化”为任何我们自定义的模板类类型
// 这就是三种类型的模板特化， 我们可以这么使用这个Compare类
// specialize for any template class type
template <class T1>
struct SpecializedType
{
    T1 x1;
    T1 x2;
};
template <class T>
class Compare<SpecializedType<T> >
{
public:
    static bool IsEqual(const SpecializedType<T>& lh, const SpecializedType<T>& rh)
    {
        return Compare<T>::IsEqual(lh.x1 + lh.x2, rh.x1 + rh.x2);
    }
};




// test
inline void test1_cpp11_3_vari()
{
    vari_int(3,1,2,3);
    vari_print("%d--%s--%x\n",123, "abc", 123);
    __vari_print("%d--%s--%x\n",123, "abc", 123);
    vari_fun(123,"abc", 'x', 12.34);
    vari_fun2(123,"abc", 'x', 12.34);
    vari_class<int,string,float> vc(1,"abc", 2.3);
    vc.print();

    // 1 2 3
    // 123--abc--7b
    // 123--abc--7b
    // 123 abc x 12.34
    // 123 abc x 12.34
    // 1 abc 2.3
}


inline void test1_cpp11_3_template()
{
    const char *left = "gatieme";
    const char *right = "jeancheng";
    compare(left, right);      // in special template< > compare...
    compare2(11, 12);          // in template <class T, class U> compare2...
    compare2(left, 12);        // in special template<class U> compare2...
    compare2(left, right);     // in special template< > compare2...

    // int
    int i1 = 10;
    int i2 = 10;
    bool r1 = Compare<int>::IsEqual(i1, i2);
    printf("Compare<int>::IsEqual i1:%d i2:%d r1:%d\n", i1, i2, (int)r1);
    // in the general class...
    // Compare<int>::IsEqual i1:10 i2:10 r1:1

    // float
    float f1 = 10;
    float f2 = 10;
    bool r2 = Compare<float>::IsEqual(f1, f2);
    printf("Compare<float>::IsEqual f1:%f f2:%f r2:%d\n", f1, f2, (int)r2);
    // in the float special class...
    // Compare<float>::IsEqual f1:10.000000 f2:10.000000 r2:1

    // double
    double d1 = 10;
    double d2 = 10;
    bool r3 = Compare<double>::IsEqual(d1, d2);
    printf("Compare<double>::IsEqual d1:%f d2:%f r3:%d\n", d1, d2, (int)r3);
    // in the double special class...
    // Compare<double>::IsEqual d1:10.000000 d2:10.000000 r3:1

    // pointer
    int* p1 = &i1;
    int* p2 = &i2;
    bool r4 = Compare<int*>::IsEqual(p1, p2);
    printf("Compare<int*>::IsEqual p1:%p p2:%p r4:%d\n", p1, p2, (int)r4);
    // in the general class...
    // Compare<int*>::IsEqual p1:0x7fff5885ec80 p2:0x7fff5885ec84 r4:1

    // vector<T>
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    bool r5 = Compare<vector<int> >::IsEqual(v1, v2);
    printf("Compare<vector<int> >::IsEqual v1:%lu v2:%lu r5:%d\n", v1.size(), v2.size(), (int)r5);
    // Compare<vector<int> >::IsEqual v1:2 v2:2 r5:1

    // custom template class
    SpecializedType<float> s1 = {10.1f,10.2f};
    SpecializedType<float> s2 = {10.3f,10.0f};
    bool r6 = Compare<SpecializedType<float> >::IsEqual(s1, s2);
    printf("Compare<SpecializedType<float> >::IsEqual s1:%f s2:%f r6:%d\n", s1.x1+s1.x2, s2.x1+s2.x2, (int)r6);
    // in the float special class...
    // Compare<SpecializedType<float> >::IsEqual s1:20.299999 s2:20.299999 r6:1
}




// *** std::enable_if
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
// 对于模板函数，有时希望根据不同的模板参数返回不同类型的值，进而给函数模板也赋予类型模板特化的性质。
// 典型的例子可以参看 tuple 的获取第 k 个元素的 get 函数：
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
inline void test1_cpp11_3_enable_if()
{
    // typename std::enable_if<true>::type vl;
    // typename T = typename std::enable_if<std::is_integral<int>::value>::type;
    // printtype<void>();            // type:v
    std::cout << std::boolalpha;
    std::cout << std::is_integral<int>::value;   // true
    std::cout << " type " << typeid(typename std::enable_if<std::is_integral<int>::value>::type).name(); // type v
    std::cout << " type " << typeid(typename std::enable_if<true>::type).name();  // type v
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
inline void test1_cpp11_3_binary()
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

inline void test1_cpp11_3_binary2()   // 需要 -std=c++2a
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