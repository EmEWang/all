#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>

#include<algorithm>                 // 算法
#include <functional>               // 仿函数
#include <numeric>                  // 
#include <memory>                  // 

using namespace std;

void map1();

void insertIterator();    // 1)for (auto val in col) 中 val是值而非it 2)使用赋值 必须使用*it(引用类型) 不能使用 it
void insertIteratorOut(); // 1)cout 不能直接输出 it 可以输出 *it
void insertFunc1(); // 1)仿函数
void testmap();    //若map中没有对应的key 返回空 若value为指针 为NULL
void testlist();
void testlist2();
void testlist3();   // 删除指针类型 看是否调用析构
void testlist4();   //指定比较方法
void OstreamInterator();
void testtransform();

void testlamda();

void testfor_each();
void testcount();
void testminmax();
void testfindsearch();
void testSection();
void testModify();
void testNumber();

void testshareptr();
void testuniqueptr();
void testweakptr();


// 时间
#include <chrono>
void testtime1();
void testtime2();
void testtime3();
void testtime4();
void testtime5();  //std::put_time()函


// 线程
#include <thread>
void testthread1();
#include <mutex>
void testthread2();
void testthread3();
void testthread4();


// 正则
#include <regex>
void testregex1();
void testregex2();
void testregex3();
void testregex4();

//hash_map
#define 	_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <unordered_map>
void testhashmap();


// float
#include <cfloat>
void testfloat1();

