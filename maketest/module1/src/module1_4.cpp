#include "module1_4.h"

// RTTI（Run-Time Type Identification)-运行时类型识别
// 在C++中，为了支持RTTI提供了两个操作符：dynamic_cast和typeid
// dynamic_cast允许运行时刻进行类型转换，从而使程序能够在一个类层次结构中安全地转化类型，
//   与之相对应的还有一个非安全的转换操作符static_cast。
// typeid是C++的关键字之一，等同于sizeof这类的操作符。
//   typeid操作符的返回结果是名为type_info的标准库类型的对象的引用
//   （在头文件typeinfo中定义，稍后我们看一下vs和gcc库里面的源码），它的表达式有下图两种形式。

void testtype()
{
    int a = 10;
    int &ra = a;
    int &&rra = 10;
    int *pa = &a;

    void f0();
    int f1(int*,int);
    float* f2(int*,int,int*,float*);
    char* f3(float*,const int*,int*,float*,const int*);

    printf("int:%s 10:%s int&:%s int&&:%s\n",
        typeid(a).name(),typeid(10).name(), typeid(ra).name(),typeid(rra).name());
    printf("int:%s int&:%s int&&:%s\n",
        typeid(int).name(),typeid(int&).name(),typeid(int&&).name());
    printf("int == int&:%d int*:%s\n",
        typeid(a) == typeid(ra), typeid(pa).name());
    printf("f0:%s f1:%s f2:%s f3:%s\n",
        typeid(f0).name(),typeid(f1).name(),typeid(f2).name(),typeid(f3).name());
}

void testweeak()
{
    std::shared_ptr<int> sp1,sp2;
    std::weak_ptr<int> wp;
                                        // sharing group:
                                        // --------------
    sp1 = std::make_shared<int> (20);    // sp1
    wp = sp1;                            // sp1, wp
    std::cout << "num: " << wp.use_count() << '\n';    // 1
    sp2 = sp1;
    std::cout << "num: " << wp.use_count() << '\n';    // 2
    sp1.reset();
    //sp2 = wp.lock();                     // sp1, wp, sp2
    std::cout << "num: " << wp.use_count() << '\n';    // 1
    sp1 = wp.lock();                     // sp1, wp, sp2
    std::cout << "num: " << wp.use_count() << '\n';    // 2
}

void vari_int(int count, ...)
{
    va_list val;
    va_start(val,count);

    for (int i = 0; i < count; i++)
    {
        int t = va_arg(val, int);
        printf("%d ", t);
    }
    va_end(val);
    printf("\n");
}

void vari_print(const char*format, ...)
{
    va_list val;
    va_start(val, format);
    vfprintf(stdout, format, val);
    va_end(val);
}