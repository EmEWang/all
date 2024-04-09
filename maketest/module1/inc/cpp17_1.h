#ifndef __MODULE1_CPP17_1_H__
#define __MODULE1_CPP17_1_H__

#include <utility>
#include <map>
#include <vector>
#include <iostream>
#include <stdio.h>


// 主要用于测试c++17
// 需要c++17 支持  make CXXFLAGS=-std=c++17

// C++17前只有内联函数，现在有了内联变量，C++类的静态成员变量在头文件中是不能初始化的，但是有了内联变量，就可以达到此目的
struct st_A {
    static const int value;
    static const int value2 = 20;    // 内联变量
};
inline int const st_A::value = 10;   // 内联变量

// namespace嵌套
namespace A {
    namespace B {
        namespace C {
            auto func1 = []{};
        }
    }
}
// c++17，更方便更舒适
namespace A::B::C {
    auto func2 = []{};
}

// __has_include预处理表达式
// 可以判断是否有某个头文件，代码可能会在不同编译器下工作，不同编译器的可用头文件有可能不同，所以可以使用此来判断
#if defined __has_include
#if __has_include(<charconv>)
#define has_charconv 1
#include <charconv>
#endif
#endif

inline std::optional<int> ConvertToInt(const std::string& str) {
    int value{};
#ifdef has_charconv
    const auto last = str.data() + str.size();
    const auto res = std::from_chars(str.data(), last, value);
    if (res.ec == std::errc{} && res.ptr == last) return value;
#else
    // alternative implementation...  其它方式实现
#endif
    return std::nullopt;
}


void test1_cpp17_1_template_deduction();
void test1_cpp17_1_struct_binding();
void test1_cpp17_1_if_switch();
void test1_cpp17_1_if_constexpr();
void test1_cpp17_1_template_fold(); // C++17引入了折叠表达式使可变参数模板编程更方便
void test1_cpp17_1_constexpr_lambda();
void test1_cpp17_1_lambda_this();
void test1_cpp17_1_attribute();
#include <charconv>
void test1_cpp17_1_string_convert(); // 新增from_chars函数和to_chars函数
#include <variant>
void test1_cpp17_1_variant();
void test1_cpp17_1_optional();       // #include <optional>  https://www.cnblogs.com/hwx0000/p/15676495.html
#include <any>
void test1_cpp17_1_any();
void test1_cpp17_1_any_variant_diff(); // https://blog.csdn.net/qq_21438461/article/details/132453206
void test1_cpp17_1_apply();
void test1_cpp17_1_make_from_tuple();
void test1_cpp17_1_as_const();
#include <filesystem>
void test1_cpp17_1_file_system();

#include <string_view> // 头文件
void test1_cpp17_1_string_view();


void test1_cpp17_1_lock();   // c++11 c++14 c++17锁的操作 https://blog.csdn.net/liguan1102/article/details/116236702

#endif