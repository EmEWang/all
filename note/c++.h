
vscdoe c++/c
// * xxx           # 高亮
// ! xxx           # 高亮
// ? xxx           # 高亮
// todo xxx        # 高亮

https://cntransgroup.github.io/EffectiveModernCppChinese/1.DeducingTypes/item1.html # Effective Modern C++
https://godbolt.org/                              # compiler explorer
https://www.onlinegdb.com/                        # 在线编程并运行
https://github.com/CnTransGroup/EffectiveModernCppChinese  # Effective Modern C++ 翻译

https://cloud.tencent.com/developer/article/1599283 # 虚函数表深入探索(详细全面)
https://zhuanlan.zhihu.com/p/534116157              # 预编译指令用法汇总
https://zhuanlan.zhihu.com/p/638191470              # 一文讲透C++设计模式
https://zhuanlan.zhihu.com/p/664310551              # C++中的线程：完整指南
https://zhuanlan.zhihu.com/p/664752662              # 深入探索C++20的重要特性：从模块化到协程
https://zhuanlan.zhihu.com/p/665799350              # [读书笔记] 现代C++白皮书

<bits/stdc++.h>  # 包含通用c/c++头文件  不是标准  gcc 支持 msvc不支持

__cplusplus      # 表示C++版本的宏 不同的C++编译器需要遵守/支持C++的标准
denotes the version of C++ standard that is being used, expands to value 199711L(until C++11),
201103L(C++11), 201402L(C++14), 201703L(C++17), or 202002L(C++20)(macro constant)  # cppreference
https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html  # gcc
https://learn.microsoft.com/zh-cn/cpp/build/reference/zc-cplusplus?view=msvc-160 # windows  /Zc:__cplusplus（启用更新的 __cplusplus 宏）
g++ -dM -E -x c++  /dev/null | grep -F __cplusplus     # #define __cplusplus 201402L  gcc 输出编译器预定义的宏
-dM -E # 输出预定义的宏
Instead of the normal output, generate a list of ‘#define’ directives for all the macros defined
during the execution of the preprocessor,including predefined macros.
This gives you a way of finding out what is predefined in your version of the preprocessor.
If you use ‘-dM’ without the ‘-E’ option, ‘-dM’ is interpreted as a synonym for ‘-fdump-rtl-mach’

-E # 预处理之后停止，预处理的结果输出到标准输出
Stop after the preprocessing stage; do not run the compiler proper.
The output is in the form of preprocessed source code, which is sent to the standard output.
Input files that don’t require preprocessing are ignored

-x language # 指定语言
Specify explicitly the language


内存泄漏
memcheck valgrind

tcmalloc
react



system("pause") 相当于从程序里调用"pause"命令，继而暂停。必须"stdlib.h" 或 "cstdlib"头文件。只适合DOS或Windows
，不合适合Linux，会出现"sh: PAUSE: command not found" ，在Linux可直接调用pause()。

调用系统命令system()去实现暂停程序，耗费系统资源。
C中推荐使用getchar(); C++中使用cin.get();

#include <unistd.h>
int pause(void);
pause() 库函数使调用进程（或线程）睡眠状态，直到接收到信号，要么终止，或导致它调用一个信号捕获函数。
The pause() function only returns when a signal was caught and the signal-catching function returned.
  In this case pause() returns -1, and errno is set to EINTR.



c++ sizeof和alignof区别
sizeof    # 获取内存存储的大小。
alignof   # 获取地址对齐的大小，POD里面最大的内存对其的大小。

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
using namespace std;
int main() {
    cout<<"sizeof(A):"<<sizeof(A)<<endl;
    cout<<"alignof(A):"<< alignof(A)<<endl;

    cout<<"sizeof(B):"<<sizeof(B)<<endl;
    cout<<"alignof(B):"<< alignof(B)<<endl;
}
输出：
sizeof(A):16
alignof(A):8
sizeof(B):12
alignof(B):4




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
语法  __asm后跟一个程序集指令、一组括在大括号中的指令或者至少一对空大括号。
1、__asm与大括号一起使用，则该关键字表示大括号之间的每一行都是一条汇编语言语句。
   如：_asm　{　mov al, 2 　mov dx, 0xD007　out al, dx　}
2、__asm不与大括号一起使用，放在代码行首部，则 __asm 关键字表示此行的其余部分是一条汇编语言语句。
  如：
__asm mov al, 2
__asm mov dx, 0xD007
__asm out al, dx
3、__asm做语句分隔符，可将汇编语句放在同一行代码中。
如：__asm mov al, 2 __asm mov dx, 0xD007 __asm out al, dx


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
string str2 =
    "abc\
123\
    ";
string str3 =
    "abc"
    "123";
string str4(
    R"EOF(
<Auto>
    <Disk mxproptype="1">
        <Disk Name="F1" Label="L1" />
        <Disk Name="F2" Label="L2" />
        <Disk Name="F3" Label="L3" />
  </Disk>
</Auto>
)EOF");
string str5 =
    R"EOF(
<Auto>
    <Disk mxproptype="1">
        <Disk Name="F1" Label="L1" />
        <Disk Name="F2" Label="L2" />
        <Disk Name="F3" Label="L3" />
  </Disk>
</Auto>
)EOF";

C++ 11开始支持Raw string literal,可以写成 R"delimiter(raw_characters)delimiter" 这种形式，比如\
std::string str(
R"EOF(line1
line2
line3
)EOF)"
其中EOF是分界字符，可以是任意组合。


[整数0X01020304]
大端  字节  小端
1234 低←→高 4321
□□□□ ?转化? □□□□
↑↑↑↑________↑↑↑↑
|||__________|||
||____________||
|______________|



const char *ptr;        # 指针指向不固定；指向内容不可改变
char const *ptr;        # 同上
char* const ptr;        # 指针指向固定；指向内容可以改变
const char* const ptr;  # 指针指向固定；指向内容不可改变


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
全局(静态)存储区：分为 DATA 段和 BSS 段。DATA 段(全局初始化区)存放初始化的全局变量和静态变量；
BSS 段(全局未初始化区)存放未初始化的全局变量和静态变量。程序运行结束时自动释放。其中BBS段在程序执行之前会被系统自动清0，
所以未初始化的全局变量和静态变量在程序执行之前已经为0。存储在静态数据区的变量会在程序刚开始运行时就完成初始化，也是唯一的一次初始化。

在 C++ 中 static 的内部实现机制：静态数据成员要在程序一开始运行时就必须存在。
因为函数在程序运行中被调用，所以静态数据成员不能在任何函数内分配空间和初始化。

这样，它的空间分配有三个可能的地方，一是作为类的外部接口的头文件，那里有类声明；二是类定义的内部实现，
那里有类的成员函数定义；三是应用程序的 main() 函数前的全局数据声明和定义处。

静态数据成员要实际地分配空间，故不能在类的声明中定义(只能声明数据成员)。类声明只声明一个类的"尺寸和规格"，
并不进行实际的内存分配，所以在类声明中写成定义是错误的。它也不能在头文件中类声明的外部定义，
因为那会造成在多个使用该类的源文件中，对其重复定义。

static 被引入以告知编译器，将变量存储在程序的静态存储区而非栈上空间，静态数据成员按定义出现的先后顺序依次初始化，
注意静态成员嵌套时，要保证所嵌套的成员已经初始化了。消除时的顺序是初始化的反顺序。

2 static的作用
  2.1 在修饰变量的时候，static 修饰的静态局部变量只执行初始化一次，而且延长了局部变量的生命周期，直到程序运行结束以后才释放。
  2.2 修饰的变量存放在全局数据区的静态变量区，包括全局静态变量和局部静态变量，都在全局数据区分配内存。初始化的时候自动初始化为 0。
  2.3 修饰全局变量的时候，这个全局变量只能在本文件中访问，不能在其它文件中访问，即便是 extern 外部声明也不可以。
  2.4 不想被释放的时候，可用static修饰。如修饰函数中存放在栈空间的数组。如果不想让这个数组在函数调用结束释放可用 static 修饰。
  2.5 考虑到数据安全性(当程序想要使用全局变量的时候应该先考虑使用 static)。
  2.6 修饰一个函数，则这个函数的只能在本文件中调用，不能被其他文件调用。

静态变量与普通变量
  静态全局变量有以下特点：
  1 静态变量都在全局数据区分配内存，包括后面将要提到的静态局部变量;
  2 未初始化的静态全局变量(函数体外声明的自动变量)会被自动初始化为0(函数体内声明的自动变量的值是随机的，除非它被显式初始化)；
  3 静态全局变量在声明它的整个文件都是可见的，而在文件之外是不可见的。
优点：静态全局变量不能被其它文件所用；其它文件中可以定义相同名字的变量，不会发生冲突。

全局变量和全局静态变量的区别
  1 全局变量默认是外部链接性，作用域是整个工程，在一个文件内定义，在另一个文件中，通过 extern 声明，就可以使用全局变量。
  2 显式用 static 修饰的全局变量，作用域是声明此变量所在的文件，其他的文件即使用 extern 声明也不能使用。

静态局部变量有以下特点：
  1 该变量在全局数据区分配内存；
  2 静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化；
  3 静态局部变量一般在声明处初始化，如果没有显式初始化，会被程序自动初始化为 0；
  4 它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，当定义它的函数或语句块结束时，其作用域随之结束。

一般程序把新产生的动态数据存放在堆区，函数内部的自动变量存放在栈区。自动变量一般会随着函数的退出而释放空间，
静态数据(即使是函数内部的静态局部变量)也存放在全局数据区。全局数据区的数据并不会因为函数的退出而释放空间。

3 static 与 类
  3.1 静态成员变量   # static修饰的类变量，通过 类名::变量名 直接引用
    3.1.1 它可以实现多个对象之间的数据共享，它是类的所有对象的共享成员，它在内存中只占一份空间。
    3.1.2 它在程序开始运行时分配空间，到程序结束后才释放，只要类中指定了静态数据成员，即使不定义对象，也会为静态数据成员分配空间。
    3.1.3 它可以被初始化，但是只能在类体外进行初始化(类内声明 类外定义)，若未对静态数据成员赋初值，则编译器会自动为其初始化为 0。
    3.1.4 它既可以通过对象名引用，也可以通过类名引用。
  3.2 静态成员函数   # static修饰的类方法，通过 类名::方法名 直接引用
    3.2.1 它和静态数据成员一样，他们都属于类的静态成员，而不是对象成员。
    3.2.2 它没有 this 指针，而非静态成员函数有 this 指针。
    3.2.3 它主要用来访问静态数据成员而不能访问非静态成员，包括成员变量和成员函数。
  3.3例子
    class Point{
    public:
      void init(){}
      static void output(){}
      int m_x;
      static int m_sx;
    };
    3.3.1 不能通过类名来调用类的非静态成员函数。  Point::init();    编译失败
    3.3.2 可以通过类的对象调用静态成员函数和非静态成员函数。  Point pt;  pt.init();   pt.output();   OK
    3.3.3 静态成员函数中不能引用非静态成员。static void output(){printf("%d\n", m_x); }    编译失败
    3.3.4 非静态成员函数可以调用用静态成员。 void init(){output();}              OK
    3.3.5 类的静态成员变量必须先初始化再使用，否则会在 linker 时出错。
      void init(){m_sx++;} static void output(){printf("%d\n", m_sx)} main中 Point pt;  pt.output();编译成功
      运行出错 因为类的静态成员变量在使用前必须先初始化。需要 main() 函数前加上 int Point::m_nPointCount = 0;

    总结：静态资源属于类，但是是独立于类存在的。
    从类的加载机制的角度讲，静态资源是类初始化的时候加载的，而非静态资源是类实例化对象的时候加载的。
    类的初始化早于类实例化对象。所以对于静态资源来说，它是不可能知道一个类中有哪些非静态资源的；
    但是对于非静态资源来说就不一样了，由于它是实例化对象出来之后产生的，因此属于类的这些东西它都能认识。

  3.4 static 一般情况下来说是不可以修饰类的， 如果 static 要修饰一个类，
  说明这个类是一个静态内部类(注意 static 只能修饰一个内部类)，也就是匿名内部类。


字节对齐
https://cloud.tencent.com/developer/article/1631792

1 什么是字节对齐
计算机中内存大小的基本单位是字节(byte)，理论上来讲，可以从任意地址访问某种基本数据类型，
但是实际上，计算机并非逐字节大小读写内存，而是以2,4,8的倍数的字节块来读写内存，
如此一来就会对基本数据类型的合法地址作出一些限制，即它的地址必须是2，4或8的倍数。
那么就要求各种数据类型按照一定的规则在空间上排列，这就是对齐。

2 对齐准则
  2.1 结构体变量的首地址能够被其对齐字节数大小所整除。
  2.2 结构体每个成员相对结构体首地址的偏移都是成员大小的整数倍，如不满足，对前一个成员填充字节以满足。
  2.3 结构体的总大小为结构体对最大成员大小的整数倍，如不满足，最后填充字节以满足。

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




