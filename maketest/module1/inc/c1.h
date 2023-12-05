#ifndef __MODULE1_C1_H__
#define __MODULE1_C1_H__

#include <utility>
#include <map>
#include <iostream>
#include <stdio.h>

using namespace std;

// 主要用于测试c 基本应用


//  类型        比特  有效数字   数值范围
//  float        32  6~7       -3.4*10^38～+3.4*10^38
//  double       64  15~16     -1.7*10^-308~1.7*10^308
//  long double 128  18~19     -1.2*10^-4932~1.2*10^4932


// ##是两个参数按字面值连接成一个参数，#@用来给参数加单引号，#用来给参数加双引号即转成字符串。
//   字符串为空时删除前置“,” (##) 举例如下
#define _T_LOG(_STRING, ...)   printf(__STRING, __VA_ARGS__)// 宏定义
// log_info("cout something");        -> printf("cout something",);  // 宏展开 此处多一个,
// log_info("cout count: %d", count); -> printf("cout count: %d", count); // 宏展开
#define _T_LOG2(_STRING, ...)   printf(__STRING, ##__VA_ARGS__)
// log_info("cout something");        -> printf("cout something");   // 宏展开 正常
// log_info("cout count: %d", count); -> printf("cout count: %d", count);  // 宏展开

#define Conn(x,y)  x##y
// #define ToChar(x)  #@x // !gcc  error: '#' is not followed by a macro parameter
#define ToString(x) #x

#define CON1  if (i > 1) {printf(">1\n");} else {printf("<1\n");}
#define CON2  if (i > 2) {printf(">2\n");} else {printf("<2\n");}
#define CON3  if (i > 3) {printf(">3\n");} else {printf("<3\n");}


// 通过宏实现enum变量 可打印字符串和数字
#define DOGS { C(RUSSELL), C(TERRIER), C(GREYHOUND) }  //定义一个宏
#undef C
#define C(a) ENUM_##a                                  //设置C为字符串拼接 ENUM_XXX
enum dog_enums DOGS;                                   //enum 扩展为 ENUM_RUSSELL 等
#undef C
#define C(a) #a      //或者 #define C(a) "ENUM_"#a     //设置C为取字符串
static const char *dog_strings[] = DOGS;               //dog_strings中的设置为RUSSELL等 没有const 则-Wwrite-strings提示
inline const char *dog_to_string(enum dog_enums dog) { //根据enum打印其字符串
    return dog_strings[dog];
}
enum _t_enum{normal=0, warnning=1, error=2};
inline void test1_c1_enum_macro()
{
    // enum
    enum dog_enums dog =ENUM_TERRIER;
    printf("%s %d\n", dog_to_string(dog), dog);       // TERRIER 1

    _t_enum eu=normal;
    printf("enum:%d \n", eu);


    // macro
    printf("[func:%s--line:%4d] \n", __FUNCTION__, __LINE__);
    printf(":%s] \n", ToString(iii));
    int i = 2;
    CON1
    // char c = ToChar(i);
}



inline void test1_c1_pointer()
{
    // const int i 与 int const i 完全相同  i++ 则报错
    // const int *p = &i1    p 指向的数不能变 (*p)++ 则报错  但是其指向 p = &i2 可变
    // int *p const = &i1    p 指向的数可以变 (*p)++ 则正确  但是其指向 p = &i2 错误
    {
        int a = 10;
        int b = 3;
        const int * p1 = &a;
        p1 = &b;
        // (*p1)++;         // 报错

        int *const p2 = &a;
        // p2 = &b;         // 报错
        (*p2)++;
    }
    {
        int i = 12;
        int *pi = &i;
        std::cout << reinterpret_cast<size_t>(pi) << std::endl;  //将指针解释为size_t类型
        //    4字节16进制 8字节16进制  16进制地址 int型  长整型
        printf("%x       %llx         %p        %d     %lld \n",
        (unsigned)(long long)pi,(unsigned long long)pi, pi, (int)(long long)pi, (long long)pi);
        // 强制转换仅为了 防止 -Wformat= 警告提示     (int)pi 则 -fpermissive 错误提示
    }
    {
        int i = 1;
        void* ptr  = NULL;
        void* ptr2 = &i;
        void* ptr3 = NULL;*(int*)(&ptr3) = 0x12345678;

        // #X表示前面加 0X       #x 表示前面加 0x
        printf("[ptr]%#X[ptr2]%#X[ptr3]%#x\n", *(int*)(&ptr), *(int*)(&ptr2), *(int*)(&ptr3));

        char* pc = new char[5];
        delete pc;
        // delete pc;  // 删除2次 gcc 出错  vs2019 没事
    }

    // Some of the % specifiers that you can use in ANSI C are as follows:
    // SPECIFIER   USED FOR
    // %c          a single character
    // %s          a string
    // %hi         short (signed)
    // %hu         short (unsigned)
    // %Lf         long double
    // %n          prints nothing
    // %d          a decimal integer (assumes base 10)
    // %i          a decimal integer (detects the base automatically)
    // %o          an octal (base 8) integer
    // %x          a hexadecimal (base 16) integer
    // %p          an address (or pointer)
    // %f/F        a floating point number for floats
    // %u          int unsigned decimal
    // %e/E        a floating point number in scientific notation
    // %%          the % symbol
}



// 测试函数指针
inline int func_c1_1(int a){
    return a+1;
}
inline int* func_c1_2(int a){
    int *p = (int*)malloc(sizeof(int));
    *p = a;
    return p;
}
inline int* const func_c1_3(int a){
    int *p = (int*)malloc(sizeof(int));
    *p = a;
    return p;
}
// inline int* const* func_c1_4(int a)
// {
//     int * const* p = (int*)malloc(sizeof(int));
//     //*p = a;
//     return p;
// }
inline void test1_c1_funcpointer()
{
    int * const(*p)(int) = func_c1_3;
    int *pi = p(3);
    int a = 5;
    printf("pi %p *pi %d\n", pi, *pi);
    *pi = 4;
    printf("pi %p *pi %d\n", pi, *pi);
    pi = &a;
}



// scanf 返回读取的参数数量
inline void test1_c1_scanf()
{
    int a = 0;
    int b = 0;
    printf("input two integer\n");
    int i = scanf("%d%d",&a, &b);
    if(i != 2)
        printf("blease input two integer! your input is %d\n", i);
    else
        printf("result %d\n", a + b);
}





// 终端颜色显示字符串
inline void test1_c1_color()
{
    std::cout << "000000\n";
    std::cout << "\033[31m" << "111111\n"
        << "\033[32m" << "222222\n"
        << "\033[33m" << "333333\n"
        << "\033[0m";
}




#endif