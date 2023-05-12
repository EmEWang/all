#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
// #include <cstddef>
// #include <utility>

#include "module1.h"
#include "module1_2.h"
#include "module1_3.h"
#include "module1_4.h"
#include "module1_5.h"
#include "module2.h"

#include "utility1.h"
#include "stltemplate.h"
#include "stlclass.h"

demo getdemo(){return demo();}
void testaddr();
void test1();
void teststruct();
void testdemo();
void testreference();
void testperfect();
void testtemplate();
void testvari();
void testcpp17();
void testbacktrace();


using namespace std;
int main()
{
    // test1();
    // teststruct();
    // testdemo();
    // testtype();
    // testreference();
    // testperfect();
    // testtemplate();
    // testweeak();
    // testvari();
    // testcpp17();
    // testbacktrace();
    // printcolor();

    // sync_with_stdiotest();
    // printenum();
    // bindtest();
    // placeholderstest();
    // reftest();
    // enable_iftest();

    // mytestclsX();
    // binarytest();
    // binarytest2();


    return 0;
}
void testaddr()
{
    int i = 12;
    int *pi = &i;
    std::cout << reinterpret_cast<size_t>(pi) << std::endl;  //将指针解释为size_t类型
    //    4字节16进制 8字节16进制  16进制地址 int型  长整型
    printf("%x       %llx         %p        %d     %lld \n", pi, pi, pi, pi, pi);
}

void test1()
{
    int a = 10;
    int b = 3;
    printf("add:%d sub:%d\n", add(a,b), sub(a,b));
}

void teststruct()
{
    struct stdataA dataa;
    struct stdataB datab;
    printf("stdata:%lu\n", sizeof(dataa));
    printf("stdata:%lu\n", sizeof(datab));
}

void testdemo()
{
    demo da = 1;
    demo de = getdemo();

    // 去掉优化后 实际输出 未定义移动构造函数之前
    // demo construct            <-- 执行 demo()
    // demo copy construct       <-- 执行 return demo()
    // demo destruct             <-- 销毁 demo() 产生的匿名对象
    // demo copy construct       <-- 执行 de = getdemo()
    // demo destruct             <-- 销毁 getdemo() 返回的临时对象
    // demo destruct             <-- 销毁 de


    // 去掉优化后 实际输出 定义移动构造函数之后
    // 当类中同时包含拷贝构造函数和移动构造函数时，如果使用临时对象初始化当前类的对象，编译器会优先调用移动构造函数来完成此操作。
    //   只有当类中没有合适的移动构造函数时，编译器才会退而求其次，调用拷贝构造函数。
    // 在实际开发中，通常在类中自定义移动构造函数的同时，会再为其自定义一个适当的拷贝构造函数，
    //   由此当用户利用右值初始化类对象时，会调用移动构造函数；使用左值（非右值）初始化类对象时，会调用拷贝构造函数。
    // demo construct
    // demo move construct
    // demo destruct
    // demo move construct
    // demo destruct
    // demo destruct

    std::cout << "----"<< std::endl;
    demo de3 = de;              // 拷贝构造函数
    demo de4 = std::move(de);   // 移动构造函数

}

void testreference()
{
    {
    string str = "abc";
    string str2 = "123";

    vector<string> vct;
    vct.push_back(str);
    vct.push_back(move(str2));
    vct.emplace_back("sss");     // 不需要拷贝或者移动 直接在末尾构造

    // str:abc str2:
    // 使用move传递左值时，还需要注意一点就是：td::move()可以应用于左值，但是用后就表示当前的值不再需要了，
    // 如果后续使用了该值，则会产生意想不到的结果。
    cout << "str:" << str << " str2:" << str2 << endl;
    }
    {
    // demo construct
    // 拷贝
    // demo copy construct
    // 移动
    // demo move construct
    // demo copy construct
    // demo destruct
    // emplace_back
    // demo construct
    // demo copy construct
    // demo copy construct
    // demo destruct
    // demo destruct
    // demo destruct
    // demo destruct
    // demo destruct
    // demo destruct
    // 解析 看以上情况
    // push_back(move(de)) 先移动 再拷贝
    // emplace_back() 先构造 再拷贝

    demo de;
    vector<demo> vct;
    printf("拷贝\n");
    vct.push_back(de);
    printf("移动\n");
    vct.push_back(move(de));
    printf("emplace_back\n");
    vct.emplace_back();
    }
}

void testperfect()
{
    {
    printf("万能引用\n");
    int n1 = int();
    int n = 5;
    int m = 6;
    int &rn = n;
    int &&rrn = 10;
    string str = "qwe";
    cout << "rn ";func_perfect(rn);
    cout << "m ";func_perfect(m);
    cout << "9 ";func_perfect(9);
    cout << "rrn ";func_perfect(rrn);
    cout << "str ";func_perfect(str);
    printf("n:%d m:%d rn:%d rrn:%d str:%s\n", n, m, rn, rrn, str.c_str());
    }

    {
    printf("万能引用 + 完美转发\n");
    int n1 = int();
    int n = 5;
    int m = 6;
    int &rn = n;
    int &&rrn = 10;
    string str = "qwe";
    cout << "rn ";func_perfect2(rn);
    cout << "m ";func_perfect2(m);
    cout << "9 ";func_perfect2(9);
    cout << "rrn ";func_perfect2(rrn);
    cout << "str ";func_perfect2(str);
    printf("n:%d m:%d rn:%d rrn:%d str:%s\n", n, m, rn, rrn, str.c_str());
    }

    int *pi = nullptr;


    int n =11;
    printf("%s\n", std::is_lvalue_reference<int&>::value?"lvalue_reference":"rvalue_reference");
}

void testtemplate()
{
    const char *left = "gatieme";
    const char *right = "jeancheng";
    compare(left, right);

    compare2(11, 12);
    compare2(left, 12);
    compare2(left, right);


    // int
    int i1 = 10;
    int i2 = 10;
    bool r1 = Compare<int>::IsEqual(i1, i2);
    printf("Compare<int>::IsEqual i1:%d i2:%d r1:%d\n", i1, i2, (int)r1);

    // float
    float f1 = 10;
    float f2 = 10;
    bool r2 = Compare<float>::IsEqual(f1, f2);
    printf("Compare<float>::IsEqual f1:%f f2:%f r2:%d\n", f1, f2, (int)r2);

    // double
    double d1 = 10;
    double d2 = 10;
    bool r3 = Compare<double>::IsEqual(d1, d2);
    printf("Compare<double>::IsEqual d1:%f d2:%f r3:%d\n", d1, d2, (int)r3);

    // pointer
    int* p1 = &i1;
    int* p2 = &i2;
    bool r4 = Compare<int*>::IsEqual(p1, p2);
    printf("Compare<int*>::IsEqual p1:%p p2:%p r4:%d\n", p1, p2, (int)r4);

    // vector<T>
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    bool r5 = Compare<vector<int> >::IsEqual(v1, v2);
    printf("Compare<vector<int> >::IsEqual v1:%lu v2:%lu r5:%d\n", v1.size(), v2.size(), (int)r5);

    // custom template class
    SpecializedType<float> s1 = {10.1f,10.2f};
    SpecializedType<float> s2 = {10.3f,10.0f};
    bool r6 = Compare<SpecializedType<float> >::IsEqual(s1, s2);
    printf("Compare<SpecializedType<float> >::IsEqual s1:%f s2:%f r6:%d\n", s1.x1+s1.x2, s2.x1+s2.x2, (int)r6);
}

void testvari()
{
    vari_int(3,1,2,3);
    vari_print("%d--%s--%x\n",123, "abc", 123);
    vari_fun(123,"abc", 'x', 12.34);
    vari_fun2(123,"abc", 'x', 12.34);
    vari_class<int,string,float> vc(1,"abc", 2.3);
    vc.print();
}

// 需要c++17 支持  make CXXFLAGS=-std=c++17
void testcpp17()
{
    // 构造函数模板推导
    pair p(1, 2.2);             // c++17 自动推导
    pair<int,double> p2(1, 2.2); // before c++17

    // 结构化绑定
    // 通过结构化绑定，对于tuple、map等类型，获取相应值会方便很多
    {
        map<int, string> m = {
        {0, "a"},
        {1, "b"},
        };
        for (const auto &[i, s] : m) {
            cout << i << " " << s << endl;
        }

        int array[3] = {1, 2, 3};
        auto [a, b, c] = array;
        cout << a << " " << b << " " << c << endl;
    }

    // 结构化绑定还可以改变对象的值，使用引用即可
    {
        std::pair a(1, 2.3f);
        auto& [i, f] = a;
        i = 2;
        cout << a.first << endl; // 2
    }
    // 注意结构化绑定不能应用于constexpr
    // constexpr auto[x, y] = std::pair(1, 2.3f); // compile error, C++20可以

    // 结构化绑定不止可以绑定pair和tuple，还可以绑定数组和结构体等
    {
    // 注意这里的struct的成员一定要是public的
        struct Point {
            int x;
            int y;
        };
        auto func= []()-> Point
        {
            return {1, 2};
        };
        auto [x, y] = func();
        cout << x << " " << y << " " << endl;
    }

}

void testbacktrace()
{
    // 1
    dummy_function();

    MyFunc_B();

    // 2
    if (signal(SIGSEGV, sighandler_dump_stack) == SIG_ERR)
		perror("can't catch SIGSEGV");
	func_a();
}
