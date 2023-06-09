C++对象内存布局
雨乐
雨乐
公众号【高性能架构探索】，中国科学技术大学
114 人赞同了该文章
C++对象内存布局
从事C++开发也有十年多了，开始写点C++相关的文章，算是对自己一个经验的总结吧
了解你所使用的编程语言究竟是如何实现的，对于C++程序员可能特别有意义。

首先，它可以去除我们对于所使用语言的神秘感，使我们不至于对于编译器干的活感到完全陌生；尤其重要的是，了解内存布局，可以使我们在Debug和使用语言高级特性的时候，能够游刃有余。

插一段自己在工作十年时候写的文章，用以记录十年技术历程
技术十年
​mp.weixin.qq.com/s/ifypkq4tsQb8uuqRUqCXgQ

简单非多态的内存布局
class X {
    int     x;
    float   xx;

public:
    X() {}
    ~X() {}

    void printInt() {}
    void printFloat() {}
};

      |                        |
      |------------------------| <------ X 对象内存布局
      |        int X::x        |
      |------------------------|      栈区
      |       float X::xx      |       |
      |------------------------|       |
      |                        |      \|/
      |                        |
      |                        |
------|------------------------|----------------
      |         X::X()         |
      |------------------------|       |
      |        X::~X()         |       |
      |------------------------|      \|/
      |      X::printInt()     |     文本区
      |------------------------|
      |     X::printFloat()    |
      |------------------------|
      |                        |
在本示例中

只有数据成员存储在堆栈中，且其声明顺序或者存储顺序的行为与编译器强相关
所有其他的成员函数（构造函数，析构函数和编译器扩展代码）都进存储在文本段。这些成员函数在被调用的时候，参数列表最前面会默认添加一个对象的this指针
❝ this指针是一个隐含于每一个成员函数中的特殊指针。它是一个指向正在被该成员函数操作的对象，也就是要操作该成员函数的对象。this作用域是在类内部，当对一个对象调用成员函数时，编译程序先将对象的地址赋给this指针，编译器会自动将对象本身的地址作为一个隐含参数传递给函数。也就是说，即使你没有写this指针，编译器在编译的时候也是加上this的，它作为非静态成员函数的隐含形参。被调用的成员函数函数体内所有对类成员的访问，都会被转化为“this->类成员”的方式。
❞
针对第二点，我们类似于：

A x;
x.printInt();
其中，X::printInt()这个行为，在编译器中，将处理为

printInt(const X* this)
那么，x.printInt()调用处理将最终成为

printInt(&x);
对于C++从业者来说，需要一直不断学习，从入门的C++程序设计语言/C++大学教程，提升系列的effective C++等，到深入系列的深度探索C++对象模型，这些书都建议看几遍，无论是底层还是上层实现，都会有更深的了解


计算机必备经典书籍
​mp.weixin.qq.com/s/9ATTDJXyznS5rDq3MWn7gw


经典书籍(免费自取)
同时具有虚函数和静态数据成员的内存布局
class X {
    int         x;
    float       xx;
    static int  count;

public:
    X() {}
    virtual ~X() {}

    virtual void printAll() {}
    void printInt() {}
    void printFloat() {}
    static void printCount() {}
};
其内存布局如下

      |                        |
      |------------------------| <------ X 对象内存布局
      |        int X::x        |
stack |------------------------|
  |   |       float X::xx      |
  |   |------------------------|      |-------|--------------------------|
  |   |         X::_vptr       |------|       |       type_info X        |
 \|/  |------------------------|              |--------------------------|
      |           o            |              |    address of X::~X()    |
      |           o            |              |--------------------------|
      |           o            |              | address of X::printAll() |
      |                        |              |--------------------------|
      |                        |
------|------------------------|------------
      |  static int X::count   |      /|\
      |------------------------|       |
      |           o            |     数据区
      |           o            |       |
      |                        |      \|/
------|------------------------|------------
      |        X::X()          |
      |------------------------|       |
      |        X::~X()         |       |
      |------------------------|       |
      |      X::printAll()     |      \|/
      |------------------------|     文本区
      |      X::printInt()     |
      |------------------------|
      |     X::printFloat()    |
      |------------------------|
      | static X::printCount() |
      |------------------------|
      |                        |
所有非静态数据成员都按照声明的顺序将空间放入堆栈中，与前面的示例顺序相同
静态数据成员将空间放入内存的数据段中。使用范围解析运算符（即::)进行的访问
静态方法进入文本段，并通过作用域解析运算符进行调用
对于virtual关键字，编译器会自动将指向虚函数表的指针（vptr）插入对象内存表示中。通常，虚函数表是在数据段中为每个类静态创建的，但它也取决于编译器的实现
在虚函数表中，第一个条目指向type_info对象
继承对象的内存布局
class X {
    int     x;
    string str;

public:
    X() {}
    virtual ~X() {}

    virtual void printAll() {}
};

class Y : public X {
    int     y;

public:
    Y() {}
    ~Y() {}

    void printAll() {}
};
其内存布局信息如下

      |                              |
      |------------------------------| <------ Y 对象内存布局
      |          int X::x            |
stack |------------------------------|
  |   |              int string::len |
  |   |string X::str ----------------|
  |   |            char* string::str |
 \|/  |------------------------------|      |-------|--------------------------|
      |           X::_vptr           |------|       |       type_info Y        |
      |------------------------------|              |--------------------------|
      |          int Y::y            |              |    address of Y::~Y()    |
      |------------------------------|              |--------------------------|
      |               o              |              | address of Y::printAll() |
      |               o              |              |--------------------------|
      |               o              |
------|------------------------------|--------
      |           X::X()             |
      |------------------------------|       |
      |           X::~X()            |       |
      |------------------------------|       |
      |         X::printAll()        |      \|/
      |------------------------------|     文本区
      |           Y::Y()             |
      |------------------------------|
      |           Y::~Y()            |
      |------------------------------|
      |         Y::printAll()        |
      |------------------------------|
      |      string::string()        |
      |------------------------------|
      |      string::~string()       |
      |------------------------------|
      |      string::length()        |
      |------------------------------|
      |               o              |
      |               o              |
      |               o              |
      |                              |
在继承模型中，基类和数据成员类是派生类的子对象。
编译器会在类的构造函数中生成具有所有重写的虚函数
_vptr所指向的虚函数表的内容，如果派生类中也定义了相同的函数，则表中的地址为派生类的虚函数地址，如果父类中的虚函数，在派生类中没有被重新定义，那么虚函数表中的地址则为父类的虚函数地址


具有多重继承和虚函数的对象的内存布局
class X {
public:
    int     x;

    virtual ~X() {}
    virtual void printX() {}
};

class Y {
public:
    int     y;

    virtual ~Y() {}
    virtual void printY() {}
};

class Z : public X, public Y {
public:
    int     z;

    ~Z() {}
    void printX() {}
    void printY() {}
    void printZ() {}
};
内存布局如下

      |                              |
      |------------------------------| <------ Z 对象内存布局
stack |          int X::x            |
  |   |------------------------------|                  |--------------------------|
  |   |          X:: _vptr           |----------------->|       type_info Z        |
  |   |------------------------------|                  |--------------------------|
 \|/  |          int Y::y            |                  |    address of Z::~Z()    |
      |------------------------------|                  |--------------------------|
      |          Y:: _vptr           |------|           |   address of Z::printX() |
      |------------------------------|      |           |--------------------------|
      |          int Z::z            |      |           |--------GUARD_AREA--------|
      |------------------------------|      |           |--------------------------|
      |              o               |      |---------->|       type_info Z        |
      |              o               |                  |--------------------------|
      |              o               |                  |    address of Z::~Z()    |
      |                              |                  |--------------------------|
------|------------------------------|---------         |   address of Z::printY() |
      |           X::~X()            |       |          |--------------------------|
      |------------------------------|       |
      |          X::printX()         |       |
      |------------------------------|       |
      |           Y::~Y()            |      \|/
      |------------------------------|     文本区
      |          Y::printY()         |
      |------------------------------|
      |           Z::~Z()            |
      |------------------------------|
      |          Z::printX()         |
      |------------------------------|
      |          Z::printY()         |
      |------------------------------|
      |          Z::printZ()         |
      |------------------------------|
      |               o              |
      |               o              |
      |                              |
在多继承层次结构中，创建的虚函数表指针（vptr）的确切数目将为N-1，其中N代表类的个数。
如果尝试使用任何基类指针调用Z类的方法，则它将使用相应的虚虚函数表进行调用。如下例子所示：
Y *y_ptr = new Z;
y_ptr->printY(); // 没问题
y_ptr->printZ(); // 错误，因为Y的虚函数表中没有printZ这个对象
在上面的代码中，y_ptr将指向完整Z对象内类Y的子对象。y_ptr->printY()将最终转化为如下代码：

 ( *y_ptr->_vtbl[ 2 ] )( y_ptr )
虚继承内存布局
class X { int x; };
class Y : public virtual X { int y; };
class Z : public virtual X { int z; };
class A : public Y, public Z { int a; };
其布局如下：

                  |                |
 Y class  ------> |----------------| <------ A 对象内存布局
sub-object        |   Y::y         |
                  |----------------|             |------------------|
                  |   Y::_vptr_Y   |------|      |    offset of X   | // offset(20) starts from Y
 Z class  ------> |----------------|      |----> |------------------|
sub-object        |   Z::z         |             |       .....      |
                  |----------------|             |------------------|
                  |   Z::_vptr_Z   |------|
                  |----------------|      |
 A sub-object --> |   A::a         |      |      |------------------|
                  |----------------|      |      |    offset of X   | // offset(12) starts from Z
 X class -------> |   X::x         |      |----> |------------------|
 shared           |----------------|             |       .....      |
 sub-object       |                |             |------------------|
具有一个或多个虚拟基类的派生类的内存表示形式分为两个区域：不变区域和共享区域。
不变区域内的数据与对象的起始位置保持固定的偏移量，而与后续派生无关。
共享区域包含虚拟基类，并且随后续派生和派生顺序而波动。
总结
了解内存布局，对我们的项目开发会提供很大的便利，比如对coredump的调试

对于从事c++开发的人，本人这些年来，也整理了不少经典书籍，自取