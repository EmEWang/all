#ifndef __MODULE1_CPP11_1_H__
#define __MODULE1_CPP11_1_H__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>



// 主要用于测试c++11 基本概念
// *** 列表初始化
// *** 类型推导 auto decltype
// *** type
// *** 流同步
// *** 类
// *** 完美转发
// *** ref
// *** bind placeholders


void test1_cpp11_1_for(); //范围for循环

// *** 列表初始化
void test1_cpp11_1_listinitialization();
void test1_cpp11_1_listinitialization2();
void test1_cpp11_1_listinitialization3();


// *** 类型推导 auto decltype
void test1_cpp11_1_auto();

// decltype推导四规则
// 如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么的decltype(e)就是e所命名的实体的类型。
//   此外，如果e是一个被重载的函数，则会导致编译错误。
// 否则，假设e的类型是T，如果e是一个将亡值，那么decltype(e)为T&&
// 否则，假设e的类型是T，如果e是一个左值，那么decltype(e)为T&。
// 否则，假设e的类型是T，则decltype(e)为T。
void test1_cpp11_1_decltype();
void test1_cpp11_1_decltype2();

// *** type
// RTTI（Run-Time Type Identification)-运行时类型识别
// 在C++中，为了支持RTTI提供了两个操作符：dynamic_cast和typeid
// dynamic_cast允许运行时刻进行类型转换，从而使程序能够在一个类层次结构中安全地转化类型，
//   与之相对应的还有一个非安全的转换操作符static_cast。
// typeid是C++的关键字之一，等同于sizeof这类的操作符。
//   typeid操作符的返回结果是名为type_info的标准库类型的对象的引用
//   （在头文件typeinfo中定义，稍后我们看一下vs和gcc库里面的源码），它的表达式有下图两种形式。
void test1_cpp11_1_type();


// *** 流同步
// 同步C和C++ 流的输入输出 默认同步 也就是C++流不缓存 每个c++流的操作 作用到相应的c流缓存中
// 标准C++流: std::cin, std::cout, std::cerr, std::clog, std::wcin, std::wcout, std::wcerr and std::wclog.
// 标准C流  : stdin, stdout and stderr.
// For a standard stream str, synchronized with the C stream f, the following pairs of functions have identical effect:
// 1) std::fputc(f, c) and str.rdbuf()->sputc(c)
// 2) std::fgetc(f) and str.rdbuf()->sbumpc()
// 3) std::ungetc(c, f) and str.rdbuf()->sputbackc(c)
// https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
void test1_cpp11_1_sync_with_stdio();


// *** 类
// C++标准允许一种（编译器）实现省略创建一个只是为了初始化另一个同类型对象的临时对象。
//   指定这个参数（-fno-elide-constructors）将关闭这种优化，强制G++在所有情况下调用拷贝构造函数
// ! gcc使用=std=c++14 c++11 及以前的 此编译选项起作用 c++17 及以后的 c++2a 不起作用
// g++ demo.cpp -fno-elide-constructors
void test1_cpp11_1_demo();
void test1_cpp11_1_demo2();

// C++11 标准引入了一个新特性，类默认函数的控制："=default" 和 "=delete"，编译器为显式声明"=default"的函数自动生成函数体。
// 类有四类特殊成员函数，分别是：默认构造函数、析构函数、拷贝构造函数以及拷贝赋值运算符。
// 类的特殊成员函数负责创建、初始化、销毁，或者拷贝类的对象。
// 若没为一个类显式定义某个特殊成员函数，而又需要用到该特殊成员函数时，则编译器会隐式的为该类生成一个默认的特殊成员函数。
void test1_cpp11_1_default_delete(); //默认成员函数控制
void test1_cpp11_1_override_final(); //虚函数覆盖  虚函数不能在子类中被覆盖，或某个类不能被子类继承
void test1_cpp11_1_cls_tmp();        // 模板类中的模板函数


// *** 完美转发
#include <type_traits>    // remove_reference
void test1_cpp11_1_perfect();


// #include <algorithm>
// #include <type_traits>
#include <functional>
// *** ref
void test1_cpp11_1_ref();


// *** bind placeholders
void test1_cpp11_1_bind();
void test1_cpp11_1_placeholders();




#endif