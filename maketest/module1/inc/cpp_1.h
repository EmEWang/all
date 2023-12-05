#include <bits/stdc++.h>        // 通用头文件


// 主要用于测试c++ 基本概念
// *** 文件 时间
// *** 类
// *** float
// *** hash_map/set unordered_map/set

// *** 文件 时间
void test1_cpp_1_file();
void test1_cpp_1_time();


// *** 类
void test1_cpp_1_class();

// *** float
#include <cfloat>
// ! https://techoverflow.net/2021/04/11/how-to-fix-gcc-undefined-reference-to-_finite-or-implicit-declaration-of-function-_finite/
//  undefined reference to `_finite'     _finite win函数 linux 未定义
#ifdef __linux__// 方法1
#include <math.h>
#define _finite(v) (isfinite((v)))
#endif
// 或者
// #ifdef __linux__// 方法2
// #define _finite(v) (__builtin_isfinite(v))
// #endif
void test1_cpp_1_float_int();


// *** hash_map/set unordered_map/set
// ! https://www.cnblogs.com/leebxo/p/10834933.html
#ifdef __linux__
#define     _GLIBCXX_PERMIT_BACKWARD_HASH               // 若没有 提示 hash_map已过期
#else
#define     _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS   // vs2019
#endif
#include <hash_map>
#include <hash_set>
#include <unordered_map>
#include <unordered_set>
// using namespace std;         // unordered_map/set
// using namespace __gnu_cxx;   // hash_map/set hash_multimap/multiset  linux
// using namespace stdext;      // hash_map/set hash_multimap/multiset  windows
// hash_map unordered_map 本质是一样的，只不过 unordered_map被纳入了C++标准库标准。
void test1_cpp_1_hash_simple();
void test1_cpp_1_hash_selfdef();
void test1_cpp_1_hash_selfdef2();
// hash_map和unordered_map都是用哈希表实现的，它们有什么区别吗？
// 其实区别不大，但是推荐使用unordered_map，因为unordered_map在C++11就被录入标准库了，而hash并没有进入标准库。

// hash_map和map的区别在哪里？
// 构造函数。hash_map需要hash函数，等于函数；map只需要比较函数(小于函数).
// 存储结构。hash_map采用hash表存储，map一般采用红黑树(RB Tree)实现。因此其memory数据结构是不一样的。

// win错误  C1189  #error:  <hash_map> is deprecated and will be REMOVED. Please use <unordered_map>. You can define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS to acknowledge that you have received this warning.    stlTest    C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.29.30133\include\hash_map    22
// 解决方法：
// 1)使用unordered_map代替hash_map(推荐)
// 2)在项目属性->c / c++->预编译器，增加   _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 定义
// 3)在使用include之前，加上      #define     _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 定义

// hash_map，首先分配一大片内存，形成许多桶(下标范围比较大的数组)。是利用hash函数，对key进行映射到不同区域（桶）进行保存。
// 其插入过程是：
//   得到key
//   通过hash函数得到hash值
//   得到桶号(一般都为hash值对桶数求模)
//   存放key和value在桶内。
// 其取值过程是:
//   得到key
//   通过hash函数得到hash值
//   得到桶号(一般都为hash值对桶数求模)
//   比较桶的内部元素是否与key相等，若都不相等，则没有找到。
//   取出相等的记录的value。

// 在声明自己的哈希函数时要注意以下几点：
//   使用struct，然后重载operator().
//   返回是size_t
//   参数是你要hash的key的类型。
//   函数是const类型的。

// 比较函数
//   在map中的比较函数，需要提供less函数。如果没有提供，缺省的也是less< Key> 。
//   在hash_map中，要比较桶内的数据和key是否相等，因此需要的是是否等于的函数:equal_to< Key> 。

//本代码可以从SGI STL
//先看看binary_function 函数声明，其实只是定义一些类型而已。
    // template <class _Arg1, class _Arg2, class _Result>
    // struct binary_function {
    //         typedef _Arg1 first_argument_type;
    //         typedef _Arg2 second_argument_type;
    //         typedef _Result result_type;
    // };
//看看equal_to的定义：
    // template <class _Tp>
    // struct equal_to : public binary_function<_Tp,_Tp,bool>
    // {
    //         bool operator()(const _Tp& __x, const _Tp& __y) const { return __x == __y; }
    // };

// 使用一个自定义的数据类型，如struct mystruct, 如何使用比较函数？
// 使用比较函数，有两种方法. 第一种是：重载==操作符，利用equal_to;看看下面的例子：
// struct mystruct{
//         int iID;
//         int  len;
//         bool operator==(const mystruct & my) const{
//                 return (iID==my.iID) && (len==my.len) ;
//         }
// };
// 这样，就可以使用equal_to< mystruct>作为比较函数了。
// 另一种方法就是使用函数对象。自定义一个比较函数体：
// struct compare_str{
//         bool operator()(const char* p1, const char*p2) const{
//                 return strcmp(p1,p2)==0;
//         }
// };
// 有了compare_str，就可以使用hash_map了。
// typedef hash_map<const char*, string, hash<const char*>, compare_str> StrIntMap;
// StrIntMap namemap;
// namemap["岳不群"]="华山派掌门人，人称君子剑";
// namemap["张三丰"]="武当掌门人，太极拳创始人";
// namemap["东方不败"]="第一高手，葵花宝典";

// hash_map 函数
// hash_map(size_type n) 如果讲究效率，这个参数是必须要设置的。n 主要用来设置hash_map 容器中hash桶的个数。桶个数越多，hash函数发生冲突的概率就越小，重新申请内存的概率就越小。n越大，效率越高，但是内存消耗也越大。
// const_iterator find(const key_type& k) const. 用查找，输入为键值，返回为迭代器。
// data_type& operator[](const key_type& k) . 这是我最常用的一个函数。因为其特别方便，可像使用数组一样使用。不过需要注意的是，当你使用[key ]操作符时，如果容器中没有key元素，这就相当于自动增加了一个key元素。因此当你只是想知道容器中是否有key元素时，你可以使用find。如果你希望插入该元素时，你可以直接使用[]操作符。
// insert 函数。在容器中不包含key值时，insert函数和[]操作符的功能差不多。但是当容器中元素越来越多，每个桶中的元素会增加，为了保证效率，hash_map会自动申请更大的内存，以生成更多的桶。因此在insert以后，以前的iterator有可能是不可用的。
// erase 函数。在insert的过程中，当每个桶的元素太多时，hash_map可能会自动扩充容器的内存。但在sgi stl中是erase并不自动回收内存。因此你调用erase后，其他元素的iterator还是可用的。


