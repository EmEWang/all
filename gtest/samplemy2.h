
#pragma once

#ifndef ___SRC__H
#define ___SRC__H
#include <stdio.h>

// bool Odd(int a);
// 头文件中定义函数要加上inline 否则会提示重复定义
// 两个源文件(.cpp)都包含了head.h的头文件时，条件编译不会起到作用。
// 这也就意味着如果头文件中定义了类外的函数或者全局变量，那么当多个源文件同时包含这一头文件时，会发生重复定义的错误。
inline bool Odd(int a) {
    if (a % 2 == 1)
    {
        return true;
    }

    return false;
}
int Add(int a, int b);
// 返回str1 str2
char* strJoin(const char* str1, const char* str2);
float Addfloat(float a, float b);

class Calc {
public:
    int add(int a, int b);
};

#endif
