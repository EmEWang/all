

https://oraclechang.files.wordpress.com/2013/05/c11-a-cheat-sheete28094alex-sinyakov.pdf # C++11对比C++03
https://www.stroustrup.com/C++11FAQ.html                                                 # C++11
https://www.cnblogs.com/shadow-lr/p/Introduce_Std-move.html  # 一文带你详细介绍c++中的std::move函数
https://zhuanlan.zhihu.com/p/581739392                       # 从示例到源码深入了解std::ref



后置返回类型
https://www.imlb6.com/cpp11-trailing-return-type/
double foo(int i);           # 声明函数时，都是把返回值类型写在前面
auto foo(int i) -> double;   # 引入了一种新的函数声明语法，可以将返回值类型后置
template <typename T1, typename T2>
decltype(a + b) sum(T1 a, T2 b){return a + b;}          # 编译器会报错  为什么不能这样写?
原因是编译器在尝试对decltype(a + b)进行推导时，a和b还未声明，尽管它们就在后面，你可以理解为编译器只能从左到右进行处理。
auto sum(T1 a, T2 b) -> decltype(a + b){return a + b;}  # 引入一种新的语法，将返回值后置的主要原因。

int& foo(int& i);                                             # 返回类型后置和decltype结合还经常用在转发函数中。
float foo(float& f);
template <typename T>
auto forward(T& val) -> decltype(foo(val)){return foo(val);}  # 这种统一的转发函数在 C++11 之前是无法实现的。




Everything about Rvalue Reference
https://zhuanlan.zhihu.com/p/386350492

0. 前言
本文从值类别、移动语义、完美转发等方面来阐述什么是右值引用，为什么需要右值引用。

右值引用(Rvalue Reference)，与传统的左值引用(Lvalue Reference)相对，是绑定到右值的引用。

int n;
int &  lref = n;
int && rref = 1;
右值引用是 C++ 11 标准引入的语言特性，理解右值引用，对理解现代 C++ 语义至关重要。
而这一概念又经常让人困惑，例如在下面的例子 “overload foo” 中，函数 foo 的调用会匹配哪一个重载？

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }

int main() {
  int &&rref = 1;
  foo(rref);    // which overload will be seleted?
}
答案是匹配 foo(int&)，是不是和想象中的不太一样？

1. 值类别(Value Category)
Each C++ expression (an operator with its operands, a literal, a variable name, etc.)
is characterized by two independent properties: a type and a value category.
C++ 中的表达式有两个维度的属性：类型(type)和值类别(value category)。
类型这个概念就是我们熟知的类型，int, int *, int &, int && 都是类型；
其中 int 称为基础类型(fundamental type)，后三者称为复合类型(compound type)。
而值类别分为：左值(lvalue)、亡值(xvalue) 和 纯右值(prvalue)，任一个表达式都可以唯一地归类到这三种值类别中的一个，
这三种类别称为基础类别(primary category)。除了这三种基础类别外，还有两种混合类别(mixed category)：
泛左值(glvalue)和右值(rvalue)，泛左值包括左值和亡值，右值包括亡值和纯右值。


纯右值
字面量，this指针，lambda表达式
所有内建数值运算表达式：a + b, a % b, a & b, a << b
&a, 取址表达式
...

亡值
返回类型为对象的右值引用的函数调用或重载运算符表达式，如 std::move(x)
转换为对象的右值引用类型的转型表达式，如 static_cast(x)
...

左值
变量、函数、模板形参对象或数据成员的名字，如 std::cin
返回类型为左值引用的函数调用或重载运算符表达式，如 std::cout << 1
++a/--a
*ptr
...

泛左值
包括左值和亡值

右值
包括亡值和纯右值

到这里你可能已经被绕晕了，右值引用(T&&)是类型，右值(rvalue)又是值类别，它们之间有什么关系？ 如何理解值类别的含义呢？

2. 类型与值类别 (Type and Value Category)
在C中，值类别只有左值和其他。这时“左值(lvalue)”的含义为标识一个对象的表达式，即“locator value”。
类型和值类别泾渭分明，它们是正交的关系：即某个类型的表达式既可能是左值，也可能不是。
C只需要谨记一条规则：不能对非左值取址。(注意这不破坏正交性，指针类型的表达式可以是非左值，只是不能指向非左值)。
大家对这条规则都欣然接受：非左值内存都不占，何来地址？

C++98带来了：引用，并且将非左值表达式命名为右值表达式。
引用引入了这样一条规则：引用类型的变量只能绑定到左值表达式，只有const引用可以绑定到右值。
表达式的类型和值类别第一次产生了联系：即引用类型的表达式一定是左值。
这里要注意，const引用类型的变量可以绑定右值，但其本身仍是左值。
大家对引用这个规则破坏者没有产生足够的警惕，依旧按照旧世界的框架来理解新世界：引用本质上就是指针嘛，指针只能指向左值。

C++11引入了右值引用类型和新的值类别概念。

随着移动语义引入到 C++11 之中，值类别被重新进行了定义，以区别表达式的两种独立的性质：
拥有身份(identity)：可以确定表达式是否与另一表达式指代同一实体，例如通过比较它们所标识的对象或函数的(直接或间接获得的)地址；
可被移动：移动构造函数、移动赋值运算符或实现了移动语义的其他函数重载能够绑定于这个表达式。
C++11 中：
拥有身份且不可被移动的表达式被称作左值(lvalue)表达式；
拥有身份且可被移动的表达式被称作亡值(xvalue)表达式；
不拥有身份且可被移动的表达式被称作纯右值(prvalue)表达式；
不拥有身份且不可被移动的表达式无法使用。
拥有身份的表达式被称作“泛左值(glvalue)表达式”。左值和亡值都是泛左值表达式。
可被移动的表达式被称作“右值(rvalue)表达式”。纯右值和亡值都是右值表达式。

        | 是否可以移动     不可移动   |      可移动 右值(rvalue)       |
        |                           |                               |
值得类别 |              左值(lvalue) | 亡值(xvalue) | 纯右值(prvalue) |
        |                                          |                |
        | 是否有身份        有身份 泛左值(glvalue)   |     无身份     |

右值引用同样引入了一条规则：右值引用类型的变量只能绑定到右值表达式。
和左值引用表达式只能是左值不同，右值引用类型的表达式既可以是左值，也可以是右值(纯右值或亡值)。
通过例子 “overload foo” 来说明：
void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }

int main() {
  int &&rref = 1;
  foo(rref);    // output: lvalue
}
在这段代码中，foo(int&) 接受一个左值引用类型的形参，根据左值引用的规则，左值引用类型的变量只能绑定到左值表达式，
想要匹配这一个重载，调用者必须使用一个值类别为左值的实参；
而 foo(int&&) 接受一个右值引用类型的形参，根据右值引用的绑定规则，右值引用类型的变量只能绑定到右值(纯右值或亡值)表达式，
想要匹配这一个重载，调用者必须使用一个值类别为右值的实参。实际上，关于这个重载决议的规则，cppreference 里有专门的描述：
More importantly, when a function has both rvalue reference and lvalue reference overloads,
the rvalue reference overload binds to rvalues (including both prvalues and xvalues),
while the lvalue reference overload binds to lvalues.
所以变量 rref 其实是一个左值，它的类型是 int 的右值引用 (int&&)，它绑定到一个右值(字面量1)，但它本身是一个左值。

3. 移动语义(Move Semantic)
搞清楚了什么是右值引用，来看看为什么需要右值引用。先说结论：右值引用的出现弥补了 C++ 在移动语义上的缺失。
在右值引用出现之前，在函数调用传参时，只有两种语义：给它一份拷贝(按值传递)，或者给它一份引用(按引用传递)。

void inc_by_value(int i) { ++i; }
void inc_by_ref(int &i) { ++i; }

int main() {
  int i = 0;
  inc_by_value(i);
  inc_by_ref(i);
  std::cout << i << std::endl;  // output: 1
}
在上面的这个场景中，语义的缺失并不明显，但当我们处理持有资源的对象时，就不是那么和谐了：

class Socket {
 public:
  void take(Socket other) { sockfd_ = other.sockfd_; }
  void take(Socket &other) {
    sockfd_ = other.sockfd_;
    other.sockfd_ = 0;
  }

 private:
  int sockfd_;
};
成员函数take的作用是接管外部传入的套接字，当使用拷贝语义时，会使得两个 Socket 对象同时持有同一份资源，可能导致资源的重用；
而当使用引用的语义时，我们修改了原对象使其不可用，但并没有将这一点明确告知原对象的使用者，这可能导致资源的误用。
可以在文档或者注释里说明原对象不可用，但不能用接口本身告知调用者资源的所有权已经被移交了。
而右值引用的出现，就是在语法上支持了这一语义，因为右值引用只能绑定到纯右值或者亡值，意味着这一对象的资源可以被转移。
在语法上支持移动语义，除了明确告知调用者语义之外，对自动化排错也是有积极意义的，
编译器或者其他代码检查工具，可能可以通过语义分析排查亡值对象的错用。

此外，有些文章里可能会提到使用右值引用类型的形参可以优化函数调用，但实际上 T& 和 const T&同样可以做到这一点；
另外还有人提到右值引用类型的函数返回值可以优化函数调用的返回过程，但实际上即使你的返回值是非引用类型，
编译器在做编译优化的时候也会尽量避免返回值拷贝，想进一步了解的可以去查查 “return value optimization” 和“copy elision”。
所以，我认为代码中使用右值引用最重要的目的还是其语义，与优化没多大关系。

4. 完美转发(Perfect Forwarding)
对完美转发问题的讨论其实已经超出了右值引用的范畴，准确地说，完美转发问题的解决依赖的是一种特殊的引用，
称为转发引用(Forwarding Reference)，只是因为它长得和右值引用有点像(都有&&)，所以经常被人们误解为是右值引用。
许多文章里声称右值引用的出现解决了完美转发问题，这是错误的，我们在这里先明确这一点。
当然，完美转发问题和右值引用存在密切的联系，所以我们在这里仍然会讨论完美转发的问题。

什么是完美转发问题？当想要包装一个函数调用时，就会遇到完美转发问题。
例如，有一个函数 bar，它什么也不干，就是包装一下 foo 的调用：
void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }
void bar(int &i)  { foo(i); }
void bar(int &&i) { foo(std::move(i)); }  // 注意这里的move是必须的，不然会匹配 `foo(int&)`，i是一个左值还记得吗？
这里，将参数 i “完美” 地转发给了函数 foo，也就是当实参是左值时，将左值转发给foo；当实参是右值时，将右值转发给foo。
所以准确一点地说，完美转发就是将函数实参以其原本的值类别转发出去。
为什么一定要完美转发呢？因为如果没有实现完美转发，则会导致语义上的错误。
例如，如果不加 std::move，就会将右值实参作为左值转发给 foo，使得本来想打印的输出“rvalue”变成了“lvalue”。
在真实的生产场景中，这种语义错误可能会导致资源的所有权没有正确转移等后果。
所以当实现函数包装时，完美转发不仅仅是出于性能的要求，更是出于语义正确性的要求。

然而，这里虽然实现了完美转发，却存在一个问题：对于 foo 的每一个重载版本，都要写一个函数签名相同的 bar 的重载与之对应。
这个问题导致在泛型场景中，根本无法做到完美转发。例如，试想一下 std::make_shared 的实现吧：

template<typename T, ...>  // 先省略模板形参
std::shared_ptr<T> std::make_shared(...) {  // 先省略函数形参列表
  // 为了简化讨论省略内部实现，直接构造一个 T 的 shared_ptr 返回
  return std::shared_ptr<T>(new T(...));
}

// 对于用户定义的两个类 `A` 和 `B`，`std::make_shared` 怎么做到匹配所有的可能的重载呢？
struct A {
  A(int &) {}
  A(int &&) {}
};

struct B {
  B(float &, int) {}
  B(float  , int &&) {}
};

还是通过 “foo&&bar” 这个简单的例子来说明解决方案，我们想实现的是这样一个效果：

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }
template<typename /*T*/> void bar(/*T*/ x) { /*call foo with x*/ }

int main() {
  int i;
  bar(i);  // expecting output: lvalue
  bar(1);  // expecting output: rvalue
}
在这里，变量 i 经历了两次转发，所以我们需要先后解决这两次转发的值类别问题。

用户调用 bar 时，参数的值类别问题
当用户以左值表达式调用 bar 时，确保其实例化(Instantiation)的形参类型为左值引用
当用户以右值表达式调用 bar 时，确保其实例化的形参类型为右值引用。
bar 调用 foo 时，参数的值类别问题
当 bar 的形参类型为左值引用时，将其以左值转发给 foo
当 bar 的形参类型为右值引用时，将其以右值转发给 foo

C++ 通过转发引用来解决第一个匹配，通过 std::forward 来解决第二个匹配。

先来看转发引用，转发引用基于一个叫做引用坍缩(Reference Collapsing)的原理：
rvalue reference to rvalue reference collapses to rvalue reference, all other combinations form lvalue reference.
typedef int&  lref;
typedef int&& rref;
int n;
lref&  r1 = n; // type of r1 is int& ,  int&  + &  => int &
lref&& r2 = n; // type of r2 is int& ,  int&  + && => int &
rref&  r3 = n; // type of r3 is int& ,  int&& + &  => int &
rref&& r4 = 1; // type of r4 is int&&,  int&& + && => int &&

那么转发引用是什么呢？转发引用具有下面两种基本形式：
// 1. function parameter of a function template declared as rvalue reference to
//    cv-unqualified type template parameter of that same function template

template<class T>
int f(T&& x);  // x is a forwarding reference

template<class T>
int g(const T&& y);  // y is not a forwarding reference: const T is not cv-unqualified

template<class T> struct A {
  template<class U>
  A(T&& x, U&& y, int* p);   // x is not a forwarding reference: T is not a
                             // type template parameter of the constructor,
                             // but y is a forwarding reference
};

// 2. auto&& except when deduced from a brace-enclosed initializer list

auto&& x = f();   // f() may be lvalue or rvalue, x is a forwarding reference

int g(auto &&y);  // y is a forwarding reference

auto&& z = {1, 2, 3};  // z is NOT a forwarding reference (special case for initializer lists)
                       // decltype(z) is std::initializer_list<int>
所以，通俗一点来说，转发引用就是对一个待推导的类型 T 应用上右值引用的形式(T&&)。
编译器在做类型推导时，会将绑定左值的T推导为左值引用类型，将绑定右值的T推导为原基本类型，
再叠加引用坍缩规则后，绑定左值的变量的实际类型为左值引用，绑定右值的变量的实际类型为右值引用。
而且即使显示地使用右值引用类型实例化模板，&& + && 也会坍缩为右值引用类型。

举例说明：
void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }
template<typename T> int bar(T &&x);  // x is a forwarding reference

int main() {
  int i = 1;
  int &lref = i;
  int &&rref = 1;

  bar(1);                 // T 为 int,   decltype(x) 为 int&&
  bar(i);                 // T 为 int&,  decltype(x) 为 int&
  bar(lref);              // T 为 int&,  decltype(x) 为 int&
  bar(rref);              // T 为 int&,  decltype(x) 为 int&
  bar(std::move(rref));   // T 为 int,   decltype(x) 为 int&&
  bar<int &&>(1);         // T 为 int&&, decltype(x) 为 int&&
}
解决了调用 bar 时参数值类别的问题，现在将 bar 的参数传递给 foo：

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }
template<typename T> int bar(T &&x) { foo(x); }
这段代码是有问题的，因为无论 x 的类型是左值引用还是右值引用，它的值类别都是一个左值，所以上面这段代码永远会调用 foo(int&)。
而想要的效果是，当 x 是左值引用类型时，调用 foo(int&)；当 x 是右值引用类型时，调用 foo(int&&)。
std::forward 可以帮我们解决这个问题，std::forward 的实现如下：

/**
 *  @brief  Forward an lvalue.
 *  @return The parameter cast to the specified type.
 *
 *  This function is used to implement "perfect forwarding".
 */
template<typename _Tp>
constexpr _Tp&&
forward(typename std::remove_reference<_Tp>::type& __t) noexcept
{ return static_cast<_Tp&&>(__t); }

/**
 *  @brief  Forward an rvalue.
 *  @return The parameter cast to the specified type.
 *
 *  This function is used to implement "perfect forwarding".
 */
template<typename _Tp>
constexpr _Tp&&
forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
{
  static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
                " substituting _Tp is an lvalue reference type");
  return static_cast<_Tp&&>(__t);
}
这段代码其实很简单，它的作用就是将左值转发为左值或右值，将右值转发为右值。
当 std::forward 的实参值类别为左值时，会匹配第一个重载，这个重载根据 _Tp 的类型将实参转发为左值或右值；
当 std::forward 的实参值类别为右值时，会匹配第二个重载，这个重载根据 _Tp 的类型将实参转发为右值。
注意，在这里 _Tp 是无法由编译器推断的，必须显式指定，因为推断会有歧义。
例如实参为左值时，_Tp 为 & 或 && 都可以匹配第一个重载。如果你不显示的指定想要 forward 的类型，编译器会抛出一个错误：
// error: candidate template ignored: couldn't infer template argument '_Tp'
std::forward(i);

下面的例子可以帮助你理解 std::forward 的作用：
void foo(const int &)  { std::cout << "lvalue" << std::endl; }
void foo(const int &&) { std::cout << "rvalue" << std::endl; }

int main() {
  int i = 1;
  foo(std::forward<int>(i));     // output: rvalue; forward lvalue -> rvalue
  foo(std::forward<int&>(i));    // output: lvalue; forward lvalue -> lvalue
  foo(std::forward<int&&>(i));   // output: rvalue; forward lvalue -> rvalue
  foo(std::forward<int>(1));     // output: rvalue; forward rvalue -> rvalue
  foo(std::forward<int&>(1));    // error: static_assert failed due to requirement '!is_lvalue_reference<int &>::value' "can not forward an rvalue as an lvalue"
  foo(std::forward<int&&>(1));   // output: rvalue; forward rvalue -> rvalue
}
OK，现在利用 std::forward，我们就可以将 bar 的实参传递给 foo 了：

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }
template<typename T> int bar(T &&x) { foo(std::forward<T>(x)); }

int main() {
  int i = 1;
  bar(i);  // output: lvalue
  bar(1);  // output: rvalue
}

总结一下。
完美转发问题是将函数的参数以其原本值类别转发出去的问题。转发引用 和 std::forward 共同解决了完美转发问题。
其中，转发引用将函数的左值实参推导为左值引用类型，右值实参推导为右值引用类型。
std::forward 将左值引用类型的实参转发为左值，将右值引用类型的实参转发为右值。
最后，作为一个例子，我们看一下 std::make_shared 中完美转发的应用(仅是示例，真正实现不是这样)：
template<typename T, typename... Args>
std::shared_ptr<T> std::make_shared(Args&&... args) {
  return std::shared_ptr<T>(new T(std::forward<Args>(args)...);
}








左值，右值，将亡值
https://cloud.tencent.com/developer/beta/article/1543336
http://naipc.uchicago.edu/2015/ref/cppreference/en/cpp/language/value_category.html (三值精简版)
http://en.cppreference.com/w/cpp/language/value_category  (三值详细版)

C++中有“左值”、“右值”的概念，C++11以后，又有了“左值”、“纯右值”、“将亡值”的概念。

表达式
  要说清“三值”，首先要说清表达式。
  表达式由运算符(operator)和运算对象(operand)①构成的计算式(类似于数学上的算术表达式)。
  举例来说字面值(literal)和变量(variable)是最简单的表达式，函数的返回值也被认为是表达式。

值类别
  表达式是可求值的，对表达式求值将得到一个结果(result)。这个结果有两个属性：类型和值类别(value categories)。
  下面我们将详细讨论表达式的值类别。
  在c++11以后，表达式按值类别分，必然属于以下三者之一：
  左值(left value,lvalue)，将亡值(expiring value,xvalue)，纯右值(pure rvalue,pralue)。
  左值和将亡值合称泛左值(generalized lvalue,glvalue)，纯右值和将亡值合称右值(right value,rvalue)。
                              value
                              ↙    ↘
                        glvalue    rvalue
                         ↙    ↘    ↙    ↘
                    lvalue    xvalue   prvalue

有一点需要说明，严格来讲，“左值”是表达式的结果的一种属性，但更为普遍地，我们通常用“左值”来指代左值表达式。
所谓左值表达式，就是指求值结果的值类别为左值的表达式。通常我们无需区分“左值”指的是前者还是后者，
因为它们表达的是同一个意思，不会引起歧义。在后文中，我们依然用左值指代左值表达式。对于纯右值和将亡值，亦然。

详细说明
事实上，无论是左值、将亡值还是纯右值，我们目前都没有一个精准的定义。它们事实上表征了表达式的属性，
而这种属性的区别主要体现在使用上，如能否做运算符的左操作数、能否使用移动语义等。
因此，从实际应用出发，我们首先需要做到的是：给定一个表达式，能够正确地判断出它的值类别。
为了能做到这一点，采取了一个实际的方式：先对各个值类别的特征加以描述，然后指出常见的表达式里边，哪些属于该类别。

1 左值
描述：能够用&取地址的表达式是左值表达式。
举例来说，
函数名和变量名(实际上是函数指针和具名变量，具名变量如std::cin、std::endl等)、返回左值引用的函数调用、
前置自增/自减运算符连接的表达式++i/--i、由赋值运算符或复合赋值运算符连接的表达式(a=b、a+=b、a%=b)、
解引用表达式*p、字符串字面值"abc"(关于这一点，后面会详细说明)等。

2 纯右值
描述
满足下列条件之一：
本身就是赤裸裸的、纯粹的字面值，如3、false；求值结果相当于字面值或是一个不具名的临时对象。
举例
除字符串字面值以外的字面值、返回非引用类型的函数调用、后置自增/自减运算符连接的表达式i++/i--、
算术表达式(a+b、a&b、a<<b)、逻辑表达式(a&&b、a||b、~a)、比较表达式(a==b、a>=b、a<b)、取地址表达式(&a)等。

下面从上面的例子中选取若干典型详细说明左值和纯右值的判断。

2.1 ++i是左值，i++是右值。
++i，对i加1后再赋给i，最终的返回值就是i，所以，++i的结果是具名的，名字就是i；
i++，先对i进行一次拷贝，将副本作为返回结果，然后再对i加1，由于i++的结果是对i加1前i的一份拷贝，所以它是不具名的。
如i=6，++i结果是7，这个7有个名字，就是i；i++结果是6，这个6是i加1前的一个副本，它没有名字，i不是它的名字，i的值此时是7。
可见，++i和i++都达到了使i加1的目的，但两个表达式的结果不同。

2.2 解引用表达式*p是左值，取地址表达式&a是纯右值。
&(*p)一定是正确的，因为*p得到的是p指向的实体，&(*p)得到的就是这一实体的地址，正是p的值。由于&(*p)的正确，所以*p是左值。
而对&a而言，得到的是a的地址，相当于unsigned int型的字面值，所以是纯右值。

2.3 a+b、a&&b、a==b都是纯右值
a+b得到的是不具名的临时对象，而a&&b和a==b的结果非true即false，相当于字面值。

3 将亡值
在C++11之前的右值和C++11中的纯右值是等价的。C++11中的将亡值是随着右值引用④的引入而新引入的。
换言之，“将亡值”概念的产生，是由右值引用的产生而引起的，将亡值与右值引用息息相关。所谓的将亡值表达式，就是下列表达式：
返回右值引用的函数的调用表达式
转换为右值引用的转换函数的调用表达式

读者会问：这与“将亡”有什么关系？

在C++11中，用左值去初始化一个对象或为一个已有对象赋值时，会调用拷贝构造函数或拷贝赋值运算符来拷贝资源(资源指new出来的东西)；
而当用一个右值(包括纯右值和将亡值)来初始化或赋值时，会调用移动构造函数或移动赋值运算符⑤来移动资源，从而避免拷贝，提高效率。
当该右值完成初始化或赋值的任务时，它的资源已经移动给了被初始化者或被赋值者，同时该右值也将会马上被销毁(析构)。
也就是说，当一个右值准备完成初始化或赋值任务时，它已经“将亡”了。
而上面1)和2)两种表达式的结果都是不具名的右值引用，它们属于右值(关于“不具名的右值引用是右值”这一点，后面还会详细解释)。
又因为这种右值是与C++11新生事物——“右值引用”相关的“新右值”，这种右值常用来完成移动构造或移动赋值的特殊任务，
扮演着“将亡”的角色，所以C++11给这类右值起了一个新的名字——将亡值。
如，std::move()、static_cast(x)(x是自定义类X的对象，这两个函数常用来将左值强制转换成右值，从而使拷贝变成移动，提高效率)。
事实上，将亡值不过是C++11提出的一块晦涩的语法糖。
它与纯右值在功能上及其相似，如都不能做操作符的左操作数，都可以使用移动构造函数和移动赋值运算符。
当一个纯右值来完成移动构造或移动赋值任务⑥时，其实它也具有“将亡”的特点。一般不必刻意区分一个右值到底是纯右值还是将亡值。

将左值和将亡值合称泛左值的原因(见三值详细版)，如两者都可以使用多态，都可以隐式转换成纯右值，都可以是不完全类型(incomplete type)等。


4 特别注意
4.1 字符串字面值是左值。不是所有的字面值都是纯右值，字符串字面值是唯一例外。
早期C++将字符串字面值实现为char型数组，实实在在地为每个字符都分配了空间并且允许程序员对其进行操作，所以类似
cout<<&("abc")<<endl;
char *p_char="abc";//注意不是char *p_char=&("abc");

这样的代码都是可以编译通过的。
注意上面代码中的注释，"abc"可以直接初始化指针p_char，p_char的值为字符串"abc"的首字符a的地址。
而&("abc")被编译器编译为const的指向数组的指针const char (*) [4](4，是因为编译器会在"abc"后自动加上一个'\0')，
它不能初始化char *类型，即使是const char *也不行。
另外，对于char *p_char="abc";，在GCC4.9(C++14)及以前的版本会给出警告，在GCC5.3(C++14)及以后的版本则直接报错：
ISO C++ forbids converting a string constant to 'char*'(ISO C++禁止string常量向char*转换)。
但这并不影响“字符串字面值是左值”这一结论的正确性，因为cout<<&("abc")<<endl;在各版本编译器上都能编译通过，没有警告和错误。

4.2 具名的右值引用是左值，不具名的右值引用是右值。
例1
void foo(X&& x)
{
    X xb = x;
   //后面还可以访问x
 }
X是自定义类，并且，其有一个指针成员p指向了在堆中分配的内存；参数x是X的右值引用。
如果将x视为右值，X anotherX=x;一句将调用X类的移动构造函数(主要是将x的p指针的值赋给xb的p指针，然后将x的p指针置为nullptr)。
而在后面，我们还可以访问x，也就是可以访问x.p，而此时x.p已经变成了nullptr，这就可能发生意想不到的错误。

例2
X& foo(X&& x)
{
     //对x进行一些操作
     return x;
}

//调用
foo(get_a_X());//get_a_X()是返回类X的右值引用的函数
foo的调用以右值(确切说是将亡值)get_a_X()为实参，调用类X的移动构造函数构造出形参x，然后在函数体内对x进行一些操作，
最后return X，这样的代码很常见，也很符合我们的编写思路。
注意foo函数的返回类型定义为X的引用，如果x为右值，那么，一个右值是不能绑定到左值引用上去的。

为避免这种情况的出现，C++规定：具名的右值引用是左值。这样一来，例一中X anotherX = x;一句将调用X的拷贝构造函数，
执行后x不发生变化，继续访问x不会出问题；例2中，return x也将得到允许。

例2中，get_a_X返回一个不具名右值引用(唯一作用就是初始化形参x)，在后面的代码中，不会也无法访问这个不具名的右值引用。
C++将其归为右值，是合理的，一方面，可以使用移动构造函数，提高效率；另一方面，这样做不会出问题。


5 注释
①只有当存在两个或两个以上的运算对象时才需要运算符连接，单独的运算对象也可以是表达式，例如上面提到的字面值和变量。
②确切说，是表达式的结果的值类别，但我们一般不刻意区分表达式和表达式的求值结果，所以这里称“表达式的值类别”。
③当我们将函数名作为一个值来使用时，该函数名自动转换为指向对应函数的指针。
④关于右值引用本身，就是指可以绑定到右值上的引用，用"&&"表示，如int &&rra=6;
相比之下，与右值引用相关的一些主题，如移动语义、引用叠加、完美转发等，更值得我们深入探讨。
⑤前提是该右值(如自定义的类X)有移动构造函数或移动赋值运算符可供调用(有时候是没有的)。
⑥在本文的例2中，如果将get_a_X()的返回值由X的右值引用改为X对象，则get_a_X()是纯右值表达式
(如前所述，返回非引用类型的函数调用是纯右值)，
此时Foo(get_a_X());一句调用的仍然是类X的移动构造函数，这就是一个纯右值完成移动构造的例子。





C++11 关键字noexcept
1 关键字noexcept
从C++11开始，我们能看到很多代码当中都有关键字noexcept。比如下面就是std::initializer_list的默认构造函数，其中使用了noexcept。

      constexpr initializer_list() noexcept
      : _M_array(0), _M_len(0) { }
该关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。
如果在运行时，noexecpt函数向外抛出了异常（如果函数内部捕捉了异常并完成处理，这种情况不算抛出异常），程序会直接终止，调用std::terminate()函数，该函数内部会调用std::abort()终止程序。

2 C++的异常处理
C++中的异常处理是在运行时而不是编译时检测的。为了实现运行时检测，编译器创建额外的代码，然而这会妨碍程序优化。
在实践中，一般两种异常抛出方式是常用的：

一个操作或者函数可能会抛出一个异常;
一个操作或者函数不可能抛出任何异常。
后面这一种方式中在以往的C++版本中常用throw()表示，在C++ 11中已经被noexcept代替。

    void swap(Type& x, Type& y) throw()   //C++11之前
    {
        x.swap(y);
    }
    void swap(Type& x, Type& y) noexcept  //C++11
    {
        x.swap(y);
    }
3 有条件的noexcecpt
在第2节中单独使用noexcept，表示其所限定的swap函数绝对不发生异常。然而，使用方式可以更加灵活，表明在一定条件下不发生异常。

    void swap(Type& x, Type& y) noexcept(noexcept(x.swap(y)))    //C++11
    {
        x.swap(y);
    }
它表示，如果操作x.swap(y)不发生异常，那么函数swap(Type& x, Type& y)一定不发生异常。

一个更好的示例是std::pair中的移动分配函数（move assignment），它表明，如果类型T1和T2的移动分配（move assign）过程中不发生异常，那么该移动构造函数就不会发生异常。

    pair& operator=(pair&& __p)
    noexcept(__and_<is_nothrow_move_assignable<_T1>,
                    is_nothrow_move_assignable<_T2>>::value)
    {
        first = std::forward<first_type>(__p.first);
        second = std::forward<second_type>(__p.second);
        return *this;
    }
4 什么时候该使用noexcept？
使用noexcept表明函数或操作不会发生异常，会给编译器更大的优化空间。然而，并不是加上noexcept就能提高效率，步子迈大了也容易扯着蛋。
以下情形鼓励使用noexcept：

移动构造函数（move constructor）
移动分配函数（move assignment）
析构函数（destructor）。这里提一句，在新版本的编译器中，析构函数是默认加上关键字noexcept的。下面代码可以检测编译器是否给析构函数加上关键字noexcept。
    struct X
    {
        ~X() { };
    };

    int main()
    {
        X x;

        // This will not fire even in GCC 4.7.2 if the destructor is
        // explicitly marked as noexcept(true)
        static_assert(noexcept(x.~X()), "Ouch!");
    }
叶子函数（Leaf Function）。叶子函数是指在函数内部不分配栈空间，也不调用其它函数，也不存储非易失性寄存器，也不处理异常。
最后强调一句，在不是以上情况或者没把握的情况下，不要轻易使用noexception。



