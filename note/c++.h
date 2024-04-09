
vscdoe c++/c
// * xxx           # 高亮
// ! xxx           # 高亮
// ? xxx           # 高亮
// todo xxx        # 高亮

https://cplusplus.com/                              # cplusplus
https://zh.cppreference.com/                        # C++ 参考手册  en.cppreference.com 英文
https://c-cpp.com/cpp                               # C++ 参考手册  c-cpp.com/cpp/11  C++11
https://www.isocpp.org/                             # ISO
https://isocpp.github.io/CppCoreGuidelines/         # C++的编程指南 C++之父和C++标准委员会主席Herb Sutter
https://www.stroustrup.com/index.html               # c++之父
https://www.open-std.org/jtc1/sc22/wg21/docs/papers # C++提案
https://www.learncpp.com/                           #
https://www.apiref.com/cpp-zh/cpp.html              # C++ 参考手册

c++ 开源工具库汇总
https://github.com/fffaraz/awesome-cpp              #
https://gitcode.com/fffaraz/awesome-cpp/overview
https://en.cppreference.com/w/cpp/links/libs        # A list of open-source C++ libraries

在线编译器
https://godbolt.org/                                # compiler explorer
https://www.build-bench.com/                        # C++ Build Benchmarks
https://quick-bench.com/                            # Quick C++ Benchmarks
https://www.onlinegdb.com/                          # 在线编程并运行
https://c.runoob.com/compile/12/                    # C++ 在线工具 菜鸟
https://www.bejson.com/runcode/cpp920/              # C++在线运行(GCC 9.2.0)

book
https://cntransgroup.github.io/EffectiveModernCppChinese/Introduction.html # Effective Modern C++
https://github.com/CnTransGroup/EffectiveModernCppChinese                  # Effective Modern C++

gits
https://github.com/Light-City/CPlusPlusThings

article
https://zhuanlan.zhihu.com/p/534116157              # 预编译指令用法汇总
https://zhuanlan.zhihu.com/p/638191470              # 一文讲透C++设计模式
https://zhuanlan.zhihu.com/p/664310551              # C++中的线程：完整指南
https://zhuanlan.zhihu.com/p/664752662              # 深入探索C++20的重要特性：从模块化到协程
https://zhuanlan.zhihu.com/p/665799350              # [读书笔记] 现代C++白皮书
https://zhuanlan.zhihu.com/p/672410503              # 现代C++模板编程：从C++11到C++20的进阶之旅
https://www.zhihu.com/question/536739862            # C/C++中如何稳定地每隔5ms执行某个函数
https://zhuanlan.zhihu.com/p/663843832              # 现代C++性能优化
https://cloud.tencent.com/developer/article/1599283 # 虚函数表深入探索(详细全面)
https://arangodb.com/2021/02/cpp-memory-model-migrating-from-x86-to-arm/  # C++ Memory Model: Migrating from X86 to ARM
https://blog.csdn.net/qq_41854911/article/details/119657617 # C++11、C++14、C++17、C++20新特性总结
https://zhuanlan.zhihu.com/p/142175297              # how? std::function in C++


<bits/stdc++.h>  # 包含通用c/c++头文件  不是标准  gcc 支持 msvc不支持


https://zh.cppreference.com/w/cpp/standard_library  # C++ 标准库头文件
输入/输出和文件操作
<iostream>               标准输入输出流
<fstream>                文件输入输出流
<sstream>                字符串流
<iomanip>                输入输出流的格式化操作
数据结构
<vector>                 动态数组
<list>                   双向链表
<deque>                  双端队列
<map>                    有序键值对集合
<set>                    有序集合
<unordered_map>          无序键值对集合
<unordered_set>          无序集合
<stack>                  栈
<queue>                  队列
<array>                  固定大小数组
功能性
<algorithm>              算法(如排序、搜索)
<functional>             函数对象和绑定操作
<iterator>               迭代器
数学
<cmath>                  数学函数
<numeric>                数值算法
时间
<chrono>                 时间和日期字
符串操作
<string>                 字符串类
<cstring>                C风格字符串操作
错误处理
<stdexcept>              标准异常类
<exception>              异常处理基类
<cassert>                断言
类型支持
<typeinfo>               运行时类型信息
<limits>                 类型属性
<type_traits>            编译时类型信息
内存管理
<memory>                 智能指针和内存工具
<new>                    动态内存分配
本地化
<locale>                 本地化支持
其他
<utility>                通用工具(如std::pair)
<random>                 随机数生成器
<bitset>                 位集合
<regex>                  正则表达式
<thread>                 线程支持
<mutex>                  互斥锁
<condition_variable>     条件变量



__cplusplus      # 表示C++版本的宏 不同的C++编译器需要遵守/支持C++的标准
denotes the version of C++ standard that is being used, expands to value 199711L(until C++11),
201103L(C++11), 201402L(C++14), 201703L(C++17), or 202002L(C++20)(macro constant)  # cppreference
https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html  # gcc
https://learn.microsoft.com/zh-cn/cpp/build/reference/zc-cplusplus?view=msvc-160 # windows  /Zc:__cplusplus(启用更新的 __cplusplus 宏)
g++ -dM -E -x c++  /dev/null | grep -F __cplusplus     # #define __cplusplus 201402L  gcc 输出编译器预定义的宏
-dM # 输出预定义的宏
Instead of the normal output, generate a list of #define directives for all the macros defined
during the execution of the preprocessor,including predefined macros.
This gives you a way of finding out what is predefined in your version of the preprocessor.
If you use -dM without the -E option, -dM is interpreted as a synonym for -fdump-rtl-mach.

-E # 预处理之后停止，预处理的结果输出到标准输出
Stop after the preprocessing stage; do not run the compiler proper.
The output is in the form of preprocessed source code, which is sent to the standard output.
Input files that don’t require preprocessing are ignored.

-x language # 指定语言
Specify explicitly the language


内存泄漏
memcheck valgrind

tcmalloc
react



system("pause") 相当于从程序里调用"pause"命令，继而暂停。必须"stdlib.h" 或 "cstdlib"头文件。
只适合DOS或Windows，不合适合Linux，会出现"sh: PAUSE: command not found" ，在Linux可直接调用pause()。

调用系统命令system()去实现暂停程序，耗费系统资源。C中推荐使用getchar(); C++中使用cin.get();

#include <unistd.h>
int pause(void);
pause()库函数使调用进程(或线程)睡眠状态，直到接收到信号，要么终止，或导致它调用一个信号捕获函数。
The pause() function only returns when a signal was caught and the signal-catching function returned.
  In this case pause() returns -1, and errno is set to EINTR.



c++ sizeof和alignof区别
sizeof    # 获取内存存储的大小。
alignof   # 获取地址对齐的大小，POD里面最大的内存对其的大小。C++11新增，返回一个整数，指出要求的对齐方式。
例子：
struct A{ //non-POD type
    int avg;
    int avg2;
    double c;
    A(int a,int b):avg((a+b)/2){}
};
struct B{
    int avg;
    int avg2;
    char c;
};
int main() {
    std::cout<<"sizeof(A):"<<sizeof(A)<<    std::endl;  // sizeof(A):16
    std::cout<<"alignof(A):"<< alignof(A)<< std::endl;  // alignof(A):8
    std::cout<<"sizeof(B):"<<sizeof(B)<<    std::endl;  // sizeof(B):12
    std::cout<<"alignof(B):"<< alignof(B)<< std::endl;  // alignof(B):4
    std::cout << "alignof std::max_align_t:" << alignof(std::max_align_t) << '\n';  // 16
    double *ptr = (double*) malloc(sizeof(double) * 3 );
    std::cout << "alignof double:" << alignof(*ptr) << '\n';                        // 8
    char *ptr2 = (char*) malloc(1);
    std::cout << "alignof char*: " << alignof(*ptr2) << '\n';                       // 1
    void *ptr3;
    std::cout << "sizeof void*:" << sizeof(ptr3) << " alignof void*:" << alignof(ptr3) << '\n'; // 8 8
}




不允许指针指向不完整的类类型
没有包含对应结构体的头文件        ->   直接添加相对应的头文件
对应的结构体定义写在了C/CPP文件里 ->  将结构体定义写在对应的头文件中

printf("\"软件\""); # \" 代表一个双引号"
printf("'软件'");   # 或 printf("\'软件\'")


goto label;
string str;     //错误 应该放在goto的外面
label:
    xxxx;


%p  # 打印内存地址 若是类的元素 这打印offset  如class A; A a; &a.x(内存) &A::x(offset)
#   # 对宏参数字符串化,即加双引号   #define B(x) #x     则B(m) 表示 "m", B(abcd123) 表示 "abcd123"
#@  # 将宏参数变换为单字符，即加单引号   #define A(x) #@x  此处x仅限于单字符 则A(m) 表示 'm',  而A(abc),则无效
##  # 把宏参数与宏定义代码序列中的标识符连接在一起，形成一个新的标识符   #define C(x)  Class##x   C(List) 表示 ClassList


__asm   # 关键字 用于调用内联汇编程序，并且可在 C 或 C++ 语句合法时出现。   同 __ASM
1 __asm 与大括号一起使用，则该关键字表示大括号之间的每一行都是一条汇编语言语句。如：_
__asm
{
mov  al,  2
mov  dx,  0xD007
out  al,  dx
}
2 __asm 不与大括号一起使用，放在代码行首部，则 __asm 关键字表示此行的其余部分是一条汇编语言语句。如：
__asm mov al, 2
__asm mov dx, 0xD007
__asm out al, dx
3 __asm 做语句分隔符，可将汇编语句放在同一行代码中。如：
__asm mov al, 2 __asm mov dx, 0xD007 __asm out al, dx


不同平台下C\C++数值数据类型长度如下：
类型          win32    win64    linux32    linux64
char          1        1        1          1
short         2        2        2          2
int           4        4        4          4
long          4        4        4          8         *
long long     8        8        8          8
float         4        4        4          4
double        8        8        8          8
void*         4        8        4          8         *
long类型和针类型需要注意，其长度与平台相关。


字符串定义
string str = "abc";
string str2 ="abc\
123\
    ";
string str3 =
    "abc"
    "123";
string str4( // C++11开始支持Raw string literal,格式 R"delimiter(raw_characters)delimiter" delimiter 可省或为任意字符串
    R"EOF(
<Auto>
</Auto>
)EOF");
string str5 =
    R"EOF(
<Auto>
</Auto>
)EOF";



[整数0X01020304]
大端  字节  小端
1234 低←→高 4321
□□□□ ?转化? □□□□
↑↑↑↑________↑↑↑↑
|||__________|||
||____________||
|______________|


1 修饰指针
const char *ptr;        # 指针指向不固定；指向内容不可改变
char const *ptr;        # 同上
char* const ptr;        # 指针指向固定；指向内容可以改变
const char* const ptr;  # 指针指向固定；指向内容不可改变
2 修饰变量
const int a = 2;        # 修饰局部变量，全局变量，成员变量
3 修饰函数
在返回之后要么赋值给了其他的变量所以通常不会这么使用。
const int getNum() {return 3;} // 修饰函数返回值，返回值是一个将亡值，其他变量可修改或离开作用域而释放内存。无意义。
class Student {
public:
    void test() const { // 修饰成员函数，通常在末尾，声明该函数为只读函数，即无法修改成员变量的值
        member = 3;     // 错误，表达式必须是可修改的左值，因为member是成员变量
        int b = 3;
        b = 4;          // 正确
    }
private:
    int member = 2;
};
4 引用限定符
class demo {
public:
    demo(int num):num(num){}
    int get_num(){return num;}          // 默认类中 public 修饰的成员函数，既可被左值对象调用，也可被右值对象调用。
    int get_num2()&{return num;}        // C++11 新增引用限定符。就是在成员函数后面添加 “&” 或者 “&&”，
    int get_num3()&&{return num;}       // 从而限制调用者的类型(左值还是右值)。
    int get_num4()const{return num;};   // const 也可用于修饰类的成员函数，位于函数的末尾，我们习惯称为常成员函数
    int get_num5()const&{return num;};  // C++11 规定，当引用限定符和 const 修饰同一成员函数时，const 必须位于引用限定符前面。
    int get_num6()const&&{return num;}; // const && 修饰类的成员函数时，调用它的对象只能是右值对象；
                                        // const & 调用它的对象既可以是左值对象，也可以是右值对象。
                                        // 无论 const && 还是 const & 限定的成员函数，内部都不允许对当前对象做修改操作。
private:
    int num;
};
demo a(10);
cout << a.get_num() << endl;
cout << move(a).get_num() << endl;
cout << a.get_num2() << endl;            // 正确
//cout << move(a).get_num2() << endl;    // 错误
//cout << a.get_num3() << endl;          // 错误
cout << move(a).get_num3() << endl;      // 正确
cout << a.get_num5() << endl;            // 正确
cout << move(a).get_num5() << endl;      // 正确
//cout << a.get_num6() << endl;          // 错误
cout << move(a).get_num6() << endl;      // 正确


constexpr 关键字
修饰一些函数和变量，使其成为常量表达式，从而在编译器就可以进行计算，进一步提高程序运行期的效率
1 修饰变量
constexpr int n = 2 + 2;          // 正确，2+2是常量表达式，n将会在编译器进行计算
int arr[n] = {11, 22, 33, 44};    // 正确，n是一个常量表达式
2 修饰普通函数
整个函数的函数体中，除了可以包含 using 指令、typedef 语句以及 static_assert 断言外，只能包含一条 return 返回语句。
该函数必须有返回值，即函数的返回值类型不能是 void。
函数在使用之前，必须有对应的定义语句。
return 返回的表达式必须是常量表达式。
不过在后续的C++14/17/20标准中进一步的放宽了这了限制，都可以通过编译了。
constexpr int test() {return 1 + 1;}
3 修饰自定义类型，和成员函数
修饰自定义类型，前提是该自定义类型有constexpr修饰的构造函数。
修饰构造函数的函数体必须为空，且采用初始化列表的方式为各个成员赋值时，必须使用常量表达式，否则会编译报错。
修饰类中的成员函数，此函数必须满足前面普通函数提到的条件。
class Student {
public:
    constexpr Student(const char* name, int age) : name_(name), age_(age) {}
    void print() const { cout << name_ << ' ' << age_ << '\n'; }
private:
    const char* name_;
    int age_;
};
void test() {
    constexpr Student s{"zhangsan", 18};
    s.print();
}
4修饰模板函数
模板函数实例化结果不满足常量表达式函数的要求，则 constexpr 会被自动忽略，即该函数就等同于一个普通函数。
template<typename T>
constexpr T dispaly(T t){
    return t;
}
constexpr int ret1 = dispaly(10);        // 常量表达式函数
struct myType ret = dispaly(struct_val); // 普通函数


C11以前const表示只读和常量双重含义，C11以后将常量的属性划给了constexpr
只读并非不可改， int a = 5; const int& b = a; 可以通过改a 间接改变b
const 可以修饰编译期和运行期的常量，而 constexpr 只能修饰编译期的常量
const 可以通过const_cast类型转换来修改值，而 constexpr 是不可以修改的，其实可以将 const 理解为只读变量更符合其含义
const 只能用于非静态成员函数，而 constexpr 可以和成员，非成员，构造函数一起使用
再有常量表示的场景，尽可能的加上constexpr来让编译期进行计算，但是大面积的constexpr也会面临相应的增加编译时间的风险


C语言声明的优先级规则
1 声明从它的名字开始读取，然后按照优先级顺序依次读取。
2 优先级从高到低依次是：
    2.1 声明中被括号括起来的那部分
    2.2 后缀操作符：括号()表示这是一个函数，方括号[]表示这是一个数组。
    2.3 前缀操作符：星号*表示 “指向…的指针”。
3 若const/volatile后面紧跟类型说明符(如int)，那它作用于类型说明符。在其他情况下，作用于它左边紧邻的指针星号。

char * const *(*next)();  next是一个指针，它指向一个函数，该函数返回另一个指针，该指针指向一个类型为char的常量指针
  1 (*next)      # 是一个指针。
  2 (*next)()    # 是一个函数指针。
  3  *(*next)()  # 是一个返回指针的函数指针。
  4 char * const # 是一个常字符串指针，即一个常量指针，该指针指向一个字符串。
  5 char * const *(*next)()   # 是一个函数指针，该函数形参列表为空返回一个指针，返回的指针类型是一个指向字符串的常量指针。
注 实际测试中  char * const * 好像不对  只需写成  char * const

char *(* c[10])(int **p); c是一个数组[0..9]，它的元素类型是函数指针，其所指向的函数的返回值是一个指向char的指针


理解复杂声明可用的“右左法则”：
从变量名看起，先往右，再往左，碰到一个圆括号就调转阅读的方向；括号内分析完就跳出括号，还是按先右后左的顺序，
如此循环，直到整个声明分析完。
int (*func)(int *p); // 举例
首先找到变量名func，外面有一对圆括号，而且左边是一个*号，这说明func是一个指针；然后跳出这个圆括号，先看右边，又遇到圆括号，
 这说明(*func)是一个函数，所以func是一个指向这类函数的指针，即函数指针，这类函数具有int*类型的形参，返回值类型是int。
int (*func[5])(int *);
func右边是一个[]运算符，说明func是具有5个元素的数组；func的左边有一个*，说明func的元素是指针
 (注意这里的*不是修饰func，而是修饰func[5]的，原因是[]运算符优先级比*高，func先跟[]结合)。
 跳出这个括号，看右边，又遇到圆括号，说明func数组的元素是函数类型的指针，它指向的函数具有int*类型的形参，返回值类型为int。
void * (* (*fp1) (int)) [10];
找到变量名fp1，往右看是圆括号，调转方向往左看到*号，说明fp1是一个指针；跳出内层圆括号，往右看是参数列表，说明fp1是一个函数指针，
 接着往左看是*号，说明指向的函数返回值是指针；再跳出外层圆括号，往右看是[]运算符，说明函数返回的是一个数组指针，往左看是void *，
 说明数组包含的类型是void *。 简言之 ，fp1是一个指向函数的指针，该函数接受一个整型参数并返回一个指向含有10个void指针数组的指针。
float (* (*fp2) (int, int, float)) (int);
找到变量名fp2，往右看是圆括号，调转方向往左看到*号，说明fp2是一个指针；跳出内层圆括号，往右看是参数列表，说明fp2是一个函数指针，
 接着往左看是*号，说明指向的函数返回值是指针；再跳出外层圆括号，往右看还是参数列表，说明返回的指针是一个函数指针，
 该函数有一个int类型的参数，返回值类型是float。简言之，fp2是一个指向函数的指针，该函数接受三个参数(int, int和float)，
 且返回一个指向函数的指针，该函数接受一个整型参数并返回一个float。
typedef double (* (* (*fp3) ()) [10]) ();  使用typedef缩短复杂的定义
 先找到变量名fp3（这里fp3其实是新类型名），往右看是圆括号，调转方向往左是*，说明fp3是一个指针；跳出圆括号，往右看是空参数列表，
 说明fp3是一个函数指针，接着往左是*号，说明该函数的返回值是一个指针；跳出第二层圆括号，往右是[]运算符，
 说明函数的返回值是一个数组指针，接着往左是*号，说明数组中包含的是指针；跳出第三层圆括号，往右是参数列表，
 说明数组中包含的是函数指针，这些函数没有参数，返回值类型是double。简言之，fp3是一个指向函数的指针，该函数无参数，
 且返回一个含有10个指向函数指针的数组的指针，这些函数不接受参数且返回double值。
int (* (*fp4()) [10]) ();   这里fp4不是变量定义，而是一个函数声明。
 找到变量名fp4，往右是一个无参参数列表，说明fp4是一个函数，接着往左是*号，说明函数返回值是一个指针；
 跳出里层圆括号，往右是[]运算符，说明fp4的函数返回值是一个指向数组的指针，往左是*号，说明数组中包含的元素是指针；
 跳出外层圆括号，往右是一个无参参数列表，说明数组中包含的元素是函数指针，这些函数没有参数，返回值的类型是int。
 简言之，fp4是一个返回指针的函数，该指针指向含有10个函数指针的数组，这些函数不接受参数且返回整型值。
也可以记住模式：
  typedef (*var)(...); // 变量名var与*结合，被圆括号括起来，右边是参数列表。表明这是函数指针
  typedef (*var)[];    // 变量名var与*结合，被圆括号括起来，右边是[]运算符。表示这是数组指针
  typedef (*var[])...; // 变量名var先与[]结合，说明这是一个数组(至于数组包含的是什么，由旁边的修饰决定)



外部链接与内部链接
https://learn.microsoft.com/zh-cn/cpp/cpp/program-and-linkage-cpp?view=msvc-170
外部链接  # 程序中的任何翻译单元内可见。其他任何全局对象都不能具有该名称。
内部链接  # 具有内部链接或无链接的符号仅在声明它的翻译单元内可见。

外部链接  # 默认情况下，非常量全局变量和在全局范围或命名空间范围内定义的函数；
  为const对象声明为extern并为其赋值 如extern const int value = 42;
没有链接  # 类定义或函数体中声明的变量
内部链接  # 将全局名称显式声明为static，const对象，constexpr对象，typedef对象，命名空间范围中的 static 对象



关键字 extern
https://learn.microsoft.com/zh-cn/cpp/cpp/extern-cpp?view=msvc-170
1 在非const全局变量声明中，extern指定变量或函数在另一个转换单元中定义。 extern int i; # declaration only 在其他文件中定义
2 在 const 变量声明中，它指定变量具有 external 链接。extern 必须应用于所有文件中的所有声明。默认全局 const 变量具有内部链接。
  extern const int i = 42; # fileA.cpp中  extern const definition
  extern const int i;      # fileB.cpp中  declaration only. same as i in FileA
3 在模板声明中，extern指定模板已在其他位置实例化，告知编译器可以重复使用另一个实例化，而不是在当前位置创建新实例。
template class My<int, 6>;              # 创建 My 的实例化，而不保留对象的任何存储。为所有成员生成代码。
template My<int, 6>::My( void );        # 仅显式实例化构造函数成员函数
extern template class My<int, 6>;       # 使用 extern 关键字来防止自动实例化成员
extern template My<int, 6>::My( void ); # 将特定成员标记为外部且未实例化
使用 extern 关键字阻止编译器在多个对象模块中生成相同的实例化代码。
  如果调用函数，则必须在至少一个链接模块中使用指定的显式模板参数来实例化函数模板。否则，生成程序时将收到链接器错误。
4 extern "C" 指定函数在别处定义并使用 C 语言调用约定。
  extern "C++" 指定函数在别处定义并使用 C++ 语言调用约定。
  extern "C" int printf(const char *fmt, ...);   # Declare printf with C linkage.
  extern "C" {                                   # Declare the two functions ShowChar
    char ShowChar(char ch);
    char GetChar(void);
  }



static
https://www.runoob.com/w3cnote/cpp-static-usage.html
1 静态数据的存储
全局(静态)存储区：分为 DATA 段和 BSS 段。程序运行结束时自动释放。
 DATA 段(全局初始化区)存放初始化的全局变量和静态变量；
 BSS 段(全局未初始化区)存放未初始化的全局变量和静态变量，在程序执行之前会被系统自动清0，
 存储在静态数据区的变量会在程序刚开始运行时就完成初始化，也是唯一的一次初始化。

在 C++ 中 static 的内部实现机制：静态数据成员要在程序一开始运行时就必须存在。
 因为函数在程序运行中被调用，所以静态数据成员不能在任何函数内分配空间和初始化。

这样，它的空间分配有三个可能的地方，一是作为类的外部接口的头文件，那里有类声明；
 二是类定义的内部实现，那里有类的成员函数定义；三是应用程序的 main() 函数前的全局数据声明和定义处。

静态数据成员要实际地分配空间，故不能在类的声明中定义(只能声明数据成员)。
 类声明只声明一个类的"尺寸和规格"，并不进行实际的内存分配，所以在类声明中写成定义是错误的。
 它也不能在头文件中类声明的外部定义，因为那会造成在多个使用该类的源文件中，对其重复定义。

static 被引入以告知编译器，将变量存储在程序的静态存储区而非栈上空间，静态数据成员按定义出现的先后顺序依次初始化，
 注意静态成员嵌套时，要保证所嵌套的成员已经初始化了。消除时的顺序是初始化的反顺序。

2 static的作用
  2.1 修饰变量时，包括全局静态变量和局部静态变量，都会存储在静态变量区，如未初始化则自动初始化为 0。
    修饰局部变量时，为静态局部变量，只执行初始化一次，作用域为局部，延长了生命周期，直到程序运行结束才释放。
      静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化；
    修饰全局变量时，为全局静态变量，只能在本文件中访问，不能在其它文件中访问，即使 extern 外部声明也不可以。
      全局变量是外部链接，作用域是整个工程，通过 extern 声明可使用其他文件定义的全局变量。如未初始化则自动初始化为 0。
  2.2 修饰函数时，这个函数的只能在本文件中调用，不能被其他文件调用。

3 static 与 类
  3.1 静态成员变量
    既可通过对象名引用，也可通过类名引用。类名::变量名  对象名.变量名
    程序开始时分配空间，程序结束后释放，即使不定义对象，也会为静态数据成员分配空间。
    实现多个对象之间的数据共享，它是类的所有对象的共享成员，它在内存中只占一份空间。
    类内为声明，类外必须有定义，可以不初始化；若未初始化，则自动初始化为 0；只能在类外始化。  ***
  3.2 静态成员函数
    和静态数据成员一样，属于类的成员，而不是对象。通过 类名::方法名 引用
    没有 this 指针，而非静态成员函数有。
    用来访问静态数据成员/函数，而不能访问非静态成员变量/函数。
  3.3 总结
    静态资源属于类，但是是独立于类存在的。
    从类的加载机制的角度讲，静态资源是类初始化的时候加载的，而非静态资源是类实例化对象的时候加载的。
    类的初始化早于类实例化对象。所以对于静态资源来说，它是不可能知道一个类中有哪些非静态资源的；
    但是对于非静态资源来说就不一样了，由于它是实例化对象出来之后产生的，因此属于类的这些东西它都能认识。
  3.4 例子
    class Point{
    public:
      void init(){}
      static void output(){}
      int m_x;
      static int m_sx;
    };
    不能通过类名调用类的非静态成员函数/变量    Point::init();    编译失败
    可以通过对象调用(非)静态成员函数/变量      Point pt;  pt.init();   pt.output();   OK
    静态成员函数中不能引用非静态成员           static void output(){printf("%d\n", m_x);}    编译失败
    非静态成员函数可以调用用静态成员           void init(){output();}              OK
    类的静态成员必须先定义再使用，否则会在 linker 时出错。 ***
      static void output(){printf("%d\n", m_sx)}   main中 Point pt;  pt.output();编译成功 运行出错
      因为类的静态成员变量在使用前必须先定义。main()函数前加上 int Point::m_nPointCount = 0; 也可不初始化
  3.5 static 一般情况下来说是不可以修饰类的。
    如果要修饰一个类，说明这个类是一个静态内部类(只能修饰一个内部类)，也就是匿名内部类。



typeof
typeof() 是GUN C提供的一种特性，可参考C-Extensions，它可以取得变量的类型，或者表达式的类型。
1 不用知道函数返回什么类型，可以使用typeof()定义一个用于接收该函数返回值的变量
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct apple{
    int weight;
    int color;
};

struct apple *get_apple_info()
{
    struct apple *a1;
    a1 = malloc(sizeof(struct apple));
    a1->weight = 2;
    a1->color = 1;
    return a1;
}

int main(int argc, char *argv[])
{
    typeof(get_apple_info()) r1; // 定义变量r1,类型是：struct apple *。注意，函数不会执行。
    r1 = get_apple_info();
    printf("apple weight:%d\n", r1->weight);
    printf("apple color:%d\n", r1->color);
    return 0;
}

2 在宏定义中动态获取相关结构体成员的类型
#define max(x, y) ({                \
    typeof(x) _max1 = (x);          \  // 定义一个和变量x相同类型的临时变量_max1
    typeof(y) _max2 = (y);          \  // 定义一个和变量y相同类型的临时变量_max2
    (void) (&_max1 == &_max2);      \  // 判断两者类型是否一致，不一致在编译时就会发出警告。
    _max1 > _max2 ? _max1 : _max2; })  // 最后比较两者

int main(int argc, char *argv[])
{
    int a=3;
    float b = 4.0;
    int r = max(a, b);                 // 传入的a和b不是同一类型 此时编译就会出现警告
    printf("r:%d\n", r);
    return 0;
}

[root@xx c_base]# gcc test.c
test.c: 在函数‘main’中:
test.c:43: 警告：比较不相关的指针时缺少类型转换

3 也可直接取得已知类型
int a = 2;
typeof (int *) p;   // 定义了一个int类型的指针p，像这种用法主没什么太大的意义。
p = &a;
printf("%d\n", *p);

4 其它用法
//其它用法1
char *p1;
typeof (*p1) ch = 'a';              // ch为char类型，不是char *类型。
printf("%d, %c\n", sizeof(ch), ch); // 1, a

//其它用法2
char *p2;
typeof (p2) p = "hello world";     // 此时的p才是char *类型，由于在64位机器上，所以指针大小为8字节
printf("%d, %s\n", sizeof(p), p);  // 8, hello world



typedef
https://www.cnblogs.com/charley_yang/archive/2010/12/15/1907384.html
https://zhuanlan.zhihu.com/p/413574268
1 四种用途
1.1 定义一种类型的别名，而不只是简单的宏替换。可以用作同时声明指针型的多个对象。
  char* pa, pb;    // 它只声明了一个指向字符变量的指针，和一个字符变量；
  char *pa, *pb;   // 2个指针需要这样
  typedef char* PCHAR;   // 一般用大写
  PCHAR pa, pb;          // 可行，同时声明了两个指向字符变量的指针
1.2 在旧的C的代码中声明struct新对象时，必须要带上struct，即形式为： struct 结构名 对象名
  struct tagPOINT1{int x;int y;};               // C结构定义
  struct tagPOINT1 p1;                          // C定义新对象时，必须带上struct
  typedef struct tagPOINT1{int x;int y;}POINT;  // C经常多写一个struct太麻烦，于是就发明了
  POINT p1;                                     // C这样就比原来的方式省事，少写了一个struct
  tagPOINT1 p1; // C++中无需typedef，可直接写：结构名 对象名，但理解它，对掌握旧代码有帮助。
  struct Teacher{int age;}Tea;         // C++中，Tea是一个变量
  struct struct Teacher{int age;}Tea;  // C++中，Tea是一个结构体类型 = struct Student
1.3 定义与平台无关的类型，只要改下 typedef 本身就行，不用对其他源码做任何修改，标准库广泛使用了这个技巧，如size_t。
  定义了一种类型的新别名，不是简单的字符串替换，所以它比宏来得稳健(虽然用宏有时也可以完成以上的用途)。
  typedef long double REAL;  // 定义一个叫 REAL 的浮点类型，在目标平台一上，让它表示最高精度的类型
  typedef double REAL;       // 在不支持 long double 的平台二上
  typedef float REAL;        // 在连 double 都不支持的平台三上
1.4 为复杂的声明定义一个新的简单的别名。
  方法是：在原来的声明里逐步用别名替换一部分复杂声明，如此循环，把带变量名的部分留到最后替换，得到的就是原声明的最简化版。
  int *(*a[5])(int, char*);         // 原声明1
  typedef int *(*pFun)(int, char*); // 变量名为a，直接用一个新别名pFun替换a就可以了
  pFun a[5];                        // 原声明1的最简化版
  void (*b[10]) (void (*)());         // 原声明2
  typedef void (*pFunParam)();        // 变量名为b，先替换右边部分括号里的，pFunParam为别名一
  typedef void (*pFunx)(pFunParam);   // 再替换左边的变量b，pFunx为别名二
  pFunx b[10];                        // 原声明2的最简化版
  doube(*)() (*c)[9];                   // 原声明3
  typedef double(*pFuny)();             // 变量名为c，先替换左边部分，pFuny为别名一
  typedef pFuny (*pFunParamy)[9];       // 再替换右边的变量c，pFunParamy为别名二
  pFunParamy c;                         // 原声明3的最简化版
2 两大陷阱
2.1 记住，typedef是定义了一种类型的新别名，不同于宏，它不是简单的字符串替换。比如：
  typedef char* PSTR;                   // 先定义
  int mystrcmp(const PSTR, const PSTR); // 然后
  const PSTR实际上相当于const char*吗？不是的，它实际上相当于char* const。
  原因在于const给予了整个指针本身以常量性，也就是形成了常量指针char* const。
  简单来说，记住当const和typedef一起出现时，typedef不会是简单的字符串替换就行。
2.2 typedef在语法上是一个存储类的关键字(如auto、extern、mutable、static、register等一样)，虽然它并不真正影响对象的存储特性
  typedef static int INT2; //不可行  编译将失败，会提示“指定了一个以上的存储类”。
3 typedef 与 #define的区别
3.1 通常讲，typedef要比#define要好，特别是在有指针的场合。请看例子：
  typedef char *pStr1;
  #define pStr2 char *;
  pStr1 s1, s2;
  pStr2 s3, s4;
  s1、s2、s3都被定义为char *，而s4则定义成了char，根本原因在于#define只是简单的字符串替换而typedef则是为一个类型起新名字。
3.2 下面的代码中编译器会报一个错误，你知道是哪个语句错了吗？
  typedef char * pStr;
  char string[4] = "abc";
  const char *p1 = string;
  const pStr p2 = string;
  p1++;
  p2++;
  是p2++出错了。这个问题再一次提醒我们：typedef和#define不同，它不是简单的文本替换。const pStr p2并不等于const char * p2。
  const pStr p2和const long x本质上没有区别，都是对变量进行只读限制，只不过p2的数据类型是自己定义的而不是系统固有类型而已。
  因此，const pStr p2的含义是：限定数据类型为char *的变量p2为只读，因此p2++错误。
4 使用 typedef 抑制劣质代码(Using typedef to Curb Miscreant Code)
  Typedef 声明有助于创建平台无关类型，甚至能隐藏复杂和难以理解的语法。
  不管怎样，使用 typedef 能为代码带来意想不到的好处，通过本文你可以学习用 typedef 避免缺欠，从而使代码更健壮。
  typedef 声明，简称 typedef，为现有类型创建一个新的名字。比如人们常常使用 typedef 来编写更美观和可读的代码。
  所谓美观，意指 typedef 能隐藏笨拙的语法构造以及平台相关的数据类型，从而增强可移植性和以及未来的可维护性。
  Q：如何创建平台无关的数据类型，隐藏笨拙且难以理解的语法?
  A： 使用 typedef 为现有类型创建同义字。
4.1 定义易于记忆的类型名
  使用最多的地方是创建易于记忆的类型名，用它来归档程序员的意图。类型出现在所声明的变量名字中，位于 typedef 关键字右边。例如：
  typedef int size; // 此声明定义了一个 int 的同义字，名字为 size。
  注意 typedef 并不创建新的类型。它仅仅为现有类型添加一个同义字。你可以在任何需要 int 的上下文中使用 size
  void measure(size * psz); size array[4];size len = file.getlength();std::vector <size> vs;
  char line[81];char text[81]; // 还可以掩饰符合类型，如指针和数组。例如，你不用象这样重复定义有 81 个字符元素的数组
  typedef char Line[81]; Line text, secondline;getline(text); // ! 定义一个 typedef，每当要用到相同类型和大小的数组时
  typedef char * pstr;int mystrcmp(pstr, pstr);  // 同样，可以象下面这样隐藏指针语法
  这里到达第一个 typedef 陷阱。标准函数 strcmp()有两个 const char * 类型的参数。
  int mystrcmp(const pstr, const pstr); // 这是错误的   它可能会误导人们象下面这样声明
  因为按照顺序，const pstr 被解释为 char * const(一个指向 char 的常量指针)，而不是 const char * (指向常量 char 的指针)。
  typedef const char * cpstr; int mystrcmp(cpstr, cpstr);  // ! 现在是正确的  这个问题很容易解决
  记住：不管什么时候，只要为指针声明 typedef，那么都要在最终的 typedef 名称中加一个 const，以使得该指针本身是常量，而不是对象。
4.2 代码简化
  上面讨论的 typedef 行为有点像 #define 宏，用其实际类型替代同义字。
  不同点是 typedef 在编译时被解释，因此让编译器来应付超越预处理器能力的文本替换。例如：
  typedef int (*PF) (const char *, const char *); // 这个声明引入了 PF 类型作为函数指针的同义字
  PF Register(PF pf); // 使用这种形式函数声明，上述 typedef 是不可或缺的  参数是一个 PF 类型的回调函数，返回某个函数的地址
  int (*Register (int (*pf)(const char *, const char *))) (const char *, const char *); // 如果不用 typedef
  这种代码费解，出错风险高。这里使用 typedef 不是一种特权，而是一种必需。如 signal()函数的头文件 <csinal>，一个有同样接口的函数。
4.3 typedef 和存储类关键字(storage class specifier)
  typedef 就像 auto，extern，mutable，static，和 register 一样，是一个存储类关键字。
  这并是说 typedef 会真正影响对象的存储特性；只是在语句构成上，typedef 声明看起来象 static，extern 等类型的变量声明。
  typedef register int FAST_COUNTER; // 错误 编译通不过。第二个陷阱
  不能在声明中有多个存储类关键字。因为符号 typedef 已经占据了存储类关键字的位置，在 typedef 声明中不能用存储类关键字。
4.4 促进跨平台开发
  有另外一个重要的用途，那就是定义机器无关的类型，例如，1.3中使用的例子
  不用对源代码做任何修改，便可以在每一种平台上编译这个使用 REAL 类型的应用程序。唯一要改的是 typedef 本身。
  在大多数情况下，甚至这个微小的变动完全都可以通过奇妙的条件编译来自动实现。
  标准库广泛地使用 typedef 来创建这样的平台无关类型：size_t，ptrdiff 和 fpos_t 就是其中的例子。
  此外，std::string 和 std::ofstream 这样的 typedef 还隐藏了长长的，难以理解的模板特化语法，
  例如：basic_string<char, char_traits<char>，allocator<char>> 和 basic_ofstream<char, char_traits<char>>。



字节对齐
https://cloud.tencent.com/developer/article/1631792

1 什么是字节对齐
计算机中内存大小的基本单位是字节(byte)，理论上来讲，可以从任意地址访问某种基本数据类型，
但是实际上，计算机并非逐字节大小读写内存，而是以2,4,8的倍数的字节块来读写内存，
如此一来就会对基本数据类型的合法地址作出一些限制，即它的地址必须是2，4或8的倍数。
那么就要求各种数据类型按照一定的规则在空间上排列，这就是对齐。

2 对齐准则
  2.1 结构体变量的首地址能够被其最宽基本类型成员大小与对齐基数中的较小者所整除。
  2.2 结构体每个成员相对结构体首地址的偏移都是该成员大小与对齐基数中的较小者的整数倍，如不满足，对前一个成员填充字节以满足。
  2.3 结构体的总大小为结构体最宽基本类型成员大小与对齐基数中的较小者的整数倍，如不满足，最后填充字节以满足。

3 举例
struct test
{
    int   a;
    char  b;
    int   c;
    short d;
};

未对齐时:
0~3  4  5~9  10~11
a    b  c    d

对齐时:
0~3  4  5~7   8~11  12~13  14~15
a    b  填充  c     d       填充

4 自定义对齐字节
  4.1 32位与64位默认对齐数不一样 ，分别是4字节和8字节对齐
  4.1 伪指令#pragma pack(n)(n为字节对齐数)来使得结构间一字节对齐
#pragma pack(1) /*1字节对齐*/
struct test
{
  ...
};
#pragma pack()/*还原默认对齐*/

  4.2 __attribute__((aligned (n)))，作用的结构成员对齐在n字节自然边界上。若结构中有成员的长度>n，则按照最大成员的长度来对齐。
    __attribute__ ((packed))，取消结构在编译过程中的优化对齐，也可以认为是1字节对齐。
      packed 与aligned (1) 不同；packed则直接取消优化对齐，按照结构中实际使用内存，紧凑连续排列;
      aligned (1)按照1字节对齐，若结构中有成员长度>1，则按照最大成员的长度来对齐，也就是1没用了。
struct test
{
  ...
}__attribute__ ((packed));



RTTI(Run-Time Type Identification)-运行时类型识别
允许“用指向基类的指针或引用来操作对象”的程序能够获取到“这些指针或引用所指对象”的实际派生类型。

1 为了支持RTTI提供了两个操作符：dynamic_cast和typeid
  1.1 dynamic_cast允许运行时刻进行类型转换，在一个类层次结构中安全地转化类型，与之相对应有一个非安全的转换操作符static_cast。
  1.2 typeid是C++的关键字之一，等同于sizeof这类的操作符。typeid操作符的返回结果是名为type_info的标准库类型的对象的引用。

2 typeid
  2.1 typeid是操作符，不是函数，这点与sizeof类似。
  2.2 运行时获知变量类型名称，typeid(变量/类型).name()，其返回的字符串格式由编译器实现，一般不会跟类型名一样。
  2.3 如果表达式的类型是类类型且至少包含有一个虚函数，则typeid操作符返回表达式的动态类型，需要在运行时计算；
    否则，typeid操作符返回表达式的静态类型，在编译时就可以计算。
例如
class base{public :void m(){}};                         class base{public :virtual void m(){}};
class derived : public base{public:void m(){}};         class derived : public base{public:void m(){}};

typeid(p)  == typeid(base*)      true                    true
typeid(p)  == typeid(derived*)   false                   false
typeid(*p) == typeid(base)       true                    false               <--
typeid(*p) == typeid(derived)    false                   true                <--
对于表达式typeid(p)，因为p是base*类型的指针，因此typeid(p) == typeid(base*)为真，而typeid(p) == typeid(derived*)为假。
而对于表达式typeid(*p)，由于左边的基类不具有多态性，因而*p将会采用编译期类型来计算，编译期*p是base对象，
而对于表达式typeid(*p)，因为右边的base类具有多态性，因而在计算typeid(*p)时会根据运行时p所指向的实际类型去计算

3 type_info类
  标准规定四种操作
  3.1 t1 == t2         返回bool            如果两个对象t1和t2类型相同，则返回true；否则返回false
  3.2 t1 != t2         返回bool            如果两个对象t1和t2类型不同，则返回true；否则返回false
  3.3 t.name()         返回C-style字符串    类型名字具体由编译器实现 标准只要求实现为每个类型返回唯一的字符串
  3.4 t1.before(t2)    返回bool            比较t1.name() < t2.name()

源码在 typeinfo 文件中
type_info类提供了public虚析构函数，以使用户能够用其作为基类。
它的默认构造函数和拷贝构造函数及赋值操作符都定义为private，不能定义或复制type_info类型的对象。
创建type_info对象的唯一方法是使用typeid操作符。

4 bad_typeid异常处理
  class bad_typeid : public exception
  {
  public:
    bad_typeid () throw() { }
    virtual ~bad_typeid() throw();
    virtual const char* what() const throw();
  };// namespace std




C++中如何高效地遍历结构体成员
https://www.zhihu.com/question/598203489/answer/3004689760

问题应该是想问C++中如何高效地遍历一个未知的结构体成员？方法是有的，可以使用反射机制来遍历一个未知的结构体成员。
使用反射机制，可以通过名称或索引来访问结构体的成员，并获取成员的类型、值及其他属性。
这样就可以在不知道结构体具体成员的情况下进行高效的遍历和操作。

C++中没有内置的反射机制，但可以使用第三方库来实现，比如Boost.Reflection和RTTR(Run Time Type Reflection)。

使用Boost.Reflection库遍历结构体成员的示例代码：

#include <boost/reflection.hpp>

struct MyStruct {
  int x;
  float y;
  std::string z;
};

int main() {
  MyStruct s = {1, 2.0f, "hello"};
  auto type = boost::reflection::get_type<MyStruct>();   // 获取结构体类型
  for (auto& member : type.get_members()) {              // 遍历结构体成员
    std::cout << member.get_name() << ": ";              // 获取成员名称
    auto value = member.get_value(s);                    // 获取成员值
    if (value.type().is_integral()) {                    // 打印成员值
      std::cout << value.cast<int>() << std::endl;
    } else if (value.type().is_floating_point()) {
      std::cout << value.cast<float>() << std::endl;
    } else if (value.type().is_class()) {
      std::cout << value.cast<std::string>() << std::endl;
    }
  }

  return 0;
}
输出：
x: 1
y: 2
z: hello

Boost.Reflection库在新版本中更改为Boost.pfr，所以使用新版本的Boost使用的反射机制是pfr。使用遍历结构体成员的示例代码：

#include <iostream>
#include <boost/pfr.hpp>
struct my_struct { // no ostream operator defined!
    int i;
    char c;
    double d;
};

int main() {
    my_struct s{100, 'H', 3.141593};
    std::cout << "my_struct has " << boost::pfr::tuple_size<my_struct>::value
        << " fields: " << boost::pfr::io(s) << "\n";
}
输出：
$ ./test
my_struct has 3 fields: {100, H, 3.14159}


使用反射机制可以方便地遍历结构体成员，但需要注意的是，反射机制可能会带来一定的性能开销。
因此，在对性能要求较高的情况下，需要评估反射机制的性能并进行优化。


Boost.Reflection简介
Boost.Reflection是一个用于C++的开源库，它提供了一种运行时反射机制。
这个库可以让程序在运行时动态地查询、访问类和对象的结构信息，如类的成员函数、属性、父类等。
通过这些功能，Boost.Reflection可以帮助开发者编写更加灵活、可扩展的代码。

Boost.Reflection的主要特点包括：
支持多种类型的反射：包括类、成员函数、变量、构造函数等等。
高性能：采用模板和元编程技术，实现了高效的反射机制。
易于使用：提供简单易用的API，并且与C++标准库兼容。
可移植：支持不同平台和编译器。

使用Boost.Reflection，开发者可以方便地实现一些常见的功能，例如：
动态创建类实例
动态调用类的成员函数和属性
检查类的类型信息
序列化和反序列化对象
Boost.Reflection是一个非常有用的C++库，它可以提供强大的反射功能，使得程序在运行时更加灵活和可扩展。
如果需要处理一些复杂的数据结构或者需要运行时动态加载一些组件，那么Boost.Reflection可能会是一个不错的选择。



RTTR(Run Time Type Reflection)
是一个C++库，用于在运行时提供类型反射和动态对象操作。它允许开发人员以简单、快速和安全的方式查询、修改和创建类的成员属性和函数。

RTTR提供以下主要特性：
类型反射：RTTR允许查询和操作任意已注册的C++类型的信息，例如类名、基类、成员函数、成员变量等等。
基于名称的访问：可以使用字符串名称来访问类的成员，而不需要硬编码名称。
动态对象创建和修改：RTTR允许在运行时实例化C++类，并在运行时修改其属性和方法。
安全操作：RTTR通过类型检查和异常处理来确保操作的安全性和稳定性。
使用RTTR，开发人员可以在运行时执行各种类型的任务，包括自动绑定、序列化和反序列化、数据驱动等。
此外，RTTR还提供了与其他库和框架的集成支持，例如Qt、Boost、STL等。

使用示例：

#include <iostream>
#include <string>
#include <rttr/type>
#include <rttr/registration>

using namespace std;
using namespace rttr;

class Person {
public:
    Person(const string& n, int a):name(n), age(a){}
    void sayHello() const {
        cout << "Hello, my name is " << name << ", I am " << age << " years old." << endl;
    }
private:
    string name;
    int age;
};

RTTR_REGISTRATION
{
    registration::class_<Person>("Person")
        .constructor<string, int>()
        .method("sayHello", &Person::sayHello);
}

int main() {
    type t = type::get_by_name("Person");              // 反射获取类信息
    if (t.is_valid()) {
        cout << "Class name: " << t.get_name().to_string() << endl;
        cout << "Number of methods: " << t.get_method_count() << endl;
        variant var_person = t.create("Tom", 22);      // 通过构造函数创建对象
        if (var_person.is_valid()) {
            var_person.invoke("sayHello");             // 调用成员函数
        }
    }
    else {
        cout << "Invalid class" << endl;
    }
    return 0;
}
示例定义了一个Person类，并使用RTTR对其进行了注册，在主函数中通过RTTR对该类进行了反射操作，
获取了类名、方法数和成员变量等信息，并通过构造函数创建了类的实例并调用了其成员函数。

请问boost里面有reflection没？
有的，编译安装后默认将相关的库安装，现在最新版本的头文件是#include <boost/pfr.hpp>，使用方式有些变化。




