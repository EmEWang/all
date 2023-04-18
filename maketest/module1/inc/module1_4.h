#ifndef __MODULE1_4_H__
#define __MODULE1_4_H__

#include <stdio.h>

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

// 测似类型
void testtype();

// 智能指针
#include <memory>
void testweeak();

#include <cstdarg>
// 可变参数
void vari_int(int count, ...);
void vari_print(const char*format, ...);

// 模板可变参数
// 方法1 递归调用 结束是参数迭代完 空的参数法结束
inline void vari_fun()
{
    cout << endl;
}
template <typename F, typename... T>
void vari_fun(F f, T... args)
{
    cout << f << " ";
    vari_fun(args...);
}

// 方法2 初始化数组方式 其展开格式如下
//  int arr[] = { (dispaly(1),0), (dispaly("http://www.biancheng.net"),0), (dispaly(2.34),0) };
template <typename T>
void vari_fun2(T t)
{
    cout << t << " ";
}
template <typename... T>
void vari_fun2(T... args)
{
    int arr[] = {(vari_fun2(args), 0)...};
    cout << endl;
}

// 可变参数类模板
template<typename... T> class vari_class;                               // 声明
template<> class vari_class<>{public: void print(){cout << endl;}};     // 继承递归出口 泛化特例
template<typename T, typename... args>
class vari_class<T, args...>:public vari_class<args...>                 // public继承
{
public:
    vari_class(T t, args... arg):m_data(t),vari_class<args...>(arg...)  // 构造
    {}
    void print()                                                        // 显示内容
    {
        cout << m_data << " ";                                          // 显示当前类中的内容
        vari_class<args...>::print();                                   // 显示基类中的内容
    }

private:
    T m_data;
};


#include <cstring>
// 函数模板特化
// 模版
template <class T>
int compare(const T left, const T right)
{
    std::cout <<"in template<class T> compare2..." << std::endl;
    return (left - right);
}
// 特化的函数模版
template <>
inline int compare<const char*>(const char* left, const char* right)  // 需要 inline 否则可能重复定义
{
    std::cout <<"in special template< > compare..." << std::endl;
    return strcmp(left, right);
}

// 特化的函数模版, 两个特化的模版本质相同, 因此编译器会报错
// error: redefinition of 'int compare(T, T) [with T = const char*]'|
//template < >
//int compare(const char* left, const char* right)
//{
//    return strcmp(left, right);
//}

// 这个其实本质是函数重载
inline int compare(char* left, char* right)
{
    std::cout <<"in overload function compare..." <<std::endl;

    return strcmp(left, right);
}


// 函数模板特化2
// 模版
template <class T, class U>
int compare2(const T left, const U right)
{
    std::cout <<"in template <class T, class U> compare2..." << std::endl;
    return (left - right);
}
// 函数模版偏特化 特化部分
template <class U>
int compare2(const char* left, const U right)  // 需要 inline 否则可能重复定义
{
    std::cout <<"in special template<class U> compare2..." << std::endl;
    return 22;
}
// 特化的函数模版
template <>
inline int compare2(const char* left, const char* right)  // 需要 inline 否则可能重复定义
{
    std::cout <<"in special template< > compare2..." << std::endl;
    return strcmp(left, right);
}


// 类模版特化
// 一是特化为绝对类型；
// 二是特化为引用，指针类型；
// 三是特化为另外一个类模板。

// 1 特化为绝对类型  直接为某个特定类型做特化
template<class T>
class Compare
{
public:
    static bool IsEqual(const T& lh, const T& rh)
    {
        std::cout <<"in the general class..." <<std::endl;
        return lh == rh;
    }
};
// specialize for float
template<>
class Compare<float>
{
public:
    static bool IsEqual(const float& lh, const float& rh)
    {
        std::cout <<"in the float special class..." <<std::endl;
        return std::abs(lh - rh) < 10e-3;
    }
};
// specialize for double
template<>
class Compare<double>
{
public:
    static bool IsEqual(const double& lh, const double& rh)
    {
        std::cout <<"in the double special class..." <<std::endl;
        return std::abs(lh - rh) < 10e-6;
    }
};
// 如果期望使用偏特化，那么
// template<class T1, class T2>
// class A
// {}
// template<class T1>
// class A<T1, int>
// {}

// 2 特化为引用，指针类型
// 这种特化其实是就不是一种绝对的特化， 它只是对类型做了某些限定，但仍然保留了其一定的模板性，
//   这种特化给我们提供了极大的方便， 如这里， 我们就不需要对int*, float*, double*等等类型分别做特化了。
// 这其实是第二种方式的扩展，其实也是对类型做了某种限定，而不是绝对化为某个具体类型
// specialize for T*
template<class T>
class Compare<T*>
{
public:
    static bool IsEqual(const T* lh, const T* rh)
    {
        return Compare<T>::IsEqual(*lh, *rh);
    }
};

// 3 这就把IsEqual的参数限定为一种vector类型， 但具体是vector还是vector， 我们可以不关心，
//   因为对于这两种类型，我们的处理方式是一样的，我们可以把这种方式称为“半特化”。
// specialize for vector<T>
template<class T>
class Compare<vector<T> >
{
public:
    static bool IsEqual(const vector<T>& lh, const vector<T>& rh)
    {
        if(lh.size() != rh.size()) return false;
        else
        {
            for(int i = 0; i < lh.size(); ++i)
            {
                if(lh[i] != rh[i]) return false;
            }
        }
        return true;
    }
};
// 可以将其“半特化”为任何我们自定义的模板类类型
// 这就是三种类型的模板特化， 我们可以这么使用这个Compare类
// specialize for any template class type
template <class T1>
struct SpecializedType
{
    T1 x1;
    T1 x2;
};
template <class T>
class Compare<SpecializedType<T> >
{
public:
    static bool IsEqual(const SpecializedType<T>& lh, const SpecializedType<T>& rh)
    {
        return Compare<T>::IsEqual(lh.x1 + lh.x2, rh.x1 + rh.x2);
    }
};

#endif