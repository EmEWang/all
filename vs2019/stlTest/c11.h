#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>

using namespace std;


class ClassA
{
public:
	ClassA(int a) : _a(a)
	{}
	// 显式缺省构造函数，由编译器生成
	ClassA() = default;

	// 在类中声明，在类外定义时让编译器生成默认赋值运算符重载
	ClassA& operator=(const ClassA& a);
private:
	int _a;
};




void listinitialization(); //列表初始化
void listinitialization2(); //列表初始化
void listinitialization3(); //列表初始化

void auto2(); //类型推导

void decltype2(); //类型推导

void for2(); //范围for循环

void override2(); //指定一个虚函数覆盖另一个虚函数
void final2(); //指定某个虚函数不能在子类中被覆盖，或者某个类不能被子类继承

void array2(); //新增加容器—静态数组array、forward_list以及unordered系列
void tuple2(); //tuple pair

void default2(); //默认成员函数控制

void threadpool(); //线程池


