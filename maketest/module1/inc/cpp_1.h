#include <bits/stdc++.h>        // 通用头文件


// 主要用于测试c++ 基本概念


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

// *** 参数传递 所有权语义
void  test1_cpp_1_paramowner();


// 只要是static变量 都会放在静态/全局存储区 不管是局部静态还是全局的 甚至是函数/类内定义的静态变量
// 局部静态变量  静态存储区 局部/函数作用域  只会被初始化一次 未经初始化则自动始化为0 生存周期为整个程序
// 全局静态变量  静态存储区 所定义文件作用域 只会被初始化一次 未经初始化则自动始化为0 生存周期为整个程序
// ! 类定义 static成员变量 一定要在类外 初始化 否则 undefined reference to `g_cls::m_s_i' 错误
void test1_cpp_1_static();
void test1_cpp_1_memory();