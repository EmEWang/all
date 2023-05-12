#ifndef __MODULE3_UTILITY_H__
#define __MODULE3_UTILITY_H__

#include <stdio.h>

#include <iostream>

// 终端颜色显示字符串
inline void printcolor()
{
    std::cout << "000000\n";
    std::cout << "\033[31m" << "111111\n"
        << "111111\n"
        << "\033[32m" << "222222\n"
        << "\033[33m" << "333333\n"
        << "\033[0m";
}

// 通过宏实现enum变量 可打印字符串和数字
#define DOGS { C(RUSSELL), C(TERRIER), C(GREYHOUND) }  //定义一个宏
#undef C
#define C(a) ENUM_##a                                  //设置C为字符串拼接 ENUM_XXX
enum dog_enums DOGS;                                   //enum 扩展为 ENUM_RUSSELL 等
#undef C
#define C(a) #a      //或者 #define C(a) "ENUM_"#a     //设置C为取字符串
static char *dog_strings[] = DOGS;                     //dog_strings中的设置为RUSSELL等
inline char *dog_to_string(enum dog_enums dog)         //根据enum打印其字符串
{
    return dog_strings[dog];
}

inline void printenum()
{
    enum dog_enums dog =ENUM_TERRIER;
    printf("%s %d\n", dog_to_string(dog), dog);       // TERRIER 1

}

#endif