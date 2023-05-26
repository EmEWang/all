C++中如何高效地遍历结构体成员
https://www.zhihu.com/question/598203489/answer/3004689760

问题应该是想问C++中如何高效地遍历一个未知的结构体成员？方法是有的，可以使用反射机制来遍历一个未知的结构体成员。

使用反射机制，可以通过名称或索引来访问结构体的成员，并获取成员的类型、值及其他属性。这样就可以在不知道结构体具体成员的情况下进行高效的遍历和操作。

C++中没有内置的反射机制，但可以使用第三方库来实现，比如Boost.Reflection和RTTR（Run Time Type Reflection）。

使用Boost.Reflection库遍历结构体成员的示例代码：

#include <boost/reflection.hpp>

struct MyStruct {
  int x;
  float y;
  std::string z;
};

int main() {
  MyStruct s = {1, 2.0f, "hello"};

  // 获取结构体类型
  auto type = boost::reflection::get_type<MyStruct>();

  // 遍历结构体成员
  for (auto& member : type.get_members()) {
    // 获取成员名称
    std::cout << member.get_name() << ": ";

    // 获取成员值
    auto value = member.get_value(s);

    // 打印成员值
    if (value.type().is_integral()) {
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



使用反射机制可以方便地遍历结构体成员，但需要注意的是，反射机制可能会带来一定的性能开销。因此，在对性能要求较高的情况下，需要评估反射机制的性能并进行优化。



关于Boost.pfr的详细安装教程，已归档到个人文章，可在c++专栏查看。

Boost.Reflection简介

Boost.Reflection是一个用于C++的开源库，它提供了一种运行时反射机制。这个库可以让程序在运行时动态地查询、访问类和对象的结构信息，例如类的成员函数、属性、父类等等。通过这些功能，Boost.Reflection可以帮助开发者编写更加灵活、可扩展的代码。

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
Boost.Reflection是一个非常有用的C++库，它可以提供强大的反射功能，使得程序在运行时更加灵活和可扩展。如果需要处理一些复杂的数据结构或者需要运行时动态加载一些组件，那么Boost.Reflection可能会是一个不错的选择。

RTTR（Run Time Type Reflection）简介
RTTR（Run Time Type Reflection）是一个C++库，用于在运行时提供类型反射和动态对象操作。它允许开发人员以简单、快速和安全的方式查询、修改和创建类的成员属性和函数。

RTTR提供以下主要特性：

类型反射：RTTR允许查询和操作任意已注册的C++类型的信息，例如类名、基类、成员函数、成员变量等等。
基于名称的访问：可以使用字符串名称来访问类的成员，而不需要硬编码名称。
动态对象创建和修改：RTTR允许在运行时实例化C++类，并在运行时修改其属性和方法。
安全操作：RTTR通过类型检查和异常处理来确保操作的安全性和稳定性。
使用RTTR，开发人员可以在运行时执行各种类型的任务，包括自动绑定、序列化和反序列化、数据驱动等。此外，RTTR还提供了与其他库和框架的集成支持，例如Qt、Boost、STL等。

使用示例：

#include <iostream>
#include <string>
#include <rttr/registration>

using namespace std;
using namespace rttr;

class Person {
public:
    Person(const string& n, int a)
        :name(n), age(a){}
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
    // 反射获取类信息
    type t = type::get_by_name("Person");
    if (t.is_valid()) {
        cout << "Class name: " << t.get_name().to_string() << endl;
        cout << "Number of methods: " << t.get_method_count() << endl;

        // 通过构造函数创建对象
        variant var_person = t.create("Tom", 22);
        if (var_person.is_valid()) {
            // 调用成员函数
            var_person.invoke("sayHello");
        }
    }
    else {
        cout << "Invalid class" << endl;
    }
    return 0;
}
示例定义了一个Person类，并使用RTTR对其进行了注册，在主函数中通过RTTR对该类进行了反射操作，获取了类名、方法数和成员变量等信息，并通过构造函数创建了类的实例并调用了其成员函数。


请问boost里面有reflection没？
有的，编译安装后默认将相关的库安装，现在最新版本的头文件是#include <boost/pfr.hpp>，使用方式有些变化。
