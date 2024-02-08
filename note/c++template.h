

“未限定名称”(unqualified-name)指的是一个没有明确限定作用域的名称，比如单纯的 “foo”，而不是 “std::foo”。

C++ Template Metaprogramming
https://zhuanlan.zhihu.com/p/378360055
1. Introduction
  1.1 What is Metaprogramming?
  1.2 What is C++ Template Metaprogramming?
  1.3 History of TMP
  1.4 Why should we Learn TMP？
2. Template Basics
  2.1 Template Declaration and Definition
  2.2 Template Parameters and Arguments
  2.3 Template Instantiation
  2.4 Template Arguments Deduction
  2.5 Template Specialization
  2.6 Function Template Overloading
  2.7 Review of binary
3. Learn TMP in Use (Part I)
  3.1 Example 1: Type Manipulation
    3.1.1 is_reference
    3.1.2 remove_reference
  3.2 Metafunction Convention
    3.2.1 Metafunction always return a "type"
    3.2.2 integral_const
    3.2.3 use public inheritance
    3.2.4 useful aliases
  3.3 Example 2: Metafunction with Multiple Arguments
    3.3.1 is_same
    3.3.2 is_one_of
    3.3.3 is_instantiation_of
    3.3.4 conditional
  3.4 Example 3: Deal with Arrays
    3.4.1 rank
    3.4.2 extent
4. Template in Depth
  4.1 Template Arguments Deduction of Function Template
  4.2 Template Arguments Deduction of Class Template
  4.3 Make Choice between Primary Template and Its Specializations
  4.4 Partial Ordering Rule
  4.5 Template Overloads vs Template Specializations
  4.6 SFINAE
  4.7 Review of Template Instantiation
5. Learn TMP in use (Part II)
  5.1 Example 4: SFINAE
    5.1.1 enable_if
    5.1.2 void_t
  5.2 Example 5: Unevaluated Expressions
    5.2.1 declval
    5.2.2 add_lvalue_reference
    5.2.3 is_copy_assignable
  5.3 Example 6: Applications in Real World
    5.3.1 std::tuple
    5.3.2 A Universal json::dumps
6. Constraints and Concepts






1. Introduction
1.1 What is Metaprogramming?
Meta 这个词根有着 “更高一层抽象” 的意味。例如我们在数据结构设计中提到的 Metadata 常指 “描述数据的数据”，
在 Python 中使用的 Metaclass 是 “描述 class 的 class”，Metaprogramming 也有类似的意思。

元编程(Metaprogramming)就是编写一类特殊程序的编程，这类程序将其他程序或者其自身视为输入的数据来进行处理，
我们称这类特殊的程序为元程序(Metaprogramming)。

Metaprogramming is the writing of computer programs that write or manipulate other programs
(or themselves) as their data.[1]

对于元程序，有个更诗意的描述：
Metaprogram is a program about a program. [2]
元程序是处理程序的程序，元编程就是编写元程序的一种编程技巧。这听起来有点拗口，但却不难理解。
编译器就是一个 Metaprogram，它处理我们输入的 Source Code，将其转化为平台相关的 Binary Code。
同样的，Python虚拟机也是一个元程序，它将 Python 代码翻译为虚拟机指令执行。

Compilers are computer programs that translate a program written in one language into
a program written in another language.[3]
我们举一个更具体的例子，YACC 是一个语法分析器生成器(Parser Generator)，
它的输入是一份对语法(Grammar)的描述，输出是一个语法分析器(Parser)。
                                        INPUT ↘
grammar.y -> YACC -> y.tab.c -> C Compiler -> Parse
                                        OUTPUT ↗
运行上图中 Infix-to-Postfix 这个例子将得到下面的结果，它检查一个中缀表达式是否合法，并将它转为后缀的。

$ yacc intopost.y && gcc y.tab.c && ./a.out
2+1*5
NUM1 NUM2 NUM3 MUL PLUS
这里有趣的一点是，Parser 本身也是一个 Metaprogram，YACC 是生成 Metaprogram 的 Metaprogram，
这与 YACC 的全称不谋而合：Yet Another Compiler-Compiler。
在这个例子中，YACC 处理的代码 grammar.y 是用一种专门的语言 Context Free Grammar (CFG) 描述的，
YACC 将之转译为 C 后再由 C 编译器处理。在这里，我们称 CFG 为 Domain Language，称 C 为 Host Language。
我们根据是否使用了 Domain Language 来实现元编程，可以将元编程技术分为两类：

(1)Metaprogramming with Domain Language
在这类元编程中，元程序定义一种专门的语言(Domain Language)，逻辑代码是用 Domain Language 书写的，
然后被元程序翻译为目标语言(Host Langugage)再去编译执行。
逻辑代码(无论是用 Domain Language 还是 Host Language 表示)与元程序的代码是分离的。

Domain -> Language Metaprogram -> Host Language

(2)Metaprogramming in Host Language
在这类元编程中，逻辑代码和元程序自身的代码是写在一起的，用同一种语言，
元程序代码通过某种机制(通常是编译)转变为(或者说生成)逻辑代码，并与其他逻辑代码合并到一起。
这就产生一种效果，这个元程序看起来像是在自己改写自己。
Metaprogram

C++ 模板元编程(C++ Template Metaprogramming, TMP)就是第二种类型，TMP 的代码与普通的 C++ 代码写在一起，
但 TMP 的逻辑在编译期执行，而普通 C++ 代码的逻辑在运行期执行。

1.2 What is C++ Template Metaprogramming?
C++ Template Metaprogramming(TMP)顾名思义是利用 C++ 模板进行的元编程。借助编译器处理模板的能力，
TMP 可以在编译期间生成代码，这些代码最终和普通的 C++ 代码一起编译执行。我们举一个例子来直观地展示什么是 TMP：

template <int N>
struct binary {
  static constexpr int value = binary<N / 10>::value << 1 | N % 10;
};

template <>
struct binary<0> {
  static constexpr int value = 0;
};
在上面的代码中，我们先是定义了一个名为 binary 的模板，然后定义了一个 binary 的特化 (Specialization)。
关于模板的特化我们会在后面详细介绍，这里可以将它理解为当 N==0 时对应的特殊版本。
利用这段代码，我们可以在编译期计算出一个二进制数对应的十进制值：

std::cout << binary<101>::value << std::endl;       // Equivalent to: std::cout << 5 << std::endl;
std::cout << binary<1110>::value << std::endl;      // Equivalent to: std::cout << 14 << std::endl;
std::cout << binary<10110>::value << std::endl;     // Equivalent to: std::cout << 22 << std::endl;
binary<x>::value 在编译期就会被求值，得到一个常量。对模板不熟悉的读者可能会对这一点产生怀疑，
我们可以用下面的代码来证明 binary<x>::value 是一个常量，如果不是，那么这句话在编译时就会报错，
因为 C++ 要求在编译时就确定静态数组的长度。(在 C++ 中，如果一个东西的名字里包含 static，那么它大概率是编译期就决定的东西，
如static_assert，static_cast；同样的，dynamic 通常意味着运行时才确定的事物，如 dynamic_cast, dynamic_link)

static char array[binary<101>::value];     // Equivalent to: static char array[5]
我们在这里暂时不去探究 binary 作用的原理，稍后在学习了模板的基础知识后，我们再回来看 binary 是怎么起作用的。
重要的是我们通过这个例子看到了 TMP 在编译期计算的能力。这种能力不是空中楼阁，C++ 模板已经被证明了是图灵完备的，
这意味着可由计算机程序表达的任何计算都可以通过 TPM 来完成。

1.3 History of TMP
有意思的是，C++ 的这种在编译时计算的能力，并非是有意设计发明的，而是“偶然”发现的。
1994 年，C++ 标准委员会在圣地亚哥举行的一次会议期间，Erwin Unruh 展示了一个可以产生质数的程序。
这个程序的特别之处在于质数的产生发生于编译期而非运行期，它在编译器产生的一系列错误提示中打印出了 2 到某个指定值之间的所有质数。
这个程序被认为是 TMP 的起源，它第一次向世人展示了 TMP 的能力。从根源上来说，这种在编译期计算的能力源自于 C++ 标准对模板的描述。
对于这段历史，更详细的描述可以参看 Erwin Unruh 的个人回忆。
在 TMP 之前，STL 的泛型容器和算法被认为是模板编程的巅峰之作，TMP 使得人们重新认识了模板的能力。

与 C++ 的很多技术一样，TMP 的发展是由社区推动的。
自 Erwin Unruh 之后，许多人都开始研究 TMP，并在他们的项目中使用 TMP 相关的技术。
其中最典型是一系列 Metaprogramming Library 的出现，这些 Library 提供编译期的容器和算法，就像是 STL 一样。
不同的是这些容器存储的是常量和类型，这些算法都是运行在编译期间。比较知名的 Metaprogramming Library 有：
boost: MPL(2003), hana(2016), mp11(2017)
github: brigand(2015), meta(2015), metal(2015)

这些 Library 提供相似的功能，但细节上有一些不同，下面几篇文章里对它们进行了一些比较：
Tradeoffs of TMP MPL design
Boost - Dev - Discussion: About all these metaprogramming libraries
Comparative TMP #1: MPL, Mp11, Kvasir, Hana, Metal。

C++ 标准也在 C++11 之后对 TMP 进行了大幅支持，包括一些核心的语言特性和标准库组件。这里我列举了一些我觉得比较重要的：
C++11: type traits, auto, variadic templates, decltype, declval, alias template
C++14: variable template, generic lambda, generalized constexpr, return type decuction
C++17: class template argument deduction, if constexpr, constexpr lambda
C++20: constraints and concepts, abbreviated function templateconsteval, constinit,
总之，相对于 C++，TMP 是一个比较 “年轻” 的技术，经过20多年的发展，现在已经成为了 C++ 程序设计不可或缺的一部分。

1.4 Why should we Learn TMP？
对许多人来说，在编译期计算听起来不仅匪夷所思，而且毫无必要：要算质数，我在运行时计算不好吗？
对我来说，学习和使用 TMP 的理由主要有下面四个：

一：TMP 可以做编译期的计算
这使得我们能将一些运行时的工作迁移到编译期，从而提升程序的运行时效率。当然这也是有代价的，通常，
将工作迁移到编译期会导致编译的时间变长，以及目标文件(object file) 的大小增大。
但因为我们的程序是一次编译多次运行的，所以有时候以编译期的代价换取运行时的效率是非常划算的。
这有点类似于渲染中“烘焙”的技术，虽然烘焙场景需要很长时间，烘焙出的资源文件也会使游戏包体变大，
但它在运行时的性能优化是我们更想要的。

二：TMP 可以对类型(type)做计算
如果说性能优化还可能通过别的方式实现，那么 TMP 对类型做计算的能力则是无可替代的了。
众所周知，C++ 缺乏有效的自省机制，在运行时根据变量的类型去编写逻辑是不可能的。
但在编译期，类型可以作为模板的实参(Arguments) 参与逻辑运算，这使得我们可以写出类似下面这样的代码：
// pseudo code
if (typeof(var) == int) { ... }
else { ... }

三：TMP 可以使代码变得简洁优美
TMP 自身的代码是晦涩难懂的，甚至可以说是 “丑陋” 的，但有时它却可以使使用它的外部代码变得简洁优雅。
例如下面是使用 pybind11 导出一个 C++ 类到 Python 的代码，如果没有 TMP，pybind11 的接口不可能如此简洁明了：
// export a C++ class to python by pybind11
py::class_<Pet>(m, "Pet")
  .def(py::init<const std::string &>())
  .def("setName", &Pet::setName)
  .def("getName", &Pet::getName);

四：TMP 的广泛应用
正如我前面所说的，TMP 已经是一个广泛使用且不可或缺的技术了，即使你没有直接写过 TMP 的代码，也一定曾间接地从 TMP 中受益。
很多程序库，特别是泛型程序库，都几乎不可避免地使用了 TMP，例如 Standard Library，asio, pybind11, boost::python 等。
如果你不了解 TMP，你可能都看不懂这些库中的代码，那更别提深度使用它们了。





2. Template Basics
TMP 的学习必须建立在对 C++ 模板坚实理解的基础之上，本章我们介绍一些模板的基础概念。

2.1 Template Declaration and Definition
在 C++ 中，我们一共可以声明(declare) 5种不同的模板，分别是：类模板(class template)、
函数模板(function template)、变量模板(variable template)、别名模板(alias template)、和概念(concept)。

// declarations
template <typename T> struct  class_tmpl;
template <typename T> void    function_tmpl(T);
template <typename T> T       variable_tmpl;          // since c++14
template <typename T> using   alias_tmpl = T;         // since c++11
template <typename T> concept no_constraint = true;   // since c++20
其中，前三种模板都可以拥有定义(definition)，而后两种模板不需要提供定义，因为它们不产生运行时的实体
(对于 concept，目前的术语还不清晰，在 cpp_reference 里能看到 difinition of a concept 的字样，
但根据一般的理解，concept 语句应该属于声明语句)。

// definitions
template <typename T> struct  class_tmpl {};
template <typename T> void    function_tmpl(T) {}
template <typename T> T       variable_tmpl = T(3.14);
可以看到，对于类模板、函数模板、和变量模板，它们的声明和定义与普通的类、函数和变量一致，
区别仅是在开头多了一个 template 关键字以及一对尖括号<...>。
template 关键字表明这是一个模板，尖括号中声明了模板的参数。
参数通常是类型，因为模板的发明就是为了实现泛型编程(Generic Programming)，因此在模板中，
类型(type)被参数化(Parameterized)了。这也是为什么我们可以在 TMP 中对类型做计算。
另外，由于模板的发明是为了泛型编程而非元编程，因此 TMP 代码的语法是很反人类的，既难读又难写。

要注意，在提到模板的时候，我们应该使用类模板(class template)、函数模板(function template)这样的词汇，
而非模板类(template class)、模板函数(template function)。后者通常指代由模板生成的具体的类和函数，
就像牛奶巧克力和巧克力牛奶是不同的东西一样。类模板不是类，函数模板也不是函数，它们是模板，是对类和函数的描述。
这也是 TMP 的思想基石：模板是对代码的描述。

此外，还需要注意的一点是，在 C++14 中我们有了泛型 lambda (generic lambda)，它的定义看起来很像模板，
但它不是模板，只是它的函数调用运算符(operator())是一个函数模板：
// NOTE: Generic lambda (since c++14) is NOT a template,
// its operator() is a member function template.
auto glambda = []<typename T>(T a, auto&& b) { return a < b; };

2.2 Template Parameters and Arguments
在模板中，我们可以声明三种类型的 形参(Parameters)，分别是：非类型模板形参(Non-type Template Parameters)、
类型模板形参(Type Template Parameters)和模板模板形参(Template Template Parameters)：
// There are 3 kinds of template parameters:
template <int n>                               struct NontypeTemplateParameter {};
template <typename T>                          struct TypeTemplateParameter {};
template <template <typename T> typename Tmpl> struct TemplateTemplateParameter {};
其中，非类型的形参接受一个确定类型的常量作为实参(Arguments)，
例如在上面的例子中，模板 NontypeTemplateParameter 接受一个 int 类型的常量。
更一般地，非类型模板形参必须是 结构化类型(structural type) 的，主要包括：
整型，如 int, char, long
enum 类型
指针和引用类型
浮点数类型和字面量类型(C++20后)
要注意的是，非类型模板实参必须是常量，因为模板是在编译期被展开的，在这个阶段只有常量，没有变量。

template <float &f>
void foo() { std::cout << f << std::endl; }

template <int i>
void bar() { std::cout << i << std::endl; }

int main() {
  static float f1 = 0.1f;
  float f2 = 0.2f;
  foo<f1>();  // output: 0.1
  foo<f2>();  // error: no matching function for call to 'foo', invalid explicitly-specified argument.

  int i1 = 1;
  int const i2 = 2;
  bar<i1>();  // error: no matching function for call to 'bar',
              // the value of 'i' is not usable in a constant expression.
  bar<i2>();  // output: 2
}

对于类型模板形参(Type Template Parameters)，我们使用 typename 关键字声明它是一个类型。
对于模板模板形参(Template Template Parameters)，和类模板的声明类似，也是在类型的前面加上 template <...>。
模板模板形参只接受类模板或类的别名模板作为实参，并且实参模板的形参列表必须要与形参模板的形参列表匹配。

template <template <typename T> typename Tmpl>
struct S {};

template <typename T>             void foo() {}
template <typename T>             struct Bar1 {};
template <typename T, typename U> struct Bar2 {};

S<foo>();   // error: template argument for template template parameter
            // must be a class template or type alias template
S<Bar1>();  // ok
S<Bar2>();  // error: template template argument has different template
            // parameters than its corresponding template template parameter

关键字 typename 可以替换为 class，它们是等效的，唯一的不同就是字面语义。
我更倾向于使用 typename，这更接近类型模板形参和模板模板形参的语义。而 class 在某些时候会产生让人困惑的字面语义，
想象一下一个名叫 template <class T> 的模板可以接受 int 作为实参，而 int 不是 class。

一个模板可以声明多个形参，更一般地，可以声明一个变长的形参列表，称为 "template parameter pack"，
这个变长形参列表可以接受 0 个或多个非类型常量、类型、或模板作为模板实参。变长形参列表必须出现在所有模板形参的最后。

// template with two parameters
template <typename T, typename U> struct TemplateWithTwoParameters {};

// variadic template, "Args" is called template parameter pack
template <int... Args>                            struct VariadicTemplate1 {};
template <int, typename... Args>                  struct VariadicTemplate2 {};
template <template <typename T> typename... Args> struct VariadicTemplate3 {};

VariadicTemplate1<1, 2, 3>();
VariadicTemplate2<1, int>();
VariadicTemplate3<>();

模板可以声明默认实参，与函数的默认实参类似。
只有 主模板(Primary Template) 才可以声明默认实参，模板特化(Template Specialization)不可以。
后面会介绍什么是主模板和模板特化。
// default template argument
template <typename T = int> struct TemplateWithDefaultArguments {};

2.3 Template Instantiation
模板的实例化(Instantiation)是指由泛型的模板定义生成具体的类型、函数、和变量的过程。
模板在实例化时，模板形参被替换(Substitute)为实参，从而生成具体的实例。
模板的实例化分为两种：按需(或隐式)实例化(on-demand (or implicit) instantiation) 和
显示实例化(explicit instantiation)，其中隐式的实例化是我们平时最常用的实例化方式。
隐式实例化，或者说按需实例化，是当我们要用这个模板生成实体的时候，要创建具体对象的时候，才做的实例化。
而显式实例化是告诉编译器，你帮我去实例化一个模板，但我现在还不用它创建对象，将来再用。
要注意，隐式实例化和显式实例化并不是根据是否隐式传参而区分的。

自 C++11 后，新标准还支持了显式的实例化声明(explicit instantiation declaration)，
我们会在后面的 Advanced Topics - Explicit Instantiation Declarations 中介绍这一特性。

// t.hpp
template <typename T> void foo(T t) { std::cout << t << std::endl; }

// t.cpp
// on-demand (implicit) instantiation
#include "t.hpp"
foo<int>(1);
foo(2);
std::function<void(int)> func = &foo<int>;

// explicit instantiation
#include "t.hpp"
template void foo<int>(int);
template void foo<>(int);
template void foo(int);

当我们在代码中使用了一个模板，触发了一个实例化过程时，编译器就会用模板的实参(Arguments)
去替换(Substitute)模板的形参(Parameters)，生成对应的代码。
同时，编译器会根据一定规则选择一个位置，将生成的代码插入到这个位置中，这个位置被称为 POI(point of instantiation)。
由于要做替换才能生成具体的代码，因此 C++ 要求模板的定义对它的 POI 一定要是可见的。
换句话说，在同一个翻译单元(Translation Unit)中，编译器一定要能看到模板的定义，才能对其进行替换，完成实例化。
因此最常见的做法是，我们会将模板定义在头文件中，然后再源文件中 #include 头文件来获取该模板的定义。
这就是模板编程中的包含模型(Inclusion Model)。

现在的一些 C++ 库，整个项目中就只有头文件，没有源文件，库的逻辑全部由模板实现在头文件中。
而且这种做法似乎越来越流行，在 GitHub 和 boost 中能看到很多很多。
我想原因一个是 C++ 缺乏一个官方的 package manager，这样发布的软件包更易使用(include就行了)；
另一个就是模板实例化的这种要求，使得包含模型成为泛型编程中组织代码最容易的方式。

但包含模型也有自身的问题。在一个翻译单元(Translation Unit)中，同一个模板实例只会被实例化一次。
也就是对同一个模板传入相同的实参，编译器会先检查是否已实例化过，如果是则使用之前实例化的结果。
但在不同的翻译单元中，相同实参的模板会被实例化多次，从而产生多个相同的类型、函数和变量。这带来两个问题：

链接时的重定义问题，如果不加以处理，这些相同的实体会被链接器认为是重定义的符号，这违反了ODR(One Definition Rule)。
对这个问题的主流解决方案是为模板实例化生成的实体添加特殊标记，链接器在链接时对有标记的符号做特殊处理。
例如在 GNU 体系下，模板实例化生成的符号都被标记为弱符号(Weak Symbol)。
编译时长的问题，同一个模板传入相同实参在不同的编译单元下被实例化了多次，这是不必要的，浪费了编译的时间。
我们在 Advanced Topics - Explicit Instantiation Declarations 中讨论除了包含模型外的另一个方案，
它规避了上面这些问题，但也带来了其他的成本。

2.4 Template Arguments Deduction
为了实例化一个模板，编译器需要知道所有的模板实参，但不是每个实参都要显式地指定。
有时，编译器可以根据函数调用的实参来推断模板的实参，这一过程被称为模板实参推导(Template Arguments Deduction)。
对每一个函数实参，编译器都尝试去推导对应的模板实参，如果所有的模板实参都能被推导出来，
且推导结果不产生冲突，那么模板实参推导成功。举个例子：

template <typename T>
void foo(T, T) {}

foo(1, 1);      // #1, deduced T = int, equivalent to foo<int>
foo(1, 1.0);    // #2, deduction failed.
                // with 1st arg, deduced T = int
                // with 2nd arg, deduced T = double
在 #1 中，两次推导的结果一直，均为 int，推导成功；在 #2 中，两次推导的结果不一致，推导失败。
C++17 引入了类模板实参推导(Class Template Arguments Deduction)，可以通过类模板的构造函数来推导模板实参：

template <typename T>
struct S { S(T, int) {} };

S s(1, 2);     // deduced T = int, equivalent to S<int>

2.5 Template Specialization
模板的特化(Template Specialization)允许我们替换一部分或全部的形参，并定义一个对应改替换的模板实现。
其中，替换全部形参的特化称为全特化(Full Specialization)，
替换部分形参的特化称为偏特化(Partial Specialization)，非特化的原始模板称为主模板(Primary Template)。
只有类模板和变量模板可以进行偏特化，函数模板只能全特化。(测试函数模板也可以偏特化gcc9.4)
在实例化模板的时候，编译器会从所有的特化版本中选择最匹配的那个实现来做替换(Substitution)，
如果没有特化匹配，那么就会选择主模板进行替换操作。

// function template
template <typename T, typename U> void foo(T, U)       {}     // primary template
template <>                       void foo(int, float) {}     // full specialization

// class template
template <typename T, typename U> struct S             {};    // #1, primary template
template <typename T>             struct S<int, T>     {};    // #2, partial specialization
template <>                       struct S<int, float> {};    // #3, full specialization

S<int, int>();      // choose #2
S<int, float>();    // choose #3
S<float, int>();    // choose #1

我们可以只声明一个特化，然后在其他的地方定义它：

template <> void foo<float, int>;
template <typename T> struct S<float, T>;
这里你可能已经注意到了，特化声明与显式实例化(explicit instantiation)的语法非常相似，注意不要混淆了。

// Don't mix the syntax of "full specialization declaration" up with "explict instantiation"
template    void foo<int, int>;   // this is an explict instantiation
template <> void foo<int, int>;   // this is a full specialization declaration
除了语法外，二者的含义也很容易混淆。理论上来说，模板实例化的结果就是一个该模板的全特化，
因为它就是一个用确定实参替换了全部形参的模板实现。
所以有的书和文档中也会用特化(Specialization)这个词来指代模板实例化之后生成的那个实体(类型、函数、或变量)。
为了区分，我们称这种为隐式特化(Implicit Specialization)，称我们在本节中讨论的特化机制为显式特化(Explicit Specialization)。
很多的书和文档中是不做这种区分的，所以可能会产生误解，需要读者结合上下文去理解 Specialization 指的是什么。
本文中我们避免使用特化一词来指代实例化的结果，而改用“实例”或“实体”，特化一词专指模板的特化机制。

2.6 Function Template Overloading
函数模板虽然不能偏特化，但是可以重载(Overloading)，并且可以与普通的函数一起重载。
在 C++ 中，所有的函数和函数模板，只要它们拥有不同的签名(Signature)，就可以在程序中共存。
一个函数(模板)的签名包含下面的部分：

函数(模板)的非限定名(Unqualified Name)
这个名字的域(Scope)
成员函数(模板)的 CV 限定符
成员函数(模板)的 引用限定符
函数(模板)的形参列表类型，如果是模板，则取决于实例化前的形参列表类型
函数模板的返回值类型
函数模板的模板形参列表
所以，根据这个规则，下列的所有函数和函数模板foo，都被认为是重载，而非重定义：

template <typename T> void foo(T) {}    // #1
template <typename T> void foo(T*) {}   // #2
template <typename T> int foo(T) {}     // #3
template <typename T, typename U> void foo(T) {}    // #4
template <typename T, typename U> void foo(T, U) {} // #5
template <typename T, typename U> void foo(U, T) {} // #6
void foo(int) {}         // #7
void foo(float, int) {}  // #8
由于模板的参数可以推导，不用显式指定，所以函数模板和普通函数可以一起重载。
但是要注意，虽然上述 #5 和 #6 两个模板不是重定义，但在调用的时候仍有可能触发一个歧义错误，
编译器有时无法决定两个函数模板哪个的重载优先级更高，我们将在 4.4 Partial Ordering Rule 里进一步解释模板重载的偏序规则：

foo(1);           // call #7
foo(new int(1));  // call #2
foo(1.0f, 1);     // call #8
foo<int, float>(1, 1.0f);  // call #5
foo(1, 1.0f);              // error: ambiguous

2.7 Review of binary
我们在了解了模板的基础知识后，就可以解释 binary 的工作原理了：

// primary template
template <int N>  // non-type parameter N
struct binary {
  // an template instantiation inside the template itself, which contructs a recursion
  static constexpr int value = binary<N / 10>::value << 1 | N % 10;
};
// full specialization when N == 0
template <> struct binary<0> {
  static constexpr int value = 0;
};
std::cout << binary<101>::value << std::endl;    // instantiation
在上面的代码中，我们定义了一个主模板 binary，它接受一个非类型形参，更具体地说是一个 int 类型的形参。
同时，我们定义了一个 binary 的特化，它是模板 binary 在 N == 0 时的一个全特化，在实例化 binary<0> 时，
编译器会为我们匹配这一个特化。
在主模板中，我们定义了一个静态常量 value，并将它初始化为 binary<N / 10>::value << 1 | N % 10，
由于静态常量会在编译期求值，所以编译器在实例化 binary<101> 时会尝试求值(Evaluate)这个表达式。
这个表达式中包含了一个对 binary 的另一个实例化，所以编译器会递归地实例化 binary 这个模板。递归的过程如下：

N	instantiation	matches	recursion	value
101	binary<101>	primary	binary<10>::value << 1 丨 1	5
10	binary<10>	primary	binary<1>::value << 1 丨 0	2
1	binary<1>	primary	binary<0>::value << 1 丨 1	1
0	binary<1>	specialization	0	0
直到 N == 0 时，模板的实例化匹配到特化版本，在这个特化中，也定义了一个静态常量 value = 0，
递归到这里终止，被求值的表达式层层返回，最终计算出 binary<101>::value = 5。

通过对这个例子的分析，我们已经得到了 TMP 的一些线索：

模板像函数一样被使用，模板的形参就像是函数的形参，模板的静态成员作为函数的返回值。
通过实例化(Instantiation)来“调用”模板。
通过特化(Specialization)和重载(Overloading)来实现分支选择。
通过递归来实现循环逻辑。
所有过程发生在编译期间，由编译器驱动。
所以，我们已经有了函数，有了if/else，有了循环，这不就可以编程了嘛！这种编程的逻辑工作在编译期，
处理的数据是常量和类型，没有运行时，也没有变量。这，就是 TMP。





3. Learn TMP in Use (Part I)
本章中，我们通过几个正经一点的例子，来进一步了解 TMP，以及了解什么是 Metafunction Convention。
这些例子大部分来自标准库的 <type_traits>。

3.1 Example 1: Type Manipulation
3.1.1 is_reference
下面的这个模板可以判定一个类型是不是引用类型：

template <typename T> struct is_reference      { static constexpr bool value = false; };    // #1
template <typename T> struct is_reference<T&>  { static constexpr bool value = true; };     // #2
template <typename T> struct is_reference<T&&> { static constexpr bool value = true; };     // #3

std::cout << is_reference<int>::value << std::endl;    // 0
std::cout << is_reference<int&>::value << std::endl;   // 1
std::cout << is_reference<int&&>::value << std::endl;  // 1
is_reference 包含一个主模板和两个偏特化，它接受一个类型 T 作为参数。
当 T 传入一个右值引用类型时，编译器会选择 #3 这个模板特化来进行实例化；
当 T 传入一个左值引用类型时，编译器会选择 #2 这个模板特化来进行实例化；
而当 T 不是引用类型时，#2 和 #3 都不匹配，编译器选择主模板 #1 来进行实例化。
想要理解编译器是怎么做出这种决定的，我们假想这样一个过程(为了方便描述，我们记 #1 的形参为 T1，
#2 的形参为 T2，#3 的形参为 T3)：

对于 is_reference<int> 这个实例化，编译器首先确定了模板的实参为 int，
于是它尝试将 int “代入” 模板的特化中看是否匹配，并且要反向推导该特化的形参，看能否推导成功。
将 int 代入 #2，是匹配的，T2& 匹配 int，但反向推导 T2 失败，
因为没有任何一个类型加上引用符号后能和 int 相等，所以编译器不选择 #2。
同理，代入 #3，T3&& 匹配 int，反向推导失败，编译器也不能选择 #3。于是编译器只能选择主模板 #1。

对于 is_reference<int&> 这个实例化，编译器首先确定了模板的实参为 int&，将 int& “代入” 模板的特化中并反向推导。
代入 #2，T2& 匹配 int&，但反向推导 T2 = int，成功；
代入 #3，T3&& 匹配 int&，反向推导 T3 失败(引用叠加规则在此处不适用)；于是选择#2。

3.1.2 remove_reference
除了判定一个引用类型外，我们还可以移除一个类型的引用：

template <typename T> struct remove_reference      { using type = T; };     // #1
template <typename T> struct remove_reference<T&>  { using type = T; };     // #2
template <typename T> struct remove_reference<T&&> { using type = T; };     // #3

// case 1:
int&& i = 0;
remove_reference<decltype(i)>::type j = i;    // equivalent to: int j = i;

// case 2:
template <typename T>
void foo(typename remove_reference<T>::type a_copy) { a_copy += 1; }

foo<int>(i);    // passed by value
foo<int&&>(i);  // passed by value
同样的一个主模板和两个偏特化，同样的匹配规则。
例如，对于 remove_reference<int&&>，会匹配 #3，#3 中的 T 被推导为 int，于是 remove_reference<int&&>::type 就是 int。
这里你可能会有疑问，移除引用的语义是什么？一个变量被移除了引用之后是变成了一份拷贝了吗？
这里我们再次强调，TMP 工作在编译期，在编译期没有变量，只有常量和类型，这里的移除引用就是把一个引用类型变成对应的非引用类型。

另一个问题是，“case 2” 中为什么 remove_reference 的前面要加一个 “typename” 关键字？
这是因为 remove_reference<T>::type 是一个待决名(Dependent Name)，编译器在语法分析的时候还不知道这个名字到底代表什么。
对于普通的名字，编译器直接通过名字查找就能知道这个名字的词性。
但对于待决名，因为它是什么取决于模板的实参 T，所以直到编译器在语义分析阶段对模板进行了实例化之后，
它才能对“type”进行名字查找，知道它到底是什么东西，所以名字查找是分两个阶段的，待决名直到第二个阶段才能被查找。
但是在语法分析阶段，编译器就需要判定这个语句是否合法，所以需要我们显式地告诉编译器 “type” 是什么。
在 remove_reference<T>::type 这个语法中，type 有三种可能，一是静态成员变量或函数，二是一个类型，三是一个成员模板。
编译器要求对于类型要用 typename 关键字修饰，对于模板要用 template 关键字修饰，以便其完成语法分析的工作。

3.2 Metafunction Convention
我们已经看了两个例子了，是时候总结一些元编程的通用原则了，我们称之为 Metafunction Convention。

3.2.1 Metafunction always return a "type"
程序是逻辑和数据的集合。
is_reference 和 remove_reference 是两个类模板，但是在 TMP 中，它们接受实参，返回结果，是像函数一样地被使用。
我们称这种在编译期“调用”的特殊“函数”为 Metafunction，它代表了 TMP 中的“逻辑”。
Metafunction 接受常量和类型作为参数，返回常量或类型作为结果，我们称这些常量和类型为Metadata，它代表了 TMP 中的“数据”。
进一步地，我们称常量为 Non-type Metadata (or Numerical Metadata)，称类型为 Type Metadata。

但在上面的例子中我们看到，is_reference 的返回值名为 “value”，remove_reference 的返回值名为 “type”，
为了形式化上的一致性，Metafunction Convention 规定，所有的 Metafunction 都以 “type” 作为唯一的返回值，
对于原本已 “value” 指代的那些常量，使用一个类模板将它们封装起来，Metafunction 返回这个类模板的相应实例。我们举例说明：

// non-type metadata (or numerical metadata)
template <bool b>
struct bool_ { static constexpr bool value = b; };

// metafunction
template <typename T> struct is_reference      { using type = bool_<false>; };
template <typename T> struct is_reference<T&>  { using type = bool_<true>; };
template <typename T> struct is_reference<T&&> { using type = bool_<true>; };
我们定义了一个名为 bool_ 的类模板，以封装 bool 类型的常量，is_reference 的返回值就变成了 bool_ 和 bool。
在调用 is_reference 时，也是使用 “type” 这个名字，如果想访问结果中的布尔值，使用 is_reference<T>::type::value 即可。

注意，Metafunction Convention 的这种规定，并不是 C++ 语言上的要求，而是编程指导上的要求，
目的是规范元编程的代码，使其更具可读性和兼容性。
标准库、boost、github 上热门的 TMP 库都遵循了这一约定，你也应该遵守。

3.2.2 integral_const
在真实世界的场景中，一个典型的 Non-type Metadata 是这样定义的：

template <typename T, T v>
struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant;   // using injected-class-name
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};
这是我们在 TMP 中最常用的一个 Non-type Metadata，它除了像 bool_ 那样定义了一个 value 外，还定义了：

value_type 指代数据的类型
type 指代自身，即 integral_constant，这个成员使得 integral_constant 变成了一个返回自己的 Metafunction
operator value_type() 是到 value_type 的隐式类型转换，返回 value 的值
value_type operator() 是函数调用运算符重载，返回 value 的值
这些成员，特别是 type，都会使 TMP 变得更方便，后面会看到例子。通常我们在使用时还会定义一些 alias：

// alias
template <bool B> using bool_constant = integral_constant<bool, B>;
using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;
有了这些定义，is_reference 的定义就变成了：

template <typename T> struct is_reference      { using type = false_type; };
template <typename T> struct is_reference<T&>  { using type = true_type; };
template <typename T> struct is_reference<T&&> { using type = true_type; };
对它的调用就变成了：

std::cout << is_reference<int>::type::value;  // 0
std::cout << is_reference<int>::type();       // 0, implicit cast: false_type --> bool
std::cout << is_reference<int>::type()();     // 0

3.2.3 use public inheritance
当一个 Metafunction 使用另一个 Metafunction 的结果作为返回值时，不用自己定义 type 成员了，
只需要直接继承另一个 Metafunction 即可！比如，我们可以这样实现 is_reference：

template <typename T> struct is_reference      : public false_type {};
template <typename T> struct is_reference<T&>  : public true_type {};
template <typename T> struct is_reference<T&&> : public true_type {};
由于 true_type 和 false_type 内部定义了一个名为 “type” 的成员，而且这个成员指的是它们自己，
所以直接继承过来，is_reference 内部也就有了一个名为 “type” 的成员了。
类似地，我们可以实现一个新的 Metafunction，它判定一个类型是不是 int 或引用类型：

// another metafunction implemented by inheritance.
template <typename T> struct is_int_or_reference : public is_reference<T> {};
template <> struct is_int_or_reference<int> : public true_type {};

// metafunction call
std::cout << is_int_or_reference<int>::value;  // 1
std::cout << is_int_or_reference<int>();       // 1
std::cout << is_int_or_reference<int>()();     // 1
公有继承和直接定义“type” 成员，这两种方式效果类似，但有一些细微的差别，
例如继承的时候不仅 “type” 成员被继承过来了，“value” 也被继承了过来。
我们在 TMP 中会尽可能地使用这种继承的方式，而不是每次都去定义type。
因为这种方式实现的代码更简洁，也更具有一致性：当一个 Metafunction 依赖另一个 Metafunction 时，
就是应该直接获取另一个 Metafunction 的全部内容。
这种继承的形式可能一开始看不习惯，但用多了就会觉得真香。

另外，我们在定义类模板时，使用 struct 关键字，而不使用 class 关键字，这样就可以省略继承时的 public 关键字，
以及类模板定义内部的 public 关键字了。

我们再来看一个特殊的 Metafunction，可能是 TMP 中最简单的一个 Metafunction 了：

template <typename T>
struct type_identity { using type = T; };

type_identity<int>::type i;    // equivalent to: int i;
type_identity 这个模板接受一个形参 T，并返回 T 本身。
你可能会疑惑这样的一个东西有什么用，实际上它非常有用，结合前面提到的公有继承，它可以让你在一行代码内就写完一个 Metafunction：

// with type_identity, we can implement remove_reference like this:
template <typename T> struct remove_reference      : type_identity<T> {};
template <typename T> struct remove_reference<T&>  : type_identity<T> {};
template <typename T> struct remove_reference<T&&> : type_identity<T> {};
特别是当你使用一些自动格式化代码的工具(如 clang-format)时，如果你采用传统的 using type = ... 的写法，
工具就会自动帮你换行，因为一般类的头部和定义体是不能放在一行的。
但是通过结合公有继承和 type_identity，类的定义体变成了空的，工具就会允许你在一行内写完一个 Metafunction 了！

说出来你可能不信，就是这么一个看起来有点蠢的 type_identity，在 C++20 被加入到了标准库当中。

3.2.4 useful aliases
为了方便，我们通常还会创建两个东西来简化 Metafunction 的调用。

一、对于返回非类型常量的 Metafunction，我们定义一个 _v 后缀的变量模板(Variable Template)，
通过它可以方便地获取 Metafunction 返回的 value：

// variable template
template <typename T> inline constexpr bool is_reference_v = is_reference<T>::value;
二、对于返回一个类型的 Metafunction，我们声明一个 _t 后缀的别名模板(Alias Template)，
通过它可以方便地获取 Metafunction 返回的 type：

// alias template
template <typename T> using remove_reference_t = typename remove_reference<T>::type;
效果如下：

std::cout << is_reference_v<remove_reference_t<int&&>> << std::endl;    // output: 0
在后面的代码中，为了使代码更简单一些，我们只展示 Metafunction 本身的实现，省略 _v 和 _t 相关的内容。

3.3 Example 2: Metafunction with Multiple Arguments
目前我们举的例子全部是单个模板形参的，本节中我们看一看多个形参的例子。

3.3.1 is_same
假如说我们想判定两个类型是否相等，并以此来写一些逻辑，应该怎么做呢？
在 Python 中，我们用 isinstance 就可以了，但在 C++ 中，由于缺乏自省机制，所以普通的代码是不可能实现下面这种效果的：

int i = 0;
std::cout << is_same_v<decltype(i), int>   << std::endl;    // 1
std::cout << is_same_v<decltype(i), float> << std::endl;    // 0

if (is_same_v<decltype(i), int>) {
    // ...
} else {
    // ...
}
这里你可能会想到 RTTI(Run-Time Type Information)的机制，但 RTTI 不同编译器的实现可能有差别，
它的本意是为了实现 C++ 内部的一些语言机制，主要是动态多态(Dynamic Polymorphism)，因此依赖 RTTI 的代码可能不具备可移植性。
但是通过 TMP，我们可以实现一个 Metafunction 来达到判定类型的效果，原理非常简单：

template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};
is_same 是一个类模板，它有两个模板形参，T 和 U，它的主模板继承了 false_type，
另外有一个特化继承了 true_type，这个特化模板匹配 T 和 U 相同的情况。
这个过程和我们之前描述的一样，当 T 和 U 相同时，编译器将 T 和 U 代入模板特化的实参列表里，然后尝试推导特化模板的形参，
因为两个参数相同，所以推导得出一致的结果，匹配特化成功，is_same<T, U>::value == true。
当 T 和 U 不同时，推导失败，fallback 到匹配主模板，这时 is_same<T, U>::value == false。

3.3.2 is_one_of
这个例子展示变长形参，我们将 is_same 推广一下，给定一个类型 T，和一堆类型列表，判定 T 是否包含在这个列表之中。

template <typename T, typename U, typename... Rest>
struct is_one_of : bool_constant<is_one_of<T, U>::value || is_one_of<T, Rest...>::value> {};

template <typename T, typename U>
struct is_one_of<T, U> : is_same<T, U> {};

int i = 0;
std::cout << is_one_of_v<decltype(i), float, double> << std::endl;               // 0, #1
std::cout << is_one_of_v<decltype(i), float, int, double, char> << std::endl;    // 1, #2
is_one_of 的主模板形参分为三个部分：类型 T，类型 U，和变长形参列表(Parameter Pack)Rest，
另有一个特化模板，只接受两个参数 T 和 U，这个特化的逻辑等效于 is_same。
主模板的递归逻辑是一个析取表达式，判定 T 和 U 是否相等，或者判定 T 是不是包含在剩余的参数中。
这里的 Rest... 是对变长形参列表的展开，当我们要引用一个变长形参列表内的内容时，就需要这样写。
这个递归会一直持续遍历所有的参数，直到只剩下 T 和 最后一个参数，这时匹配模板特化，递归终止。

要注意的是，这个析取表达式的求值与运行时不同，运行时的析取表达式遵循“短路求值(short-circuit evaluation)”的规则，
对 a || b 如果 a 为 true，就不再对 b 求值了。
但是在编译期，在模板实例化的时候，析取表达式的短路求值是不生效的，例如对 #2，
虽然在遍历到 bool_constant<is_one_of<int, int> || is_one_of<int, double, char>> 的时候，
虽然前面的表达式已经可以确定为 true 了，但是后半部分的表达式 is_one_of<int, double, char> 依旧会被实例化。
感兴趣的同学可以尝试用代码证明这个问题。

另外，有一个元编程的小技巧是，有时我们可以通过一个简单地别名来实现一个新的 Metafunction。例如：

// alias template
template <typename T>
using is_integral = is_one_of<T, bool, char, short, int, long, long long>;

3.3.3 is_instantiation_of
这个例子展示模板模板形参(Template Template Parameters)。
is_instantiation_of 接受两个参数，一个类型，一个模板，它可以判定这个类型是不是这个模板的实例类型。

std::list<int>     li;
std::vector<int>   vi;
std::vector<float> vf;

std::cout << is_instantiation_of_v<decltype(vi), std::vector> << std::endl;  // 1
std::cout << is_instantiation_of_v<decltype(vf), std::vector> << std::endl;  // 1
std::cout << is_instantiation_of_v<decltype(li), std::vector> << std::endl;  // 0
std::cout << is_instantiation_of_v<decltype(li), std::list>   << std::endl;  // 1

// is_instantiation_of
template <typename Inst, template <typename...> typename Tmpl>
struct is_instantiation_of : false_type {};

template <template <typename...> typename Tmpl, typename... Args>
struct is_instantiation_of<Tmpl<Args...>, Tmpl> : true_type {};
is_instantiation_of 也有一个主模板和一个偏特化，主模板继承 false_type，它匹配当这个类型不是模板的实例时的情况；
特化模板继承自 true_type，它匹配当传入的类型是对应模板的实例时的情况。
这个过程也是和上面一样的，确定实参->代入特化->反向推导，大家可以自行尝试推演一下，我就不赘述了。

3.3.4 conditional
我们已经看到了很多通过类模板特化来实现选择逻辑的例子，更通用地，我们可以实现一个通用的选择，
就像是 if 语句那样，如果条件为 true，就走一个分支，条件为 false，就走另一个分支。
conditional 就是编译期的 if：

template<bool B, typename T, typename F>
struct conditional : type_identity<T> {};

template<typename T, typename F>
struct conditional<false, T, F> : type_identity<F> {};
当 B 是 false 时，匹配模板的特化，返回 F；当 B 是 true 时，匹配主模板，返回 T。
这里值得一提的是，通过 conditional，我们可以实现一个类似 “短路求值” 的效果。
例如我们用 conditional 来实现 is_one_of：

// With conditional, we can implement a "short-circuited" is_one_of.
// For is_one_of<int, float, int, double, char>,
// is_one_of<int, double, char> will NOT be instantiated.

template <typename T, typename U, typename... Rest>
struct is_one_of : conditional_t<
  is_same_v<T, U>, true_type, is_one_of<T, Rest...>> {};

template <typename T, typename U>
struct is_one_of<T, U> : conditional_t<
  is_same_v<T, U>, true_type, false_type> {};
每一次递归前，我们都先判定了 T 和 剩余所有参数中的第一个 U 是否相等，如果相等，就直接返回 true_type 了，不会再向下递归。
所以在上面那个 #2 的例子中，is_one_of<int, double, char> 不会再被实例化了。这个技巧有时可以用来优化编译时长。

3.4 Example 3: Deal with Arrays
最后一组例子，我们来看在 TMP 中是怎么处理数组类型的。

3.4.1 rank
rank 返回数组的维度。

std::cout << rank_v<int> << std::endl;              // 0
std::cout << rank_v<int[5]> << std::endl;           // 1
std::cout << rank_v<int[5][5]> << std::endl;        // 2
std::cout << rank_v<int[][5][6]> << std::endl;      // 3

template <typename T>
struct rank : integral_constant<std::size_t, 0> {};                          // #1

template <typename T>
struct rank<T[]> : integral_constant<std::size_t, rank<T>::value + 1> {};    // #2

template <typename T, std::size_t N>
struct rank<T[N]> : integral_constant<std::size_t, rank<T>::value + 1> { };  // #3
rank 包含一个主模板和两个偏特化。根据模板特化的匹配规则我们知道，当模板实参是数组类型时，
会匹配 #2 或 #3 这两个特化，当实参是非数组类型时，匹配主模板。
其中，#2 匹配不定长数组；#3 匹配定长数组。整个递归的过程就是对维度做递归，每次递归 value + 1，就可以得到总维度。
这里我们可以思考一个问题：对于 int[5][6]，毫无疑问会匹配到特化 #3，那么这时 #3 的两个参数 T 和 N 被推导为什么呢？
是 int[5] 和 6，还是 int[6] 和 5？答案我不公布了，你可以尝试写代码来测试看看。

3.4.2 extent
extent 接受两个参数，一个数组 T 和一个值 N，它返回 T 的第 N 维的大小。

std::cout << extent_v<int[3]> << std::endl;        // 3
std::cout << extent_v<int[3][4], 0> << std::endl;  // 3
std::cout << extent_v<int[3][4], 1> << std::endl;  // 4
std::cout << extent_v<int[3][4], 2> << std::endl;  // 0
std::cout << extent_v<int[]> << std::endl;         // 0


template<typename T, unsigned N = 0>
struct extent : integral_constant<std::size_t, 0> {};

template<typename T>
struct extent<T[], 0> : integral_constant<std::size_t, 0> {};

template<typename T, unsigned N>
struct extent<T[], N> : extent<T, N-1> {};

template<typename T, std::size_t I>
struct extent<T[I], 0> : integral_constant<std::size_t, I> {};

template<typename T, std::size_t I, unsigned N>
struct extent<T[I], N> : extent<T, N-1> {};
其实，看懂了 extent 的代码，你也就知道上面那个问题的答案了。
extent 共有 4 个偏特化，前两个匹配不定长数组，后两个匹配定长数组，主模板匹配非数组类型。原理类似，我不赘述了。



4. Template in Depth
读到这里，恭喜你，你对 TMP 已经有不错的认知了！但我们还没充分展示 TMP 的威力，比如前面提到的 Function Template 都还没派上用场。
本章中我们将了解一些进阶的模板知识，并在下一章将它们应用到例子中去。

4.1 Template Arguments Deduction of Function Template
函数模板的实参推导发生在名字查找(Name Lookup)之后，重载决议(Overload Resolution)之前。
如果函数模板实参推导失败，那么编译器不会直接报错，而是将这个模板从函数的重载集中无声地删除。[4][5]

template <typename T, typename U> void foo(T, U) {}     // #1
template <typename T> void foo(T, T) {}                 // #2
void foo(float, int) {}                                 // #3

foo(1, 1.0f);  // call #1, deduction of #2 faild
               // with 1st arg, deduced T = int; with 2nd arg, deduced T = float
例如，在上面的例子中，foo 有两个函数模板和一个普通函数，对 #2 的实参推导失败了，但并不会发生错误，编译器会匹配模板 #1。
我们简单地阐述一下这个过程中发生了什么：

首先，编译器看到了对函数 foo 的一个调用。
编译器通过名字查找，找到所有名为 “foo” 的函数和函数模板，找到了#1，#2，和#3。
对每个函数模板，编译器尝试通过函数实参(1, 1.0f)来推断模板的实参。
对#1，T 被推导为 int，U 被推导为 float，OK。
对#2，通过第一个参数推导 T 为 int，通过第二个参数推导 T 为 float，失败，#2 被移出重载集。
编译器对当前重载集(#1和#3)进行重载决议，#1 被选中
编译器对 #1 进行替换(Substitution)以完成实例化。

4.2 Template Arguments Deduction of Class Template
类模板的实参推导与函数模板不同，当同时定义了主模板和模板特化时，实参推导只考虑主模板，模板特化不参与实参推导。[6]。
如果主模板实参推导出错，那么编译器直接报错。

template <typename T, typename U>
struct S           { S(T a, U b) { std::cout << is_same_v<decltype(b), float> } };  // #1

template <typename T>
struct S<T, float> { S(T a, T b) { std::cout << is_same_v<decltype(b), float> } };  // #2

template <>
struct S<int, int> { S(int a, int b) { std::cout << is_same_v<decltype(b), float> } };  // #3

S s(1, 1.0f);     // match #2, output: 0
例如在上面的例子中，编译器通过主模板的构造函数推导出 T=int, U=float，这个模板实参的最佳匹配结果是特化#2，
所以最终调用的构造函数是 #2 实例化后的 S<int, float>::S(int, int)，第二个实参 1.0f 被隐式转型为了 int。
而假设你用特化 #2 去做模板实参推导的话，这个推导是失败的，这也反证了编译器并不是用模板特化推导实参的。
我们也简单阐述一下这里发生的事：

首先，编译器看到变量“s”的定义。
编译器通过名字查找，找到名为“S” 的类或类模板，这里应该只找到一个，否则会抛出一个类型重定义的错误。
编译器找到了类模板 S，对 S 的主模板，编译器尝试根据构造函数实参(1, 1.0f)推导模板实参，得到 T=int, U=float。
编译器根据模板实参去匹配最优的特化，匹配到 #2。
编译器对 #2 进行替换(Substitution)以完成实例化。

4.3 Make Choice between Primary Template and Its Specializations
在前面的许多例子中，我们已经简单阐述了编译器是如何在主模板和特化模板之间做出选择的。现在，我们来更加准确地描述这一过程。

在模板的实例化(Instantiation)中，当所有的模板实参都确定了之后(这些实参可能是显式指定的、推导的、或者从默认实参中获取的)，
编译器就需要在模板的主模板和所有显式特化中选择一个来做替换(Substitution)。规则是：

对每一个模板特化，先判断它能不能匹配该实例化(判断过程我们在3.1.1 is_reference中讲了)。
如果只有一个模板特化能匹配模板实参，那么就选择这个特化；
如果有多个模板特化都能匹配模板实参，那么通过这些特化的偏序关系来决定哪个模板特化的特化程度更高，其中特化程度最高的那个将会被选中。
如果特化程度最高的模板特化不止一个，也就是说，存在多个模板特化，它们的特化程度无法比较高低，那么编译器会报错，实例化失败。
如果没有任何一个模板特化能匹配模板实参，那么主模板被选中。
不严谨地说，“A 的特化程度比 B 高” 意味着 A 接受的参数是 B 接受的参数的子集。

严谨地说，对两个模板特化 A 和 B，编译器首先会将它们转换成两个虚构的函数模板 fa 和 fb，模板特化的形参被转换为函数的形参：

template <typename T, typename U, typename... Args> struct S {};  // primary template
template <typename T, typename U> struct S<T, U> {};              // specialization #A
template <typename T> struct S<T, int> {};                        // specialization #B

// #A is converted to: template <typename T, typename U> void fa(S<T, U>);
// #B is converted to: template <typename T> void fb(S<T, int>);
然后，模板特化 A 和 B 的优先级规则，就被转换为了函数模板重载的优先级规则了。
这个规则就是 Partial Ordering Rule，我们在下一节介绍。
在这里我们看到，通过一个巧妙的转换，特化决议和重载决议对优先级的排序就被归一到了同一个算法里，它们是一致的。

4.4 Partial Ordering Rule
对于两个函数模板 fa 和 fb，怎么判定它们两个谁的特化程度更高呢？这个过程也是一个代入+推导的过程。
为了方便，我们定义一个过程名字就叫“代入推导”(这个名字我自己起的，方便我阐述)，用 fa 代入推导 fb 是指：

记 fb 的模板形参为 T。假设 fa 的模板实参是 U，那么 fa 的函数实参类型(记为A)就可以用 U 来表示出来。
我们用 A 去代入 fb 的函数形参列表(记为P)，并且尝试由此推导 fb 的模板形参 T，这里推导的意思就是尝试用 U 来表示出 T。

如果用 fa 代入推导 fb 成功，并且用 fb 代入推导 fa 失败，那么我们称 fa 比 fb 的特化程度更高。这就是模板的偏序规则。

template<typename T> void foo(T);        // #1
template<typename T> void foo(T*);       // #2
template<typename T> void foo(const T*); // #3

const int* p;
foo(p);   // template augument deduction succeeded for all templates,
          // so overload resolution picks them all.

// partial ordering
// deduce #1 from #2: void(T) from void(U*): P=T, A=U*: deduction ok: T=U*
// deduce #2 from #1: void(T*) from void(U): P=T*, A=U: deduction fails
// #2 is more specialized than #1 with regards to T
// deduce #2 from #3: void(T*) from void(const U*): P=T*, A=const U*: ok
// deduce #3 from #2: void(const T*) from void(U*): P=const T*, A=U*: fails
// #3 is more specialized than #2 with regards to T
// result: #3 is most specialized.
规则有点复杂，我们还是通过例子来理解。我们尝试对比 #1 和 #2 的偏序关系。首先，尝试用 #2 来代入推导 #1，
我们记 #1 的模板形参为 T，并假设给 #2 传入一个实参 U，那么 #1 和 #2 就被表示为这样两个函数模板：

template <typename T>   void foo(T);  // #1
template <typename T=U> void foo(U*); // #2
我们将下面的函数实参 U 代入上面的函数形参，也就是将 #1 写为 template <typename T> void foo(T=U*)，
然后推导T，得出 T=U，代入推导成功。

然后，我们尝试用 #1 来代入推导 #2，我们记 #2 的模板形参为 T，并给 #1 传入一个实参 U，那么 #1 和 #2 就被表示为：

template <typename T=U> void foo(U);  // #1
template <typename T>   void foo(T*); // #2
然后将上面的函数实参 U 代入下面，也就是将 #2 写为 template <typename T> void foo(T*=U)，然后推导T，失败。
所以我们得出结论：#2 的特化程度比 #1 高。

这个规则之所以称为“偏序”规则，是因为函数模板的重载集(或类模板的偏特化集)是一个偏序集合，集合元素之间的关系是偏序关系。
也就是说，并不是任意两个函数模板都是可比较的，有时你无法比较两个模板谁的特化程度更高。
如果从 fa 代入推导 fb 成功，且从 fb 代入推导 fa 成功；或者从 fa 代入推导 fb 失败，且从 fb 代入推导 fa 失败，
那么 fa 和 fb 就被认为是无法比较的，或者说特化程度相同的。例如：

template<typename T> void foo(T, T*);    // #1
template<typename T> void foo(T, int*);  // #2

foo(0, new int(1)); // template augument deduction succeeded for all templates,
                    // so overload resolution picks them all.
// partial ordering:
// #1 from #2: void(T,T*) from void(U1,int*): P1=T, A1=U1: T=U1; P2=T*, A2=int*: T=int; fails
// #2 from #1: void(T,int*) from void(U1,U2*) : P1=T A1=U1: T=U1; P2=int* A2=U2*; fails
// neither is more specialized w.r.t T, the call is ambiguous
在这里两个方向的代入推导操作都失败了，所以重载决议时无法判定哪个的优先级更高，编译器抛出一个歧义错误。

4.5 Template Overloads vs Template Specializations
函数模板既可以重载，又可以(全)特化，它们之间是什么关系呢？特化会不会影响重载呢？

答案是，函数模板的每一个重载都是主模板(Primary Template)，在重载决议的时候，只考虑非模板函数和函数模板的主模板，
模板的特化不在重载集的范畴之内。并且，对于一个函数调用，是先进行重载决议，确定使用哪个主模板，再考虑是否使用该模板的特化。

我们看第一个例子，下面哪一个 foo 会被实例化？

template <typename T> void foo(T);     // #1
template <>           void foo(int*);  // #2
template <typename T> void foo(T*);    // #3
foo(new int(1));  // which one will be called?
答案是 #3。就像我们说的，编译器会在 #1 和 #3 中先进行重载决议，#2 只是 #1 的一个特化，不予考虑。
重载决议选择了 #3，而且 #3 也没有特化，那么就会实例化 #3 这个主模板。
虽然我们能看出来 #2 才是这次调用的一个完美匹配，但很可惜，规则如此。

第二个例子，哪个 foo 会被实例化呢？

template <typename T> void foo(T);     // #1
template <typename T> void foo(T*);    // #3
template <>           void foo(int*);  // #2
foo(new int(1));  // which one will be called?
这个例子只是把 #2 和 #3 调换了一下位置，答案就变了，这次编译器会选择 #2。因为调换了位置之后，#2 变成了 #3 的一个特化了。
这里我们看到，编译器在决定一个模板特化属于哪一个主模板的时候，只会从它已经“看见”的主模板里选择。
在第一个例子中，编译器在为 #2 寻找主模板的时候，还没看见 #3，所以认为它是 #1 的特化。

第三个例子，那个 foo 会被实例化呢？

template <typename T> void foo(T);     // #1
template <>           void foo(int*);  // #2
template <typename T> void foo(T*);    // #3
template <>           void foo(int*);  // #4
foo(new int(1));  // which one will be called?
没错，是#4。

最后，值得说明的是，编译器在重载决议的时候为什么不考虑特化呢？因为模板的特化并不引入一个名字(Name)。
所以在名字查找的时候，模板特化就直接是被忽略的，或者说是和主模板视为一体的，它不是一个独立的名字。
还记得我们在 4.2 Template Arguments Deduction of Class Template 中讲的吗？
类模板的实参推导不考虑其特化，归根结底也是同一个原因：模板的特化并不引入一个名字。
所以我们一定要注意，编译器是按步骤做事的，第一步，名字查找；第二步，实参推导；第三步，重载决议；
第四步，选择特化；第五步，做替换生成实例。

4.6 SFINAE
SFINAE 的全程是：Substitution Failure Is Not An Error，替换失败不是一个错误。
这可能是模板编程中最出名的一个规则了，你可能已经听过。替换失败不是一个错误，什么意思呢？我们将这句话拆分为两半来理解：

Substitution Failure
替换失败是指，如果用实参替换了模板形参后，在模板立即上下文(Immediate Context)中的类型或表达式呈现为非良构(ill-formed)的，
那么这种情形就称为替换失败。
一个类型或表达式“非良构”是指代码违背了语法或语义规则。
立即上下文，非正式地说，就是你在模板的声明里看到的内容。
is Not an Error
在函数模板的实例化中，如果发生替换失败，那么这个函数模板就被无声地从重载集中剔除，编译器继续尝试其他重载，而不会抛出一个错误
在类/变量模板偏特化的实例化中，如果发生替换失败，那么这个特化就被从特化集中剔除，编译器继续尝试其他特化，而不会抛出一个错误
要说明的是，如果每个重载(特化)都发生了替换失败，没有其他重载(特化)可用了，那编译器还是会报错，
但它不会直接报一个 Substitution Failure，而是会告诉你 “No matching function to call”。另外，
前面我们在4.1 Template Arguments Deduction of Function Template中提到的，函数模板实参推导失败的时候也会从重载集剔除，
但这个机制不是 SFINAE。

举个例子来进一步理解 SFINAE：

template <typename T>
typename T::value_type foo(T t) {  // int::value is ill-formed, here is a substitution failure
  T::value_type i; // int::value_type is ill-formed, but here is NOT the immediate context of foo,
}                  // compiler will report an error.
foo(1);
在这个实例化中，有三处地方发生了替换，一个是函数的返回值，一个是函数的形参列表，一个是函数内部的局部变量声明。
在函数的返回值处，替换后构成了 “ill-formed” 的程序，因为 int::value 是一个非法的名字，
但这里是在立即上下文内，所以是一个替换失败。
在局部变量 i 的声明处，替换后也构成了 “ill-formed” 的程序，但这里不在立即上下文内，所以是一个硬错误(Hard Error)。

第二个例子，用以说明 SFINAE 在函数模板重载中的作用：

// 1. SFINAE in function template:

template <typename T> void          foo(T) {}   // #1
template <typename T> void          foo(T*) {}  // #2
template <typename T> T::value_type foo(T) {}   // #3

foo(1);  // SFINAE(int::value_type) in #3,
         // #1 is selected by overload resolution, T is deduced as int

foo(new int(1));  // SFINAE(int*::value_type) in #3,
                  // #2 is selected by overload resolution, T is deduced as int

foo<int&&>(1);    // SFINAE(int&&*) in #2, SFINAE(int&&::value_type) in #3, #1 is selected
在 foo(1) 的实例化中，#3 发生替换失败，从重载集排除，重载决议在 #1 和 #2 中选择了 #1。
在 foo(new int(1)) 的实例化中，#3 发生替换失败，重载决议在 #1 和 #2 中选择 #2。
在 foo<int&&>(1) 中，#2 和 #3 都发生了替换失败，重载决议选择了 #1。

第三个例子，用以说明 SFINAE 在类模板偏特化中的作用：

// 2. SFINAE in class template:

template <typename T, typename U> struct S {};                  // #1
template <typename T> struct S<T, typename T::value_type> {};   // #2

S<int, int>();          // SFINAE in #2, select #1
S<true_type, bool>();   // select #2
S<true_type, int>();    // select #1
在 S<int, int> 的实例化中，#2 发生替换失败，编译器选择主模板 #1 来实例化。
在 S<true_type, bool> 的实例化中，没有替换失败发生，编译器选择 #2。
在 S<true_type, int> 的实例化中，没有替换失败发生，但根据匹配规则，#2 不匹配，所以选择 #1.

4.7 Review of Template Instantiation
最后，我们用学到的知识，回顾一下整个实例化的过程。当一个实例化发生时，编译器：

进行名字查找，找到所有匹配该名字的模板
如果是函数模板，可能会找到一个或多个重载
如果是类/变量模板，应找到唯一一个主模板，否则抛出重定义错误
确定所有的模板实参，需要推导的，通过主模板来推导
对函数模板，如果推导失败，那么这个模板从重载集中剔除
对类/变量模板，如果推导失败，则抛出错误
对函数模板，进行重载决议，决议时只考虑主模板
偏序规则和 SFINAE 在此发挥作用
对确定的主模板和它的特化，选择最匹配的那个
对类/变量模板，因为存在偏特化，偏序规则和 SFINAE 在此发挥作用
对函数模板，只有全特化，直接匹配就行了
对最终选定的主模板或特化进行替换，生成真实代码，放到 POI 中



5. Learn TMP in use (Part II)
5.1 Example 4: SFINAE
本节展示两个基于 SFINAE 的例子，enable_if 和 void_t。

5.1.1 enable_if
假设我们想要这样的函数模板重载，对于整型的参数，匹配第一个模板，这个模板实现一些针对整型参数的逻辑；
对于浮点数型的参数，匹配第二个模板，这个模板实现针对浮点型参数的逻辑。于是我们定义了下面两个函数模板重载：

// The first one is for integral type such as int, char, long...
template <typename INT> void foo(INT) {}
// The second one is for floating point types such as float, double...
template <typename FLT> void foo(FLT) {}    // Error: redefinition!
但是这时我们发现，编译器报告了一个重定义错误，上面两个模板实际上是一模一样的，因为它们的签名完全相同。
我们无法写一个针对参数类型的函数模板重载。唯一的办法是对每一个类型，int, char, long, float, double... 都写一个普通函数重载：

void foo(int)   {}
void foo(char)  {}
void foo(float) {}
// ...
但是这样我们要定义十几个相似的函数，完全失去了泛型编程的支持。这时，我们就需要 enable_if 出马了：

template <bool, typename T = void>
struct enable_if : type_identity<T> {};

template <typename T>
struct enable_if<false, T> {};

template <typename T> enable_if_t<is_integral_v<T>>       foo(T) {}  // #1
template <typename T> enable_if_t<is_floating_point_v<T>> foo(T) {}  // #2
foo(1);     // match #1
foo(1.0f);  // match #2
我们先来看 enable_if 是怎么定义的。首先它是一个类模板，主模板有两个形参，第一个形参接受一个 bool 值，
第二个形参接受一个类型 T 且有一个默认值 void，主模板就返回 T 本身。
另外有一个偏特化，偏特化接受一个类型形参 T，它匹配 bool 值为 false 的情况，但注意，它内部没有定义 “type”！
这就造成一种效果，当我们 “调用” enable_if<bool, T>::type 时，如果 bool 值为 true，那么 enable_if 就返回 T；
而如果 bool 值为 false，enable_if 返回不了任何东西！“type” 不存在，对它的调用构成了一个非良构的(ill-formed)表达式，
只要这个表达式位于立即上下文(Immediate Context)中，那么就会触发 SFINAE 机制！

所以，对于 foo(1)，在函数模板 #2 中，T 被推导为 int，is_floating_point_v<T> 为 false，
所以 enable_if_t<is_floating_point_v<T>> 产生了非良构的实例化表达式。
我们看下这个表达式位于哪里，它位于函数模板 foo 的返回值处，这里是一个立即上下文，
所以这是一个替换失败(Substitution Failure)，函数模板 #2 从重载集中剔除，避免了重定义错误。

foo(1.0f) 也是同理。所以，通过 enable_if(更准确地说是通过 SFINAE)，
我们拥有了基于逻辑来控制函数重载集的能力，而原本的我们仅仅只能基于 C++ 语法规则来控制重载，这就是 TMP 的威力。

我们来看第二个例子，假设我们想通过类模板的形参来控制类模板成员函数的重载：

template <typename T> struct S {
  template <typename U> static enable_if_t< is_same_v<T, int>> foo(U) {}    // #1
  template <typename U> static enable_if_t<!is_same_v<T, int>> foo(U) {}    // #2
};
S<int>::foo(1);
在这里，foo 是 S 的静态成员函数模板，我们希望，当 S 的实参是 int 时，匹配第一个 foo；
当 S 的实参不是 int 时，匹配第二个 foo。
也就是说，我们希望 S<int>::foo(1) 调用的是 #1。但是，我们去编译这段代码却发现编译器报告了错误：

metaprogramming/immediate_context.cpp:44:40:
    error: no type named 'type' in 'enable_if<false>';
    'enable_if' cannot be used to disable this declaration
    using enable_if_t = typename enable_if<B, T>::type;
                                       ^
metaprogramming/immediate_context.cpp:52:10:
    note: in instantiation of template type alias 'enable_if_t' requested here
    static enable_if_t<!is_same_v<int, T>> foo(U) {}
           ^
metaprogramming/immediate_context.cpp:55:14:
    note: in instantiation of template class 'S<int>' requested here
    int main() { S<int>::foo(1.0f); }
我们分析下错误信息，编译器说在实例化 S<int> 的时候，enable_if<false> 里面没有名叫 “type” 的类型。
这不是我们预期的替换失败吗？怎么没有 SFINAE，而是报告了一个错误？
历史经验告诉我们，当编译器和我们的预期不一致时，一般都是我们错了。
那么是哪里搞错了呢？仔细分析我们发现，原来是因为这个 enable_if 不在类模板 S 的立即上下文里！
奇怪，enable_if 不是在 foo 的返回值里的吗？在上个例子里返回值不是立即上下文吗？
注意，foo 的返回值属于立即上下文，是对 foo 来说的。
也就是说，在实例化成员函数模板 foo 的时候，foo 的返回值区域位于立即上下文中。
而我们现在正在实例化 S，只有在 S 的自己的立即上下文内才能使用 SFINAE。

所以我们就没办法通过类模板的实参控制成员函数重载了吗？不是的，有一个巧妙的办法能避免上面的错误。
理论上，我们只需要将 enable_if 的实例化推迟到 foo 的立即上下文中就行了，
让 enable_if 的实例化发生在 foo 实例化的时候，而不是 S 实例化的时候。我们看下面这段代码：

template <typename... Args>
struct always_true : true_type {};

template <typename T> struct S {
  template <typename U> static enable_if_t<always_true_v<U> &&  is_same_v<T, int>> foo(U) {}
  template <typename U> static enable_if_t<always_true_v<U> && !is_same_v<T, int>> foo(U) {}
};

S<int>::foo(1);  // works
我们实现一个无意义的 Metafunction，always_true，它接受任意的参数，然后返回 true。
然后，我们将 always_true_v<U> 放到 enable_if 的实参表达式里，U 是成员函数模板 foo 的形参，
因为 always_true 永远是 true，所以这个合取表达式(&&)和原来的逻辑是一样的。神奇，这样问题就解决了！

我们来解释下原理，在实例化 S<int> 时，编译器用 int 替换 T，第二个 foo 中的 !is_same_v<T, int> 就变为了 false。
但是对于这个合取表达式的剩余部分 always_true_v<U>，其值依赖于模板 foo 的形参 U，
而这个 U 直到 foo 实例化的时候编译器才能确定它的值，所以编译器无法继续对 enable_if_t 求值了，
所以也就没有任何非良构的表达式产生。直到 foo(1) 开始进行实例化的时候，U 被推导为 int，always_true_v<U> 返回 true。
这时 enable_if_t<true && false> 就构成了非良构的，但是因为我们现在位于 foo 的立即上下文中，SFINAE！

另外，就像我们在 3.3.2 is_one_of 中提到的那样，模板的实例化是没有短路求值规则的，
所以这里即使把 always_true_v<U> 放在 !is_same_v<T, int> 的后面，也是可以把 enable_if 的实例化推迟到 foo 实例化之时的。

5.1.2 void_t
如果 enable_if 还没有让你大脑宕机，那试一下 void_t 吧！void_t 的定义如下：

template <typename...> using void_t = void;
看起来是一个很简单的东西，这就是一个别名模板，接受任意的类型形参，不论你传给它什么，它都返回给你一个 void。
这样一个东西能有啥用呢？说出来你可能不信，用它我们可以在 C++ 中实现一个类似 Python 里 hasattr 一样的东西。

假设我们现在想实现这样一个功能，要检查一个 Metafunction 是否遵守了 Metafunction Convention。
也就是说，给一个任意的类型，我们检查它内部是否定义了一个名为 “type” 的名字：

// primary template
template <typename, typename = void> struct has_type_member : false_type {};
// partial specialization
template <typename T> struct has_type_member<T, void_t<typename T::type>> : true_type {};

std::cout << has_type_member_v<int> << std::endl;                // 0, SFINAE
std::cout << has_type_member_v<true_type> << std::endl;          // 1
std::cout << has_type_member_v<type_identity<int>> << std::endl; // 1
我们定义了一个 Metafunction 叫做 has_type_member，它的主模板接受两个参数，第一个参数是一个类型
第二个参数也是一个类型，但默认值置为了 void。
另有一个偏特化，偏特化保留了第一个参数 T，第二个参数期望匹配的是一个 void 类型，
但我们没有直接写 void，而是写了 void_t<typename T::type>。

第一个关键点来了，我们先理解一下偏序规则是怎么在这里发挥作用的，也就是说，什么情况下，会匹配 has_type_member 的偏特化。
对于第二个模板参数，当我们传入 void 时，由于主模板的能匹配任意的类型，而偏特化只匹配 void 类型，所以显然这时会匹配偏特化；
当我们给第二个参数传入非 void 时，由于偏特化不匹配非 void，所以这时会匹配主模板。而重点是，当我们不传第二个参数时，
那么编译器会从该形参的默认实参来确定实参，而默认实参就是 void。
也就是说，当我们不显示指定第二个实参时，模板的偏序规则会优先匹配 has_type_member 的偏特化。

第二个关键点是，在偏特化的第二个特化形参里，并不是直接指定了 void，而是指定的一个 void_t 实例化表达式，
这个表达式是有可能是非良构的！
具体地说，当第一个形参 T 中包含名为 “type” 的成员、且 “type” 是一个类型时，表达式 typename T::type 良构；
而当第一个形参 T 中不包含 “type” 成员或 “type” 不是一个类型时，表达式 typename T::type 非良构。
这个非良构发生在 has_type_member 的形参列表里，属于立即上下文，因此 SFINAE 发挥作用。也就是说，
当 T 中不包含 “type” 类型时，偏特化被剔除，这次实例化只能匹配has_type_member 的主模板。

所以，我们使用 has_type_member 时，只指定一个参数，不指定第二个参数。
效果就是，当第一个参数里包含 “type” 成员时，匹配特化，结果为 true；
当第一个参数里不包含 “type” 成员时，匹配主模板，结果为 false。

最后需要说明一下的是，void_t 与 has_type_member 的实现与 void 没有直接的关系，void 不重要，
重要的是第二个参数的默认实参要和 void_t 的返回类型匹配，从而触发偏序关系选择偏特化模板。
只要遵守这个原理，你可以把 void 换成其他的类型，也一样能实现这个效果。

5.2 Example 5: Unevaluated Expressions
在 C++ 中，有四个运算符，它们的操作数是不会被求值(Evaluate)的，因为这四个运算符只是对操作数的编译期属性进行访问。
[7] 这四个运算符分别是：typeid, sizeof, noexcept, 以及decltype。

std::size_t n = sizeof(std::cout << 42);  // Nothing is outputed
decltype(foo()) r = foo();                // Function foo is called only once.
例如，第一句里的 std::cout << 42 并不会被执行，第二句中的 foo 也只调用了一次，
也就是说，这些运算符的操作数是不会在运行时生效的，它们甚至都不存在了，在编译期间就已经处理掉了。
这些运算符的表达式称为不求值表达式(Unevaluated Expression)，它们的参数所处的区域称为不求值上下文(Unevaluated Context)。

5.2.1 declval
我们先来看不求值表达式的第一个用例，也是最简单的用例。加入我们定义了两个函数模板重载：

template <typename T> enable_if_t<is_integral_v<T>,       int>   foo(T) {}  // #1
template <typename T> enable_if_t<is_floating_point_v<T>, float> foo(T) {}  // #2
第一个模板匹配整型的实参 T，接受一个 T 类型的变量作为函数参数，返回值类型为 int；
第二个模板匹配浮点数类型的实参 T，接受一个 T 类型的变量作为函数参数，返回值类型为 float。
然后，我们定义一个类模板 S，它内部有一个成员 value_，我们希望 value_ 的类型是 S 的形参 T 对应的 foo 重载的返回值类型：

template <typename T> struct S { decltype(foo<T>(??)) value_; };  // What should be put in ??
为了得到 foo 的返回值类型，我们只需要写一个 foo 的调用表达式，然后将这个表达式传入 decltype 运算符，就能得到 foo 的返回值类型。
并且根据我们知道 decltype 是一个不求值运算符，foo 的调用表达式并不会被求值。
但是问题在于，foo 函数接受一个类型为 T 的变量作为参数，我们去哪里创建一个 T 的变量出来呢？况且，在编译期也没变量啊。

巧妙的是，虽然我们不能真正地在编译期创建一个变量，但是在不求值表达式中，我们可以表示出一个“假想的”变量出来，通过 declval：

// We can get a fictional variable by a function template named "declval"
template <typename T> add_rvalue_reference_t<T> declval() noexcept;  // only declaration, no definition!
declval 是一个函数模板，首先我们注意到，它只有声明，没有定义。
因为在不求值上下文中，对这个模板的实例化不会被求值，我们不是真的要创建这个变量，只是要让编译器假设我们有一个这样的变量。
所以 declval 是不能被用在需要求值的地方的，它只能应用在不求值上下文中。
另外，它的返回值类型是 T 的右值引用，add_rvalue_reference 也是一个 Metafunction，它把接受 T，返回 T 的右值引用，
我们下节再介绍 add_rvalue_reference 的实现，现在只需要知道它的功能。有了 declval，我们就可以伪造一个变量传给 foo 了：

template <typename T> struct S { decltype(foo<T>(declval<T>())) value_; };

std::cout << is_same_v<int,   decltype(S<char>().value_)>   << std::endl;    // 1
std::cout << is_same_v<float, decltype(S<double>().value_)> << std::endl;    // 1
declval<T>() 在不求值上下文中，就表示了一个 T 类型的变量。

5.2.2 add_lvalue_reference
结合不求值表达式和 SFINAE，我们能实现更复杂的功能。
还记得 remove_reference 吗？它移除一个类型的引用，现在我们反其道而行之，想实现两个 Metafunction，它们给类型加上引用。
特别地，add_lvalue_reference 给类型加上左值引用，add_rvalue_reference 给类型加上右值引用：

template <typename T>
struct add_lvalue_reference : type_identity<T&> {};

template <typename T>
struct add_rvalue_reference : type_identity<T&&> {};
这两个 Metafunction 很简单，相信大家都能看懂，这段代码看起来似乎以为没什么问题。等等，真的没问题吗？
哦！如果我传入一个 void 会怎样？void 是没有相应的引用类型的，如果 T 是 void，那么将产生一个编译错误！
那怎么办呢，能不能想个办法，当 T 是 void 时就返回 void 本身，而不是尝试返回 void 的引用呢？
emmmm，对 void 进行特殊判断是一个办法，但是万一有别的类型也不支持添加引用呢？我们有一个更好的办法解决这个问题：

namespace detail {

  template <typename T> type_identity<T&> try_add_lvalue_reference(int);
  template <typename T> type_identity<T>  try_add_lvalue_reference(...);

  template <typename T> type_identity<T&&> try_add_rvalue_reference(int);
  template <typename T> type_identity<T>   try_add_rvalue_reference(...);
}

template <typename T>
struct add_lvalue_reference : decltype(detail::try_add_lvalue_reference<T>(0)) {};
template <typename T>
struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) {};

std::cout << is_same_v<char&, add_lvalue_reference_t<char>> << std::endl;    // 1
std::cout << is_same_v<void,  add_lvalue_reference_t<void>> << std::endl;    // 1
我们来解释一下这里的原理。
对 add_lvalue_reference，我们实现两个辅助函数模板：type_identity<T&> detail::try_add_lvalue_reference(int) 和
 type_identity<T> detail::try_add_rvalue_reference(...)。
先看它们的返回值类型，他们的返回值类型一个是 type_identity<T&>， 一个是 type_identity<T>。
而这个返回值类型决定了 add_lvalue_reference 的结果，因为是直接继承过来的。而具体继承哪个呢？取决于重载决议的结果。
当 T=void 时，type_identity<void&> 是一个非良构的表达式，根据 SFINAE，第一个辅助模板被剔除，
所以 add_lvalue_reference 实际继承的是第二个辅助函数模板的返回值，也就是 type_identity<void>，返回 void。
而当 T=char 时，type_identity<char&> 是一个良构的表达式，这时两个函数模板都合法，那么根据偏序规则，
由于第一个函数模板的函数形参类型特化程度更高，更匹配 detail::try_add_lvalue_reference<char>(0) 这个调用，
所以第一个重载被选中，add_lvalue_reference 返回 char&。

可以看到，这种实现方式的思路是，不论 T 能否添加引用，我先假设能，先给它添上引用，反正也不求值，如果没错就最好，错了就 SFINAE。
所以这种实现方式是更通用的，如果除了 void 外，有其他类型也不能添加引用的，这个实现也能覆盖到。
总之思路就是管他行不行，我先试试，不行再说。

5.2.3 is_copy_assignable
同样的思路，我们可以实现一个 Metafunction，来判断一个类型是不是可拷贝赋值的。
类型 T 可以拷贝赋值的意思是，对两个 T 类型的变量 a 和 b，我们可以写表达式：a = b。

参照上面的思路，想知道能不能写 a = b，管他能不能写，我先写出来再说：

template <typename T>
using copy_assign_t = decltype(declval<T&>() = declval<T const&>());
上面 decltype 括号里的就是一个赋值表达式，只不过我们是借助 declval 将它写出来的。
对于一个赋值表达式，等号左边是一个 T& 类型的变量，等号右边是一个 T const& 类型的变量(或者说常量？)，
并且赋值表达式的返回值类型等于等号左边变量的类型，也就是 T&。
如果赋值这句话良构，那么 copy_assign_t 就等于 T&；如果非良构，那么我们只要保证它在立即上下文里就行了，就可以 SFINAE。所以：

template <typename T, typename = void>      // default argument is essential
struct is_copy_assignable : false_type {};

template <typename T>
struct is_copy_assignable<T, void_t<copy_assign_t<T>>> : true_type {};

// S is not copy assignable
struct S { S& operator=(S const&) = delete; };
std::cout << is_copy_assignable_v<int> << std::endl;        // 1
std::cout << is_copy_assignable_v<true_type> << std::endl;  // 1
std::cout << is_copy_assignable_v<S> << std::endl;          // 0
我们把 copy_assign_t<T> 放到 void_t 里，剩下的事情就和你在 has_type_member 里看到的没有区别了。你可以自己尝试推演一下。

最后，你还能在标准库头文件 里找到更多相似的例子，你可以去探索探索。

5.3 Example 6: Applications in Real World
5.3.1 std::tuple
std::tuple 类似于 Python 的 tuple，可以存储多个不同类型的值。
在 Python 这种弱类型的语言中，tuple 并不难理解；但 C++ 是强类型的语言，不同类型的值是如何存储到一个列表的呢？

int i = 1;
auto t = std::tuple(0, i, '2', 3.0f, 4ll, std::string("five"));

std::cout << std::get<1>(t) << std::endl;       // output: 1
std::cout << std::get<5>(t) << std::endl;       // output: five
我们尝试实现一个自己的 tuple，来展示它的实现原理：

// primary template
template <typename... Args>
struct tuple {
  // for class template arguments deduction
  tuple(Args...) {}
};

// partial specialization with recursive inheritance
template <typename T, typename... Args>
struct tuple<T, Args...> : tuple<Args...> {
  tuple(T v, Args... params) : value_(v), tuple<Args...>(params...) {}
  // value of T stores here
  T value_;
};
tuple 的主模板什么都不做，只是定义了一个构造函数，这个构造函数也没有任何逻辑，定义它是为了做类模板实参推导。
tuple 的模板特化实现了一个递归继承，tuple<T, Args...> 继承了 tuple<Args...>，这个递归继承会一直继承到 tuple<>，
这时匹配主模板，递归终止。特化模板定义了一个类型为 T 的成员 value_，也就是说，在递归继承的每一层都存储了一个 value，
每一层的 value 的类型都可以是不同的，这就是 tuple 可以存储不同类型变量的关键。如果你熟悉 C++ 的对象模型，
那么你应该不难理解这些 value 是怎么存储的，它们在一块连续的内存空间内紧密排布，每一层根据其类型占据相应大小的空间。


了解了 tuple 的结构，我们再看下怎么读取 tuple 中的第 N 个元素，我们首先来看下如何获取 tuple 中第 N 个元素的类型：

template <unsigned N, typename Tpl>
struct tuple_element;

template <unsigned N, typename T, typename... Args>
struct tuple_element<N, tuple<T, Args...>>
    : tuple_element<N - 1, tuple<Args...>> {};

template <typename T, typename... Args>
struct tuple_element<0, tuple<T, Args...>> : type_identity<T> {
  using __tuple_type = tuple<T, Args...>;
};
和我们在 example 3.4.2: extent 中做的事情类似，tuple_element 也是对下标 N 做递归，直到 N=0，这时 T 就是第 N 个元素的类型。
但有一点点特别的是，这里除了 tuple_element<>::type 以外，我们还定义了一个 tuple_element<>::__tuple_type，
它代表的是从 N 之后的参数组成的 tuple 类型。
例如，tuple_element<1, tuple<int, float, char>>::__tuple_type 就等于 tuple<float, char>。

int i = 1;
auto t = std::tuple(0, i, '2', 3.0f, 4ll, std::string("five"));
std::cout << std::is_same_v<
               tuple_element<3, decltype(t)>::type,
               float> << std::endl;                                 // output: 1
std::cout << std::is_same_v<
               tuple_element<3, decltype(t)>::__tuple_type,
               tuple<float, long long, std::string>> << std::endl;  // output: 1
然后我们定义一个 get 函数，它直接通过一个类型转换就可以获得 tuple 的第 N 个元素。

template <unsigned N, typename... Args>
tuple_element_t<N, tuple<Args...>>& get(tuple<Args...>& t) {
  using __tuple_type = typename tuple_element<N, tuple<Args...>>::__tuple_type;
  return static_cast<__tuple_type&>(t).value_;
}
因为 tuple 是一层层继承的，所以这里对 t 相当于是一个向上转型，转型后直接返回这一层的 value 就行了。
另外 get 返回的是 value 的左值引用，也就是说 tuple 中的元素是可以修改的。

int i = 1;
auto t = std::tuple(0, i, '2', 3.0f, 4ll, std::string("five"));
i = 0;
std::cout << get<1>(t) << std::endl;  // output: 1
get<1>(t) = 0;
std::cout << get<1>(t) << std::endl;  // output: 0

5.3.2 A Universal json::dumps
本节我们实现一个通用的 json::dumps，它支持将嵌套的 STL 容器序列化为 json 字符串，效果如下：

auto li = std::list<int>{1, 2};
auto tli = std::tuple(li, 3, "hello");
auto mtli = std::map<std::string, decltype(tli)>{{"aaa", tli}, {"bbb", tli}};

std::cout << json::dumps(mtli) << std::endl;    // output: {"aaa":[[1, 2], 3, hello], "bbb":[[1, 2], 3, hello]}
实现原理是使用函数模板重载的递归展开，并且通过 SFINAE 控制模板重载。在下面的实现中，我们优先使用 std 中的 Metafunction。

首先，对于内置的数值类型，我们直接转成 string 返回，这里通过 is_one_of 判定参数类型是不是内置的数值类型：

namespace json {
template <typename T>
std::enable_if_t<
    is_one_of_v<
        std::decay_t<T>,    // std::decay means remove reference, and remove cv
        int, long, long long, unsigned,
        unsigned long, unsigned long long,
        float, double, long double>,
    std::string>
dumps(const T &value) {
  return std::to_string(value);
}
}
std::decay 也是个 Metafunction，类似我们前面讲的 remove_reference，它返回 T 的原始类型，这样无论 T 是引用类型，
还是 const/volatile，都能保证用原始类型和后面的参数进行比较。
通过 std::enable_if，当 dumps 参数的类型不是这些数值类型时，这个模板被从重载集中剔除。

然后对于 std::string 和其他的内置类型，可能要做一些特殊的处理：

namespace json {
// string, char
template <typename T>
std::enable_if_t<is_one_of_v<std::decay_t<T>, std::string, char>, std::string>
dumps(const T &obj) {
  std::stringstream ss;
  ss << '"' << obj << '"';
  return ss.str();
}

// char *
static inline std::string dumps(const char *s) {
  return json::dumps(std::string(s));
}

// void, nullptr
template <typename T>
std::
    enable_if_t<is_one_of_v<std::decay_t<T>, void, std::nullptr_t>, std::string>
    dumps(const T &) {
  return "null";
}

// bool
template <typename T>
std::enable_if_t<is_one_of_v<std::decay_t<T>, bool>, std::string>
dumps(const T &value) {
  return value ? "true" : "false";
}
}
下面就是重头戏了，对于 STL 中的容器，我们要递归地调用 dumps。这里用到了 is_instantiation_of 来判定函数参数是不是容器实例：

namespace json {
// vector, list, deque, forward_list, set, multiset, unordered_set, unordered_multiset
template <template <typename...> class Tmpl, typename... Args>
std::enable_if_t<
        is_instantiation_of_v<Tmpl<Args...>, std::vector> ||
        is_instantiation_of_v<Tmpl<Args...>, std::list> ||
        is_instantiation_of_v<Tmpl<Args...>, std::deque> ||
        is_instantiation_of_v<Tmpl<Args...>, std::forward_list> ||
        is_instantiation_of_v<Tmpl<Args...>, std::set> ||
        is_instantiation_of_v<Tmpl<Args...>, std::multiset> ||
        is_instantiation_of_v<Tmpl<Args...>, std::unordered_set> ||
        is_instantiation_of_v<Tmpl<Args...>, std::unordered_multiset>,
    std::string>
dumps(const Tmpl<Args...> &obj) {
  std::stringstream ss;
  ss << "[";
  for (auto itr = obj.begin(); itr != obj.end();) {
    ss << dumps(*itr);
    if (++itr != obj.end()) ss << ", ";
  }
  ss << "]";
  return ss.str();
}

// map, multimap, unordered_map, unordered_multimap
template <template <typename...> class Tmpl, typename... Args>
std::enable_if_t<
        is_instantiation_of_v<Tmpl<Args...>, std::map> ||
        is_instantiation_of_v<Tmpl<Args...>, std::multimap> ||
        is_instantiation_of_v<Tmpl<Args...>, std::unordered_map> ||
        is_instantiation_of_v<Tmpl<Args...>, std::unordered_multimap>,
    std::string>
dumps(const Tmpl<Args...> &obj) {
  std::stringstream ss;
  ss << "{";
  for (auto itr = obj.begin(); itr != obj.end();) {
    ss << dumps(itr->first);
    ss << ":";
    ss << dumps(itr->second);
    if (++itr != obj.end()) ss << ", ";
  }
  ss << "}";
  return ss.str();
}

// std::pair
template <typename T, typename U>
std::string dumps(const std::pair<T, U> &obj) {
  std::stringstream ss;
  ss << "{" << dumps(obj.first) << ":" << dumps(obj.second) << "}";
  return ss.str();
}
}
对于数组类型，使用到了我们前面提到的 extent，另外 std::is_array 可以判定 T 是不是一个数组。
对于 std::array，直接可以通过模板参数获得数组的长度：

namespace json {
// array
template <typename T>
std::enable_if_t<std::is_array_v<T>, std::string> dumps(const T &arr) {
  std::stringstream ss;
  ss << "[";
  for (size_t i = 0; i < std::extent<T>::value; ++i) {
    ss << dumps(arr[i]);
    if (i != std::extent<T>::value - 1) ss << ", ";
  }
  ss << "]";
  return ss.str();
}

// std::array
template <typename T, std::size_t N>
std::string dumps(const std::array<T, N> &obj) {
  std::stringstream ss;
  ss << "[";
  for (auto itr = obj.begin(); itr != obj.end();) {
    ss << dumps(*itr);
    if (++itr != obj.end()) ss << ", ";
  }
  ss << "]";
  return ss.str();
}
}
对于 std::tuple，由于它的实现原理比较特殊，所以逻辑与其他有一些不同，要写一个基于 tuple 长度 N 的递归展开：

namespace json {
// std::tuple
template <size_t N, typename... Args>
std::enable_if_t<N == sizeof...(Args) - 1, std::string>
dumps(const std::tuple<Args...> &obj) {
  std::stringstream ss;
  ss << dumps(std::get<N>(obj)) << "]";
  return ss.str();
}
template <size_t N, typename... Args>
std::enable_if_t<N != 0 && N != sizeof...(Args) - 1, std::string>
dumps(const std::tuple<Args...> &obj) {
  std::stringstream ss;
  ss << dumps(std::get<N>(obj)) << ", " << dumps<N + 1, Args...>(obj);
  return ss.str();
}
template <size_t N = 0, typename... Args>
std::enable_if_t<N == 0, std::string> dumps(const std::tuple<Args...> &obj) {
  std::stringstream ss;
  ss << "[" << dumps(std::get<N>(obj)) << ", " << dumps<N + 1, Args...>(obj);
  return ss.str();
}
}
对于指针类型，我们可能希望输出它指向的值：

namespace json {
// pointer
template <typename T>
std::string dumps(const T *p) {
  return dumps(*p);
}
// shared_ptr, weak_ptr, unique_ptr
template <typename T>
std::enable_if_t<
    is_instantiation_of_v<T, std::shared_ptr> ||
        is_instantiation_of_v<T, std::weak_ptr> ||
        is_instantiation_of_v<T, std::unique_ptr>,
    std::string>
dumps(const std::shared_ptr<T> &p) {
  return dumps(*p);
}
}
我们定义了很多模板，但这时我们会遇到第一个问题就是名字查找的问题。
如果我们直接把上面这些模板的定义写到头文件里，由于这些函数模板是相互调用的，
例如 json::dumps<std::list<std::map<..., std::list<int>>>>(...) 会先调用 list 对应的 dumps，
再调用 map 对应的 dumps，再调用 list 对应的 dumps，最后调用 int 对应的 dumps；所以这些模板之间的名字查找就存在了顺序依赖。
比如 int 对应的 dumps 必须放在 list 对应的 dumps 之前，以保证 dumps<list> 能查找到 dumps<int>。
但 list 和 map 在这个例子中是相互依赖的，把谁放前面都不行。所以，我们必须先前向声明(Forward Declare)所有的 dumps 模板。
这和函数的前向声明是同一个道理，如果你熟悉名字查找问题的话应该不难理解。
所以虽然我们在 Inclusion Model 中把模板的定义直接放在头文件里，但是模板的声明在某些情况下也是必不可少的。

我们已经处理了内置类型和 STL 中的类型，这时我们遇到的第二个问题就是，对于用户的自定义类型，我们应该怎么处理？
比如一个 vector 里存了一个用户自定义的类型，json::dumps<vector<UserDefine>> 展开以后，怎么处理 UserDefine 的对象？
这里就要用到依赖于实参的名字查找(Argument-dependent Name Lookup, ADL)，
ADL 是指，编译器会去函数实参类型所在的名字空间里去查找函数名字。
所以，我们在定义 UserDefine 类型时，在同一个名字空间内提供一个针对 UserDefine 的 json::dumps 重载即可。
这样，我们在 json.hpp 里定义的对应 vector 参数的函数模板，就也能查找到 UserDefine 的重载了。

namespace user_namespace {

struct UserDefine { int a; };

std::string dumps(const UserDefine &obj) {
  return "ud" + std::to_string(obj.a);
}

}  // namespace user_namespace

using user_namespace::UserDefine;

int main() {
  auto vu = std::vector<UserDefine>{UserDefine{1}, UserDefine{1}};
  auto li = std::list<int>{1, 2};
  auto tvuli = std::tuple(vu, li, 3, "hello");
  auto mtvuli = std::map<std::string, decltype(tvuli)>{{"aaa", tvuli}, {"bbb", tvuli}};
  std::cout << json::dumps(mtvuli) << std::endl;
  // output: {"aaa":[[ud1, ud1], [1, 2], 3, "hello"], "bbb":[[ud1, ud1], [1, 2], 3, "hello"]}
}
这里是 json.hpp 的完整代码。



6. Constraints and Concepts
概念(Concepts)是对模板实参的一些约束(Constraints)的集合，是 C++20 引入的新特性。这些约束可以被用于选择最恰当的函数模板重载和类模板偏特化。相较于传统的技术手段，它的优势有两个：一是语法更简单的同时功能也更强大；二是编译器产生的错误信息更易理解。

在前面我们已经看到了使用 SFINAE 来选择重载和特化的用法了，对比一下我们就可以看到 Concept 的优势：

// with SFINAE:
template <typename T>
static constexpr bool is_numeric_v = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <typename T>
std::enable_if_t<is_numeric_v<T>, void> foo(T);

// with Concept:
template <typename T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <Numeric T>
void foo(T);
另外，由于编译时对约束规则的检查发生在模板的实例化之前，所以此时产生的错误信息更容易理解。特别是当涉及嵌套多层的模板实例化时，错误信息基本没法看。你可以测试一下编译下面这两行代码：

std::list<int> l = {3,-1,10};
std::sort(l.begin(), l.end());
在我的电脑上，它产生的错误信息有472行：

|| /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/algorithm:3961:40: error: invalid operands to binary expression ('std::__1::__list_iterator<int, void *>' and 'std::__1::__list_iterator<int, void *>')
||         difference_type __len = __last - __first;
||                                 ~~~~~~ ^ ~~~~~~~
|| /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/algorithm:4149:12: note: in instantiation of function template specialization 'std::__1::__sort<std::__1::__less<int> &, std::__1::__list_iterator<int, void *>>' requested here
||     _VSTD::__sort<_Comp_ref>(__first, __last, _Comp_ref(__comp));
||            ^
|| /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/algorithm:4157:12: note: in instantiation of function template specialization 'std::__1::sort<std::__1::__list_iterator<int, void *>, std::__1::__less<int>>' requested here
||     _VSTD::sort(__first, __last, __less<typename iterator_traits<_RandomAccessIterator>::value_type>());
||            ^
|| /Users/guoang/test/test.cpp:23:8: note: in instantiation of function template specialization 'std::__1::sort<std::__1::__list_iterator<int, void *>>' requested here
||   std::sort(l.begin(), l.end());
||        ^
|| /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/iterator:855:1: note: candidate template ignored: could not match 'reverse_iterator' against '__list_iterator'
|| operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
|| ^
|| /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/iterator:1311:1: note: candidate template ignored: could not match 'move_iterator' against '__list_iterator'
|| operator-(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
|| ^
|| /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/iterator:1719:1: note: candidate template ignored: could not match '__wrap_iter' against '__list_iterator'
|| operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
|| ^
|| /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/string:560:11: note: candidate template ignored: could not match 'fpos' against '__list_iterator'
|| streamoff operator-(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
||
|| ......
而如果使用支持 Concept 的编译器，报错信息大概长这样：

error: cannot call std::sort with std::_List_iterator<int>
note:  concept RandomAccessIterator<std::_List_iterator<int>> was not satisfied
Concept 的声明语句形如：

template <...>
concept _name_ = _constraint_expression_;
一个约束表达式就是一个对模板形参的逻辑运算表达式(与、或、非)，它指定对于模板实参的要求。例如上面看到的 std::is_integral_v<T> || std::is_floating_point_v<T> 就是一个约束表达式。与模板实例化中的逻辑运算表达式不同，约束表达式中的逻辑运算是短路求值的。约束表达式可以出现在 Concept 的声明中，比如 template <typename T> Numerical = std::is_integral_v<T> || std::is_floating_point_v<T>；也可以出现在 requires 从句中。

requires 关键字用来引入 Requires 从句(Requires Clause)，requires 从句可以放在函数模板的签名里，用来表示约束。requires 关键字后面必须跟一个常量表达式，可以是 true/false，可以是 Concept 表达式、Concept 的合取/析取，也可以是约束表达式，还可以是 requires 表达式。下面的这些写法都是等效的，其中第一个是在形参列表中直接使用 Concept，第二第三个是使用 Concept 的 requires 从句，最后两个是使用约束表达式的 requires 从句：

template <Numeric T>
void foo(T) {}

template <typename T> requires Numeric<T>
void foo(T) {}

template <typename T>
void foo(T) requires Numeric<T> {}

template <typename T> requires std::is_integral_v<T> || std::is_floating_point_v<T>
void foo(T) {}

template <typename T>
void foo(T) requires std::is_integral_v<T> || std::is_floating_point_v<T> {}
requires 关键字还可以用来引入一个 Requires 表达式(Requires Expression)。它是一个 bool 类型的纯右值表达式，描述一些对模板实参的约束。若约束满足(表达式良构)则返回 true；否则返回 false。requires 表达式形如：requires (parameters) { requirement-sequences }。下面是用 requires 表达式来声明 Concept 的例子：

template <typename T> concept Incrementable = requires(T v) { ++v; };
template <typename T> concept Decrementable = requires(T v) { --v; };

template <typename From, typename To>
concept ConvertibleTo = std::is_convertible_v<From, To> &&
    requires(std::add_rvalue_reference_t<From> (&f)()) {
  static_cast<To>(f());
};

template <typename T, typename U = T>
concept Swappable = requires(T&& t, U&& u) {
    swap(std::forward<T>(t), std::forward<U>(u));
    swap(std::forward<U>(u), std::forward<T>(t));
};
另外，有些写法是 requires 表达式独有的，比如下面的 Hashable，它判断 a 能否传给 std::hash，以及 std::hash 的返回值类型能否转型为 std::size_t:

template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> ConvertibleTo<std::size_t>;
};
除了用在 Concept 的声明中外，requires 表达式还可以直接用在 requires 从句中：

template<typename T> concept Addable = requires (T x) { x + x; };  // requires expression

template<typename T> requires Addable<T>   // requires clause
T add(T a, T b) { return a + b; }

template<typename T> requires requires (T x) { x + x; }   // requires expression in requires clause
T add(T a, T b) { return a + b; }
最后，约束出现的顺序决定了编译器检查的顺序，所以下面两个函数模板虽然在逻辑上是等效的，但他们拥有不同的约束，不算是重定义：

template <Incrementable T>
void g(T) requires Decrementable<T> {};

template <Decrementable T>
void g(T) requires Incrementable<T> {};
但是，我在这里更想讨论的，不是 concept 的语法，而是它的意义。concept 虽然最近(C++20)才被写入标准里，但它其实是一个历史非常悠久的东西，可以说它是伴随着泛型编程而生的。concept 其实一直都存在，只是 C++ 直到 C++20 才在语法上支持了 concept。对 concept 的讨论触及元编程的一个核心问题，就是我们为什么需要元编程、什么情况下需要用到元编程。我在 1.4 Why should we Learn TMP？ 中列举了 4 条原因，其中第二条是我们有时需要对类型做计算，我们在这里进一步讨论这个问题。

你可能已经听说过一些 concept，比如 Iterator Categories，标准库中一共有 6 种 Iterator，分别是：InputIterator, OutputIterator, ForwardIterator, BidirectionalIterator, RandomAccessIterator, 和 ContiguousIterator(since C++17)。它们的关系是这样的：


你可能也已经知道标准库中的泛型排序函数 std::sort 只接受 RandomAccessIerator 的迭代器参数:

template< typename RandomIt >
void sort( RandomIt first, RandomIt last );
这里的 RandomAccessIterator 实际上就是一个概念(concept)，它描述了 std::sort 对其参数类型的要求。这样的要求在标准库中有很多，它们被统称为具名要求(Named Requirements)。这些东西本质上都是 concept，但它们早在 concept 的语法出现之前，就已经存在很久了。因为对 concept 的需求是与泛型编程伴生的：我们希望泛型，但又不是完全的泛型，对传入的类型仍有一定的要求。比如 std::sort 就要求它的参数类型是支持随机访问的迭代器，而这个要求是源自于快排算法的，是 std::sort 自身本质的要求，是一种必然的要求。从这个层面来说，C++ 对 concept 的语法的支持，来得太晚了。在没有这种语法支持的时候，我们只能通过类似 enable_if 或者其他比较原始的 TMP 手段来实现对具名要求的检查，concept 语法的出现，大大简化了泛型编程和元编程的难度。

我们再进一步从软件设计的角度讨论这个问题。concept 其实代表了我们在设计中对某一类实体的抽象。假如说我们想实现一种接口与实现分离的设计，接口是统一的，而实现有多种，甚至用户可以自定义实现，传统的做法是怎样的呢？我们会实现一个纯虚的基类 "Interface"，在里面定义所有纯虚的接口，然后所有的实现都继承这个基类，在派生类里提供具体实现。这带来两个问题，一是你必须通过基类指针来操作接口，通过运行时多态的机制访问实现，这是有成本的，而有时候你并不需要在运行时变换实现，在编译时就能确定你想要用哪个实现，但你扔避免不了运行时的成本；二是这种约束太强了，不仅约束了实现类的类型，还约束了所有接口的参数类型和返回值类型。但是有了 concept 后，我们不需要基类，只需要通过 concept 声明一系列对类型和接口的约束就可以了，比如我们可以约束这个类型必须包含一个名为 "work" 的接口，这个接口接受一个数值类型参数，返回一个数值类型参数。所有的实现不论是什么类型，只需要满足这个约束，就可以拿来使用。这种对类型的约束有点像 Python 的 Duck Type：当看到一只鸟走起来像鸭子、游泳起来像鸭子、叫起来也像鸭子，那么这只鸟就可以被称为鸭子。并且这种对接口的约束可以是严格的，也可以是松散的，比如我可以要求一个接口使用 int 型的参数，也可以要求它接受所有数值类型的参数。所以从这个层面来说，concept 的出现对于软件设计也是有积极意义的。

// dynamic polymorphic
struct WorkerInterface {
  virtual int work(int) = 0;
};

struct WorkerImpl : WorkerInterface {
  int work(int) override { return 1; }
};

int do_work(WorkerInterface* w) { return w->work(1); }

// static polymorphic
template <typename T>
concept worker = requires(T a) {
  { a.work(int()) } -> std::same_as<int>;
};

template <worker T>
int do_work(T&& w) { return w.work(1); }



#endif
