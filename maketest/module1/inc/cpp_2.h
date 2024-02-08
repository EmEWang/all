#pragma once

#include <string.h>

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <forward_list>
#include <list>
#include <deque>

#include <algorithm>                // 算法
#include <functional>               // 仿函数
#include <numeric>                  //
#include <memory>                   //
#include <atomic>

// STL 算法库大致可以分为以下几类:
//   非修改性算法(Non-modifying algorithms):不修改容器中的元素。
//     遍历(for_each)、查找(find、find_if)、计数(count、count_if)、搜索(search)等。
//   修改性算法(Modifying algorithms): 修改容器中的元素。 对元素进行操作的算法(如 copy、move、replace、fill)、
//    删除操作(如 remove、unique)以及重新排列元素的操作(如 reverse、rotate、shuffle)。
//   排序和相关操作(Sorting and related operations): 排序容器中的元素，如 sort、stable_sort、partial_sort。
//     还包括用于在已排序的序列中执行操作的算法，如 binary_search、lower_bound、upper_bound。
//   数值算法(Numeric algorithms): 数值计算。
//     包括对序列进行数学运算(如 accumulate、inner_product)和生成数值序列(如 iota、adjacent_difference)。

// find()是一种线性搜索算法。它从容器的开始位置遍历到结束位置，逐个检查每个元素，直到找到目标元素或遍历完所有元素。O(n)
// binary_search()是一种二分搜索算法。它要求容器预先被排序。 O(log n)
// sort()函数的实现原理
// sort() 函数是 C++ STL 中用于排序的一个重要算法。在大多数实现中，它是基于快速排序算法实现的，但具体实现可能会根据不同的情况选择不同的排序算法，以优化性能。以下是 sort() 函数的一些关键特点：
// 快速排序（Quick Sort）: 快速排序是 sort() 函数的主要实现算法。快速排序是一种分治算法，它通过选择一个“枢纽”元素来将数组分成两个子数组，一个包含所有小于枢纽的元素，另一个包含所有大于枢纽的元素。然后，它递归地对这两个子数组进行同样的操作。
// 插入排序（Insertion Sort）: 对于较小的数据集，快速排序可能不如插入排序高效。因此，sort() 函数在处理小数组时可能会使用插入排序。
// 归并排序（Merge Sort）: 在一些实现中，当递归到较小的子数组时，sort() 函数可能会使用归并排序，特别是在需要稳定排序（即相等元素的相对顺序保持不变）时。
// 内省排序（Introsort）: 内省排序是一种混合排序算法，结合了快速排序、堆排序（Heap Sort）和插入排序的特点。它从快速排序开始，但如果递归深度超过某个阈值（通常是基于待排序元素数量的对数），则改用堆排序。
// 性能: sort() 函数通常优化得很好，其平均时间复杂度为 O(n log n)，其中 n 是要排序的元素数量。它比 C 语言中的 qsort 函数更快，因为它使用模板，这允许在编译时进行更多优化。
// 稳定性: 标准并未要求 sort() 函数是稳定的。如果需要稳定排序，可以使用 stable_sort() 函数。

// function
void test1_cpp_2_iterator();   // 1)for 2)赋值 *it 3)cout 输出 *it 4)仿函数 5)copy_if
void test1_cpp_2_ostream_iterator();   // copy
void test1_cpp_2_transform();
void test1_cpp_2_lamda();
void test1_cpp_2_for_each();
void test1_cpp_2_count();
void test1_cpp_2_minmax();
void test1_cpp_2_find_search();
void test1_cpp_2_section();
void test1_cpp_2_modify();
void test1_cpp_2_number();
void test1_cpp_2_fill();


// 容器
// https://zhuanlan.zhihu.com/p/651090509
// https://zhuanlan.zhihu.com/p/657768498
#include <string>
void test1_cpp_2_string();         // 包含c串
void test1_cpp_2_array();          // 静态数组  连续存储 固定大小无法改变
void test1_cpp_2_vector();         // 动态数组  连续存储
void test1_cpp_2_list();           // 双向链表
void test1_cpp_2_forward_list();   // 单链表 (since C++11) 单向的，只能前进(forward)
void test1_cpp_2_deque();          // 双端队列 允许在两端高效的插入/删除 一系列连续的存储块，每个块都是独立分配
// 存储的键值对，其本质都是 pair 类模板创建的 pair 对象   红黑树结构  自动排序 唯一键 快速查找 高效的插入和删除
void test1_cpp_2_map();            // 若map中没有对应的key 返回空 若value为指针 为NULL
void test1_cpp_2_set();            // 自动排序 唯一键 快速查找 高效的插入和删除 集合运算
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
void test1_cpp_2_hash_simple();
void test1_cpp_2_hash_selfdef();
void test1_cpp_2_hash_selfdef2();









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






