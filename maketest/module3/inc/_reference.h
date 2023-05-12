Everything about Rvalue Reference
https://zhuanlan.zhihu.com/p/386350492

0. 前言
本文从值类别、移动语义、完美转发等方面来阐述什么是右值引用，为什么需要右值引用。

右值引用(Rvalue Reference)，与传统的左值引用(Lvalue Reference)相对，是绑定到右值的引用。

int n;
int &  lref = n;
int && rref = 1;
右值引用是 C++ 11 标准引入的语言特性，理解右值引用，对理解现代 C++ 语义至关重要。而这一概念又经常让人困惑，例如在下面的例子 “overload foo” 中，函数 foo 的调用会匹配哪一个重载？

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }

int main() {
  int &&rref = 1;
  foo(rref);    // which overload will be seleted?
}
答案是匹配 foo(int&)，是不是和想象中的不太一样？

1. 值类别（Value Category)
Each C++ expression (an operator with its operands, a literal, a variable name, etc.) is characterized by two independent properties: a type and a value category.
C++ 中的表达式有两个维度的属性：类型（type）和值类别（value category）。类型这个概念就是我们熟知的类型，int, int *, int &, int && 都是类型;其中 int 称为基础类型(fundamental type)，后三者称为复合类型(compound type)。而值类别分为：左值(lvalue)、亡值(xvalue) 和 纯右值(prvalue)，任一个表达式都可以唯一地归类到这三种值类别中的一个，这三种类别称为基础类别(primary category)。除了这三种基础类别外，还有两种混合类别(mixed category)：泛左值(glvalue)和右值(rvalue)，泛左值包括左值和亡值，右值包括亡值和纯右值。

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

2. 类型与值类别 （Type and Value Category）
在 C 的世界中，天空一片晴朗。值类别只有左值和其他。这时“左值 (lvalue)”的含义为标识一个对象的表达式，即“locator value”。类型和值类别泾渭分明，它们是正交的关系：即某个类型的表达式既可能是左值，也可能不是。C 世界中的人们只需要谨记一条规则：不能对非左值取址。（注意这不破坏正交性，指针类型的表达式可以是非左值，只是不能指向非左值）。大家对这条规则都欣然接受：非左值内存都不占，何来地址？

后来 C++98 突破次元壁来到了这个世界，带来了一朵乌云：引用，并且将非左值表达式命名为右值表达式。引用引入了这样一条规则：引用类型的变量只能绑定到左值表达式，只有const引用可以绑定到右值。表达式的类型和值类别第一次产生了联系：即引用类型的表达式一定是左值。这里要注意，const引用类型的变量可以绑定右值，但其本身仍是左值。大家对引用这个规则破坏者没有产生足够的警惕，依旧按照旧世界的框架来理解新世界：引用本质上就是指针嘛，指针只能指向左值，这个我懂，俺们村以前就是这样的。

直到 C++11 引入了右值引用类型和新的值类别概念，人们才开始慌了：卧槽这是啥玩意儿，俺咋没见过？

随着移动语义引入到 C++11 之中，值类别被重新进行了定义，以区别表达式的两种独立的性质：
拥有身份 (identity)：可以确定表达式是否与另一表达式指代同一实体，例如通过比较它们所标识的对象或函数的（直接或间接获得的）地址；
可被移动：移动构造函数、移动赋值运算符或实现了移动语义的其他函数重载能够绑定于这个表达式。
C++11 中：
拥有身份且不可被移动的表达式被称作左值 (lvalue)表达式；
拥有身份且可被移动的表达式被称作亡值 (xvalue)表达式；
不拥有身份且可被移动的表达式被称作纯右值 (prvalue)表达式；
不拥有身份且不可被移动的表达式无法使用。
拥有身份的表达式被称作“泛左值 (glvalue) 表达式”。左值和亡值都是泛左值表达式。
可被移动的表达式被称作“右值 (rvalue) 表达式”。纯右值和亡值都是右值表达式。

        | 是否可以动     不可移动    |      可移动 右值(rvalue)       |
        |                           |                               |
值得类别 |              左值(lvalue) | 亡值(xvalue) | 纯右值(prvalue) |
        |                                          |                |
        |是否有身份        有身份 泛左值(glvalue)    |     无身份     |

右值引用同样引入了一条规则：右值引用类型的变量只能绑定到右值表达式。但奇怪的事情出现了，和左值引用表达式只能是左值不同，右值引用类型的表达式既可以是左值，也可以是右值（纯右值或亡值）。旧世界的人们纷纷出现了不同程度的 Brain Freeze。我们通过例子 “overload foo” 来治疗这一症状：

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }

int main() {
  int &&rref = 1;
  foo(rref);    // output: lvalue
}
在这段代码中，foo(int&) 接受一个左值引用类型的形参，根据左值引用的规则，左值引用类型的变量只能绑定到左值表达式，我们知道，想要匹配这一个重载，调用者必须使用一个值类别为左值的实参；而 foo(int&&) 接受一个右值引用类型的形参，根据右值引用的绑定规则，右值引用类型的变量只能绑定到右值（纯右值或亡值）表达式，想要匹配这一个重载，调用者必须使用一个值类别为右值的实参。实际上，关于这个重载决议的规则，cppreference 里有专门的描述：

More importantly, when a function has both rvalue reference and lvalue reference overloads, the rvalue reference overload binds to rvalues (including both prvalues and xvalues), while the lvalue reference overload binds to lvalues.
所以，问题的答案很明显了：变量 rref 其实是一个左值，它的类型是 int 的右值引用 (int&&)，它绑定到一个右值（字面量1），但它本身是一个左值。

3. 移动语义（Move Semantic）
搞清楚了什么是右值引用，我们来看看为什么需要右值引用。先说结论：右值引用的出现弥补了 C++ 在移动语义上的缺失。在右值引用出现之前，我们在函数调用传参时，只有两种语义：给它一份拷贝（按值传递），或者给它一份引用（按引用传递）。

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
成员函数take的作用是接管外部传入的套接字，当我们使用拷贝语义时，会使得两个 Socket 对象同时持有同一份资源，可能导致资源的重用；而当使用引用的语义时，我们修改了原对象使其不可用，但并没有将这一点明确告知原对象的使用者，这可能导致资源的误用。我们可以在文档或者注释里说明原对象不可用，但不能用接口本身告知调用者资源的所有权已经被移交了。而右值引用的出现，就是在语法上支持了这一语义，因为右值引用只能绑定到纯右值或者亡值，意味着这一对象的资源可以被转移。在语法上支持移动语义，除了明确告知调用者语义之外，对自动化排错也是有积极意义的，编译器或者其他代码检查工具，可能可以通过语义分析排查亡值对象的错用。

此外，有些文章里可能会提到使用右值引用类型的形参可以优化函数调用，但实际上 T& 和 const T&同样可以做到这一点；另外还有人提到右值引用类型的函数返回值可以优化函数调用的返回过程，但实际上即使你的返回值是非引用类型，编译器在做编译优化的时候也会尽量避免返回值拷贝，想进一步了解的可以去查查 “return value optimization” 和“copy elision”。所以，我认为代码中使用右值引用最重要的目的还是其语义，与优化没多大关系。

4. 完美转发（Perfect Forwarding）
对完美转发问题的讨论其实已经超出了右值引用的范畴，准确地说，完美转发问题的解决依赖的是一种特殊的引用，称为转发引用（Forwarding Reference），只是因为它长得和右值引用有点像（都有&&），所以经常被人们误解为是右值引用。许多文章里声称右值引用的出现解决了完美转发问题，这是错误的，我们在这里先明确这一点。当然，完美转发问题和右值引用存在密切的联系，所以我们在这里仍然会讨论完美转发的问题。

什么是完美转发问题？当我们想要包装一个函数调用时，就会遇到完美转发问题。例如，我们有一个函数 bar，它什么也不干，就是包装一下 foo 的调用：

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }
void bar(int &i)  { foo(i); }
void bar(int &&i) { foo(std::move(i)); }  // 注意这里的move是必须的，不然会匹配 `foo(int&)`，i是一个左值还记得吗？
这里，我们将参数 i “完美” 地转发给了函数 foo，也就是当实参是左值时，我们将左值转发给foo；当实参是右值时，我们将右值转发给foo。所以准确一点地说，完美转发就是将函数实参以其原本的值类别转发出去。为什么一定要完美转发呢？因为如果没有实现完美转发，则会导致语义上的错误。例如，上面代码的第四行如果不加 std::move，就会将右值实参作为左值转发给 foo，使得我们本来想打印的输出“rvalue”变成了“lvalue”。在真实的生产场景中，这种语义错误可能会导致资源的所有权没有正确转移等后果。所以当实现函数包装时，完美转发不仅仅是出于性能的要求，更是出于语义正确性的要求。

然而，这里我们虽然实现了完美转发，却存在一个问题：对于 foo 的每一个重载版本，我们都要写一个函数签名相同的 bar 的重载与之对应。这个问题导致在泛型场景中，我们根本无法做到完美转发。例如，试想一下 std::make_shared 的实现吧：

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
我们还是通过 “foo&&bar” 这个简单的例子来说明解决方案，我们想实现的是这样一个效果：

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
所以，通俗一点来说，转发引用就是对一个待推导的类型 T 应用上右值引用的形式(T&&)。编译器在做类型推导时，会将绑定左值的T推导为左值引用类型，将绑定右值的T推导为原基本类型，再叠加引用坍缩规则后，绑定左值的变量的实际类型为左值引用，绑定右值的变量的实际类型为右值引用。而且即使显示地使用右值引用类型实例化模板，&& + && 也会坍缩为右值引用类型。

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
OK，我们解决了调用 bar 时参数值类别的问题，现在我们将 bar 的参数传递给 foo：

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }
template<typename T> int bar(T &&x) { foo(x); }
现在我们已经知道了，上面这段代码是有问题的，因为无论 x 的类型是左值引用还是右值引用，它的值类别都是一个左值，所以上面这段代码永远会调用 foo(int&)。而我们想要的效果是，当 x 是左值引用类型时，调用 foo(int&)；当 x 是右值引用类型时，调用 foo(int&&)。std::forward 可以帮我们解决这个问题，std::forward 的实现如下：

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
这段代码其实很简单，它的作用就是将左值转发为左值或右值，将右值转发为右值。当 std::forward 的实参值类别为左值时，会匹配第一个重载，这个重载根据 _Tp 的类型将实参转发为左值或右值；当 std::forward 的实参值类别为右值时，会匹配第二个重载，这个重载根据 _Tp 的类型将实参转发为右值。注意，在这里 _Tp 是无法由编译器推断的，必须显式指定，因为推断会有歧义。例如实参为左值时，_Tp 为 & 或 && 都可以匹配第一个重载。如果你不显示的指定想要 forward 的类型，编译器会抛出一个错误：

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
我们总结一下。完美转发问题是将函数的参数以其原本值类别转发出去的问题。转发引用 和 std::forward 共同解决了完美转发问题。其中，转发引用将函数的左值实参推导为左值引用类型，右值实参推导为右值引用类型。std::forward 将左值引用类型的实参转发为左值，将右值引用类型的实参转发为右值。最后，作为一个例子，我们看一下 std::make_shared 中完美转发的应用（仅是示例，真正实现不是这样）：

template<typename T, typename... Args>
std::shared_ptr<T> std::make_shared(Args&&... args) {
  return std::shared_ptr<T>(new T(std::forward<Args>(args)...);
}
5. 结语
我承认我标题党了，一篇文章当然不可能穷尽所有关于右值引用的知识，仅是介绍了一些最基本的内容，有错漏之处欢迎指导。