#ifndef __MODULE1_CPP11_2_H__
#define __MODULE1_CPP11_2_H__

#include <stdio.h>

#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <list>
#include <map>

#include <algorithm>                // 算法
#include <functional>               // 仿函数
#include <numeric>                  //
#include <memory>                   //
#include <atomic>                   // 原子



// 主要用于测试c++11 基本应用 基本库

// *** 字符串
#include <string>
void test1_cpp11_2_string();  // 包含c串

// *** 线程
#include <thread>
#include <mutex>
void test1_cpp11_2_thread();
void test1_cpp11_2_threadpool(); //线程池

// *** 异步
void test1_cpp11_2_async();
void test1_cpp11_2_future();
void test1_cpp11_2_promise();
void test1_cpp11_2_packaged_task();

// *** 智能指针
#include <memory>
void test1_cpp11_2_memory();
void test1_cpp11_2_shareptr();
void test1_cpp11_2_uniqueptr();
void test1_cpp11_2_weakptr();

// *** 标准时间库
#include <chrono>
void test1_cpp11_2_chrono();
void test1_cpp11_2_chrono_duration();
void test1_cpp11_2_chrono_timepoint();
void test1_cpp11_2_chrono_clock();
void test1_cpp11_2_chrono_cast();
void test1_cpp11_2_chrono_put_time();  //std::put_time()函数

// *** 正则
#include <regex>
void test1_cpp11_2_regex_match();
void test1_cpp11_2_regex_search();
void test1_cpp11_2_regex_replace();
void test1_cpp11_2_regex_other();

// *** 小工具
#include <array>
void test1_cpp11_2_array(); // 新增加容器—静态数组array、forward_list以及unordered系列
void test1_cpp11_2_tuple_pair(); // tuple pair    #include <tuple>


#endif