#ifndef __MODULE1_3_H__
#define __MODULE1_3_H__

#include <stdio.h>
#include <iostream>

// g++ demo.cpp -fno-elide-constructors
// C++标准允许一种（编译器）实现省略创建一个只是为了初始化另一个同类型对象的临时对象。
//   指定这个参数（-fno-elide-constructors）将关闭这种优化，强制G++在所有情况下调用拷贝构造函数
class demo
{
public:
    demo(){printf("demo construct\n");}
    demo(int i){printf("demo construct int\n");}
    demo(const demo&other){printf("demo copy construct\n");}
    demo(demo&&other){printf("demo move construct\n");}
    demo& operator =(const demo&other){printf("demo assignment\n");return *this;}
    ~demo(){printf("demo destruct\n");}
};

// 完美转发
#include <type_traits>    //remove_reference

// 引用折叠规则
// 当实参为左值或者左值引用（A&）时，函数模板中 T&& 将转变为 A&（A& && = A&）；
// 当实参为右值或者右值引用（A&&）时，函数模板中 T&& 将转变为 A&&（A&& && = A&&）

// 在实现完美转发时，只要函数模板的参数类型为 T&&，则 C++ 可以自行准确地判定出实际传入的实参是左值还是右值。
template <typename T>
void func_call(T&& t)
{
    //printf("call t:%d\n", t);
    std::cout << (std::is_lvalue_reference<T>::value?" lvalue_call:":" rvalue_call:")
        << t << " addr:%x" << &t <<std::endl;

    //t = 0;
    t = typename std::remove_reference<T>::type();     // 必须用 typename 指明是个类型
}


// is_reference (C++11) 检查类型是否为左值引用或右值引用 (类模板)
// is_rvalue_reference (C++11) 检查类型是否为右值引用 (类模板)
// is_lvalue_reference (C++11) 检查类型是否为左值引用 (类模板)
// 由此可知 无论左值还是右值 都能接受 其t要么变为左值引用 要么变为右值引用
// 函数中当前变量t为右值引用 其用它在调用其他函数func(t) 此时变为左值 因为当前t 能取其地址
template <typename T>
void func_perfect(T&& t)
{
    std::cout << "call:" << t << " addr:%x " << &t
        << (std::is_lvalue_reference<T>::value?" lvalue_reference":" rvalue_reference");
    func_call(t);
}

// 通过将函数模板的形参类型设置为 T&&，我们可以很好地解决接收左、右值的问题。
//   但除此之外，还需要解决一个问题，即无论传入的形参是左值还是右值，对于函数模板内部来说，形参既有名称又能寻址，
//   因此它都是左值。那么如何才能将函数模板接收到的形参连同其左、右值属性，一起传递给被调用的函数呢？

// C++11 标准的开发者已经帮我们想好的解决方案，该新标准还引入了一个模板函数 forword()，
//   我们只需要调用该函数，就可以很方便地解决此问题。仍以 function 模板函数为例，如下演示了该函数模板的用法：
template <typename T>
void func_call2(T& t)
{
    std::cout << " lvalue_call:" << t << " addr:%x" << &t<< std::endl;
    t = typename std::remove_reference<T>::type();
}
template <typename T>
void func_call2(const T& t)
{
    std::cout << " rvalue_call:" << t << " addr:%x" << &t<< std::endl;
    //t = typename std::remove_reference<T>::type();   // 不能改变
}

template <typename T>
void func_perfect2(T&& t)
{
    std::cout << "call:" << t << " addr:%x" << &t
        << (std::is_lvalue_reference<T>::value?" lvalue_reference":" rvalue_reference");
    func_call2(std::forward<T>(t));
}

#endif