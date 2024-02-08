#include "cpp17_1.h"



void test1_cpp17_1_template_deduction()
{
    using namespace std;
    // 构造函数模板推导
    {
        pair<int,double> p2(1, 2.2); // before c++17
        pair p(1, 2.2);              // c++17 自动推导
        vector v = {1, 2, 3};        // c++17
    }
}

class Entry {
public:
    void Init() {name_ = "name";age_ = 10;}
    std::string GetName() const { return name_; }
    int GetAge() const { return age_; }
private:
    std::string name_;
    int age_;
};

template <size_t I>
auto get(const Entry& e) {
    if constexpr (I == 0) return e.GetName();
    else if constexpr (I == 1) return e.GetAge();
}

namespace std {
    template<> struct tuple_size<Entry> : integral_constant<size_t, 2> {};
    template<> struct tuple_element<0, Entry> { using type = std::string; };
    template<> struct tuple_element<1, Entry> { using type = int; };
}
void test1_cpp17_1_struct_binding()
{
    using namespace std;
    // 通过结构化绑定，对于pair、tuple、map、数组和结构体等类型，获取相应值会方便很多
    {
        map<int, string> m = {{0, "a"},{1, "b"},};
        for (const auto &[i, s] : m) {cout << i << " " << s << endl;} // 0 a  1 b

        tuple tp(1,"abc");
        auto[i, d] = tp;
        cout << i << " " << d << endl; // 1 abc

        int array[3] = {1, 2, 3};
        auto [a, b, c] = array;
        cout << a << " " << b << " " << c << endl; // 1 2 3

        struct Point {int x;int y;};  // 注意这里的struct的成员一定要是public的
        auto func= []()-> Point {return {1, 2};};
        auto [x, y] = func();
        cout << x << " " << y << endl; // 1 2
    }

    // 结构化绑定还可以改变对象的值，使用引用即可
    {
        std::pair a(1, 2.3f);
        auto& [i, f] = a;
        i = 2;
        cout << a.first << endl; // 2
    }

    // constexpr auto[x, y] = std::pair(1, 2.3f); // ! compile error, 结构化绑定不能应用于constexpr C++20才可以

    {
        // 需要实现相关的tuple_size和tuple_element和get<N>方法。
        Entry e;
        e.Init();
        auto [name, age] = e;
        cout << name << " " << age << endl; // name 10
    }
}

void test1_cpp17_1_if_switch()
{
    auto GetValue = []{return 1;};
    {
        // C++17前if语句需要这样写代码
        int a = GetValue();
        if (a < 101) {std::cout << a << std::endl;} // 1
    }

    {
        // C++17之后可以这样
        // if (init; condition)
        if (int a = GetValue(); a < 101) {std::cout << a << std::endl;}           // 1

        std::string str = "Hi World";
        if (auto [pos, size] = std::pair(str.find("Hi"), str.size()); pos != std::string::npos) {
            std::cout << pos << " Hello, size is " << size << std::endl;  // 0 Hello, size is 8
        }
    }
}

void test1_cpp17_1_if_constexpr()
{
    // if constexpr 是 C++17 引入的一种编译时 if 语句，它允许在编译时进行条件判断。
    // 这意味着编译器会根据条件来优化生成的代码，这通常会带来更高的性能。
    int a= 1;
    double f = 1.1;
    if constexpr(std::is_same_v<decltype(a), int>) std::cout << "int" << std::endl;
    else if constexpr(std::is_same_v<decltype(f), double>)  std::cout << "double" << std::endl;
}

template <typename ... Ts>
auto sum(Ts ... ts) {return (ts + ...);}
void test1_cpp17_1_template_fold()
{
    // C++17引入了折叠表达式使可变参数模板编程更方便
    int i {sum(1, 2, 3, 4, 5)};
    std::cout << i << std::endl; // 15
    std::string a{"hello "};
    std::string b{"world"};
    std::cout << sum(a, b) << std::endl; // hello world
}

void test1_cpp17_1_constexpr_lambda()
{
    // C++17前lambda表达式只能在运行时使用，C++17引入了constexpr lambda表达式，可以用于在编译期进行计算。
    // constexpr函数体不能包含汇编语句、goto语句、label、try块、静态变量、线程局部存储、没有初始化的普通变量，
    // 不能动态分配内存，不能有new delete等，不能虚函数。
    constexpr auto lamb = [] (int n) { return n * n; };
    static_assert(lamb(3) == 9, "a");
}

void test1_cpp17_1_lambda_this()
{
    // 正常情况下lambda表达式中访问类的对象成员变量需要捕获this，但是这里捕获的是this指针，指向的是对象的引用，
    // 正常情况下没问题，但如果多线程情况下，函数的作用域超过了对象的作用域，对象已经被析构了，还访问了成员变量，就会出问题。
    // 所以C++17增加了新特性，捕获*this，不持有this指针，而是持有对象的拷贝，这样生命周期就与对象的生命周期不相关啦。
    struct A {
        int a;
        void func()  {auto f = [this]  {std::cout << a << std::endl;};  f();}
        void func2() {auto f = [*this] {std::cout << a << std::endl;};  f();}
    };
    A a;
    a.func();    // 0
    a.func2();   // 0
}

void test1_cpp17_1_attribute()
{
    // __declspec, attribute , #pragma指示符，给编译器提供额外的信息，来产生优化或特定的代码，也可以给其它开发者提示信息。
    struct A { short f[3]; } __attribute__((aligned(8)));
    void fatal() __attribute__((noreturn));

    // 在C++11和C++14中有更方便的方法
    // [[carries_dependency]] 让编译期跳过不必要的内存栅栏指令
    // [[noreturn]] 函数不会返回
    // [[deprecated]] 函数将弃用的警告
    [[noreturn]] void terminate() noexcept;
    [[deprecated("use new func instead")]] void func();

    // C++17又新增了三个
    // [[fallthrough]]，用在switch中提示可以直接落下去，不需要break，让编译期忽略警告
    // 使得编译器和其它开发者都可以理解开发者的意图。
    int i = 2;
    switch (i) {
        case 1:
            std::cout << 1 << std::endl; // warning
        case 2:
            std::cout << 2 << std::endl;
            [[fallthrough]];      // 警告消除
        case 3:
            std::cout << 3 << std::endl;
        break;
    }
    // 2 3

    // [[nodiscard]] ：表示修饰的内容不能被忽略，可用于修饰函数，标明返回值一定要被处理
    // [[nodiscard]] int func_nodiscard(){return 1};
    // func_nodiscard(); // warning 没有处理函数返回值

    // [[maybe_unused]] ：提示编译器修饰的内容可能暂时没有使用，避免产生警告
    // void func_unused(){};    //
    // [[maybe_unused]] void func_maybe_unused(){}; // 警告消除
    // void func3() {
    //     int x = 1;
    //     [[maybe_unused]] int y = 2; // 警告消除
    // };

}

void test1_cpp17_1_string_convert()
{
    // 新增from_chars函数和to_chars函数
    std::string str{"123456098"};
    int value = 0;
    const auto res = std::from_chars(str.data(), str.data() + 4, value);
    if (res.ec == std::errc()) {
        std::cout << value << ", distance " << res.ptr - str.data() <<std:: endl;
    } else if (res.ec == std::errc::invalid_argument) {
        std::cout << "invalid" << std::endl;
    }
    // 1234, distance 4
    str = std::string("12.34");
    double val = 0;
    // const auto format = std::chars_format::general;
    // res = std::from_chars(str.data(), str.data() + str.size(), value, format);

    str = std::string("xxxxxxxx");
    int v = 1234;
    auto res2 = std::to_chars(str.data(), str.data() + str.size(), v);
    std::cout << str << ", filled " << res.ptr - str.data() << " characters \n";
    // 1234xxxx, filled 4 characters
}

void test1_cpp17_1_variant()
{
    // C++17增加std::variant实现类似union的功能，但却比union更高级，举个例子union里面不能有string这种类型，
    // 但std::variant却可以，还可以支持更多复杂类型，如map等
    std::variant<int, double, std::string> var("hello");
    std::cout << var.index() << std::endl;  // 1
    var = 123;
    std::cout << var.index() << std::endl;  // 0

    // https://zhuanlan.zhihu.com/p/677040577 深入解析 C++17 中的 std::visit：从原理到实践
    // 用了错误的类型去访问 std::variant，会抛出一个 std::bad_variant_access 异常
    // 拿到一个 std::variant 对象时，如何知道它当前存储了哪种类型的值
    // 1手动类型检查通常涉及使用 std::holds_alternative 和 std::get，或者更糟糕的是，使用 std::get_if
    // std::holds_alternative   简单、直观                      不能提取值
    // std::get                 可以直接提取值                   类型错误会抛出异常
    // std::get_if              可以检查和提取值，不会抛出异常    返回指针，需要额外的空指针检查
    std::cout << std::get<int>(var) << std::endl; // 访问存储的值（不安全，需确保类型正确）
    if (auto pval = std::get_if<int>(&var)) {std::cout << *pval << std::endl;}// 安全地访问存储的值
    if(std::holds_alternative<int>(var)) std::cout << std::get<int>(var) << std::endl; // 安全
    // if(std::holds_alternative<double>(var)) std::cout << std::get<double>(var) << std::endl; // 编译失败

    // std::visit 是 C++17 中引入的一个工具，用于访问和操作存储在 std::variant 类型中的数据。
    // template<class Visitor, class... Variants>
    // constexpr visit(Visitor&& vis, Variants&&... vars);
    // Visitor：一个可调用对象，它应该能够接受 Variants 中每种类型的值。它通常是一个重载了 operator() 的结构或类。
    // Variants：一个或多个 std::variant 类型的对象。

    // 1 使用泛型 lambda 表达式
    std::visit([](auto&& arg) {std::cout << "The value is: " << arg << std::endl;}, var);  // The value is: 123
    // 2 使用 if constexpr 和类型萃取
    std::visit([](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, int>) {std::cout << "int: " << arg << std::endl;}
    else if constexpr (std::is_same_v<T, double>) { std::cout << "double: " << arg << std::endl;
    } else {
        static_assert(std::is_same_v<T, std::string>);
        std::cout << "other" << std::endl;
    }
    }, var);                         // int: 123

    // 3 访问者 模式 编写一个访问者函数对象，这个对象会根据 std::variant 当前存储的类型执行不同的操作。
    // 使用 std::visit 调用 VariantVisitor 实例，它会自动选择并调用与 variant 当前存储的类型相匹配的重载函数。
    struct VariantVisitor {
        void operator()(int i) const {std::cout << "处理 int: " << i << std::endl;}
        void operator()(double d) const {std::cout << "处理 double: " << d << std::endl;}
        void operator()(const std::string& s) const {std::cout << "处理 string: " << s << std::endl;}
    };

    var = 10;      std::visit(VariantVisitor(), var); // 输出: 处理 int: 10
    var = 3.14;    std::visit(VariantVisitor(), var); // 输出: 处理 double: 3.14
    var = "hello"; std::visit(VariantVisitor(), var); // 输出: 处理 string: hello

    try {
        var = "world";
        std::string str = std::get<std::string>(var); // 通过类型获取值
        var = 3;
        int i = std::get<0>(var); // 通过index获取对应值
        std::cout << str << std::endl;  // world
        std::cout << i <<   std::endl;  // 3
    } catch(...) {
        // xxx;
    }

    // 一般情况下variant的第一个类型一般要有对应的构造函数，否则编译失败
    struct A {A(int i){}};
    struct B {B(){}};
    // std::variant<A, int> var2;    // 编译失败
    std::variant<B, int> var21;      // 编译成功
    std::variant<int, A, int> var22; // 编译成功
    std::variant<std::monostate, A> var23; // 编译成功  使用std::monostate来打个桩，模拟一个空状态
}

void test1_cpp17_1_optional()
{
    // 有时候可能会有需求，让函数返回一个对象
    // struct A {};
    // A func() {
    //     if (flag) return A();
    //     else {
            // 异常情况下，怎么返回异常值呢，想返回个空呢
    //     }
    // }
    // 一是返回对象指针，异常情况下就可以返回nullptr啦，但是这就涉及到了内存管理，也许你会使用智能指针，
    // 但这里其实有更方便的办法就是std::optional。
    auto func = [](const std::string &s)->std::optional<int>{
        try {
            return std::stoi(s);
        }
        catch(...) {
            return std::nullopt;
        }
    };
    std::string s{"123"};
    std::optional<int> o = func(s);
    if (o) std::cout << *o << std::endl;     // 123
    else std::cout << "error" << std::endl;

    o = func("abc");
    if (o) std::cout << *o << std::endl;
    else std::cout << "error" << std::endl;  // error
}

void test1_cpp17_1_any()
{
    // C++17引入了any可以存储任何类型的单个值
    std::any a = 1;
    std::cout << a.type().name() << " " << std::any_cast<int>(a) << std::endl; // i 1
    a = 2.2f;
    std::cout << a.type().name() << " " << std::any_cast<float>(a) << std::endl; // f 2.2
    if (a.has_value()) {std::cout << a.type().name() << std::endl;} // f
    a.reset();
    if (a.has_value()) {std::cout << a.type().name() << std::endl;}
    a = std::string("a");
    std::cout << a.type().name() << " " << std::any_cast<std::string>(a) << std::endl; // NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE a
}

int add(int first, int second) { return first + second; }
auto add_lambda = [](auto first, auto second) { return first + second; };
void test1_cpp17_1_apply()
{
    // 使用std::apply可以将tuple展开作为函数的参数传入
    std::cout << std::apply(add, std::pair(1, 2)) << '\n';  // 3
    // std::cout << add(std::pair(1, 2)) << "\n"; // error
    std::cout << std::apply(add_lambda, std::tuple(2.0f, 3.0f)) << '\n';  // 5
}

void test1_cpp17_1_make_from_tuple()
{
    // 使用make_from_tuple可以将tuple展开作为构造函数参数
    struct Foo {
        Foo(int first, float second, int third) {
            std::cout << first << ", " << second << ", " << third << "\n";
        }
    };
    auto tuple = std::make_tuple(42, 3.14f, 0);
    Foo f = std::make_from_tuple<Foo>(std::move(tuple));
}

void test1_cpp17_1_as_const()
{
    // C++17使用as_const可以将左值转成const类型
    std::string str = "str";
    const std::string& constStr = std::as_const(str);
}

void test1_cpp17_1_file_system()
{
    // C++17正式将file_system纳入标准中，提供了关于文件的大多数功能，基本上应有尽有
    namespace fs = std::filesystem;
    // fs::create_directory(dir_path);
    // fs::copy_file(src, dst, fs::copy_options::skip_existing);
    // fs::exists(filename);
    // fs::current_path(err_code);
}

void test1_cpp17_1_shared_mutex()
{
    // C++17引入了shared_mutex，可以实现读写锁
}

std::string_view GetStringView(){
    std::string name = "xunwu";
    return std::string_view(name);  //离开作用域时，name已经被回收销毁
}
void test1_cpp17_1_string_view()
{
    // std::string_view是一个字符串的视图，并不会真正分配存储空间，而只是原始数据的一个只读窗口，一个内存的观察者。
    // 它只拥有原始字符串的查看功能，只是记录起始指针和长度，并不创建或者拷贝字符串，结构内存占用小，开销小，性能高。

    // 1 data()谨慎使用
    // 返回的是起始位置的字符指针，若以其返回值进行输出打印，会一直输出直到遇到\0结束符。
    // 没有\0的字符数组来初始化它，可能会出现内存问题，将之传入接收字符串的函数时要小心。
    // 2 注意引用对象的生命周期
    // 不持有所指向内容的所有权，把局部变量作为函数返回值，将出现悬垂指针或悬垂引用。

    // constexpr basic_string_view() noexcept;                      // 默认构造函数
    // constexpr basic_string_view(const string_view& other) noexcept = default; // 拷贝构造函数
    // constexpr basic_string_view(const CharT* s, size_type count);// 直接构造，s指向的字符数组前count个字符的视图
    // constexpr basic_string_view(const CharT* s);    // 直接构造，s指向的字符数组开始，到\0为止的视图，不包含空字符

    // std::string_view foo(std::string("abc"));  这个过程其实包含三步
    // 第一步构造std::string的临时对象a，
    // 第二步通过转换操作符将临时对象a转换为string_view类型的临时对象b，
    // 第三步调用std::string_view的拷贝构造函数。

    const char* cstr = "abc123";
    std::string_view stringView1(cstr);
    std::string_view stringView2(cstr, 4);
    std::cout << "stringView1: " << stringView1 << std::endl;    // stringView1: abc123
    std::cout << "stringView2: " << stringView2 << std::endl;    // stringView2: abc1

    std::string str = "abc123";
    std::string_view stringView3(str);
    std::string_view stringView4(stringView3);
    std::cout << "stringView3: " << stringView3 << std::endl;    // stringView3: abc123
    std::cout << "stringView4: " << stringView4 << std::endl;    // stringView4: abc123

    // 在查看std::string_view的同时修改了字符串，或者字符串被消毁，那么将是未定义的行为。
    std::string_view stringView5 = GetStringView();
    std::cout << "stringView5: " << stringView5 << std::endl;    // stringView6:

    // 1 迭代器
    // begin()和cbegin() end()和cend() rbegin()和crbegin() rend()和crend()
    // 这些成员函数与std::basic_string的相同成员函数完全兼容，可以认为是对其调用的一层封装。
    // 2 元素访问
    // operator[] at() front() back() data()
    // 返回指向底层字符串数组的指针，该指针满足范围[data(), data() + size())，且其中的值与视图的值对应。
    // 不同于std::basic_string::data()和字符串字面量，data()可以返回指向非空终止的缓冲区的指针。
    {
        std::string_view sv("hello:111");
        std::cout << "sv=" << sv << " size()=" << sv.size() << " data()=" << sv.data() << std::endl;
        // sv=hello:111 size()=9 data()=hello:111
        std::string_view sv2 = sv.substr(0, 5);
        std::cout << "sv2=" << sv2 << " size()=" << sv2.size() << " data()=" << sv2.data() << std::endl;
        // sv2=hello size()=5 data()=hello:111

        using namespace std;    // sv 需要
        // ! *** std::operator""sv; 表示按照字面值转换为std::string_view
        std::string_view sv3 = "12345\0 678"sv;//或std::string_view sv4("hello\0 zhxilin"sv)
        std::cout << "sv3=" << sv3 << " size()=" << sv3.size() << " data()=" << sv3.data() << std::endl;
        // sv3=12345 678 size()=10 data()=12345
        for (size_t i = 0; i < 10; i++)
        {
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wformat"
            printf("sv3[%x]%x ", i, (int)sv3[i]);     // 局部屏蔽-Wformat 警告 或改 sv3[%lx]%x
            #pragma GCC diagnostic pop
        }
        printf("\n");// sv3[0]31 sv3[1]32 sv3[2]33 sv3[3]34 sv3[4]35 sv3[5]0 sv3[6]20 sv3[7]36 sv3[8]37 sv3[9]38

        std::string_view sv4("hello\0 444");
        std::cout << "sv4=" << sv4 << " size()=" << sv4.size() << " data()=" << sv4.data() << std::endl;
        // sv4=hello size()=5 data()=hello

        // 从运行结果可以看出，data()会返回的是起始位置的字符指针（const char*），
        // 以data()返回值进行打印会一直输出直到遇到空字符。因此使用data()需要非常小心。
    }

    // 3 容量
    // size() length() max_size() 返回可以容纳的最大长度 empty()
    // 4 修改器
    // remove_prefix() 视图的起始位置向后移动n位，收缩视图大小
    // remove_suffix() 视图的结束位置向前移动n位，收缩视图大小
    // swap()
    {
        std::string str = "   hello";
        std::string_view v = str;
        std::string_view v2 = str;
        v.remove_prefix(std::min(v.find_first_not_of(" "), v.size()));
        v2.remove_prefix(2);
        std::cout << "str:'" << str << "' v:'" << v << "'" << std::endl;
        std::cout << "str:'" << str << "' v2:'" << v2 << "'" << std::endl;
        // str:'   hello' v:'hello'
        // str:'   hello' v2:' hello'
    }
    // 5 其他操作
    // size_type copy(CharT* dest, size_type count, size_type pos = 0) const;
    //   拷贝子串[pos, pos + rcount)到dest所指向的字符序列中，其中rcount = min(count, size() - pos)。
    //   如果pos > size()，则会抛出std::out_of_range异常。
    // constexpr basic_string_view substr(size_type pos = 0, size_type count = npos ) const;
    //   返回子串[pos, pos + rcount)的视图，其中rcount = min(count, size() - pos)，
    //   不同于std::string::substr()的时间复杂度O(n)，它的时间复杂度是O(1)。
    //   如果pos > size()，则会抛出std::out_of_range异常。

// compare() 比较
// constexpr int compare(basic_string_view v) const noexcept;
// constexpr int compare(size_type pos1, size_type count1, basic_string_view v) const;
//等价于substr(pos1, count1).compare(v)
// constexpr int compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const;
//等价于substr(pos1, count1).compare(v.substr(pos2, count2))
// constexpr int compare(const CharT* s) const;
//等价于compare(basic_string_view(s))
// constexpr int compare(size_type pos1, size_type count1, const CharT* s) const;
//等价于substr(pos1, count1).compare(basic_string_view(s))
// constexpr int compare(size_type pos1, size_type count1, const CharT* s, size_type count2) const;
//等价于substr(pos1, count1).compare(basic_string_view(s, count2))

// 比较两个视图是否相等。令rlen = min(size(), v.size())，该函数通过调用traits::compare(data(), v.data(), rlen)比较两个视图：
// a) traits::compare(data(), v.data(), rlen) < 0时，*this小于v，返回值 < 0
// b) traits::compare(data(), v.data(), rlen) == 0时，
// 若size() < v.size()，则*this小于v，返回值 < 0
// 若size() == v.size()，则*this等于v，返回值为0
// 若size() > v.size()，则*this大于v，返回值 > 0
// c) traits::compare(data(), v.data(), rlen) > 0时，*this大于v，返回值 > 0
    {
        using std::operator""sv;
        static_assert("abc"sv.compare("abcd"sv) < 0);
        static_assert("abcd"sv.compare("abc"sv) > 0);
        static_assert("abc"sv.compare("abc"sv) == 0);
        static_assert(""sv.compare(""sv) == 0);
    }

// starts_with() (C++20)  判断视图是否以以给定的前缀开始。
// constexpr bool starts_with(basic_string_view sv) const noexcept;
// constexpr bool starts_with(CharT c) const noexcept;
// constexpr bool starts_with(const CharT* s) const;

// ends_with() (C++20)    判断视图是否以给定的后缀结尾。
// constexpr bool ends_with(basic_string_view sv) const noexcept;
// constexpr bool ends_with(CharT c) const noexcept;
// constexpr bool ends_with(const CharT* s) const;

// contains() (C++23)     判断视图是否包含给定的子串。
// constexpr bool contains(basic_string_view sv) const noexcept;
// constexpr bool contains(CharT c) const noexcept;
// constexpr bool contains(const CharT* s) const;

// find()                 返回首次出现给定子串的位置。
// constexpr size_type find(basic_string_view v, size_type pos = 0) const noexcept;
// constexpr size_type find(CharT ch, size_type pos = 0) const noexcept;
// constexpr size_type find(const CharT* s, size_type pos, size_type count) const;
// constexpr size_type find(const CharT* s, size_type pos = 0) const;


// rfind()                返回最后一次出现给定子串的位置。
// constexpr size_type rfind(basic_string_view v, size_type pos = npos) const noexcept;
// constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept;
// constexpr size_type rfind(const CharT* s, size_type pos, size_type count) const;
// constexpr size_type rfind(const CharT* s, size_type pos = npos) const;

// find_first_of()        返回首次出现给定子串中任意一个字符的位置。
// constexpr size_type find_first_of(basic_string_view v, size_type pos = 0) const noexcept;
// constexpr size_type find_first_of(CharT c, size_type pos = 0) const noexcept;
// constexpr size_type find_first_of(const CharT* s, size_type pos, size_type count) const;
// constexpr size_type find_first_of(const CharT* s, size_type pos = 0) const;

// find_last_of()         返回最后一次出现给定子串中任意一个字符的位置。
// constexpr size_type find_last_of(basic_string_view v, size_type pos = npos) const noexcept;
// constexpr size_type find_last_of(CharT c, size_type pos = npos) const noexcept;
// constexpr size_type find_last_of(const CharT* s, size_type pos, size_type count) const;
// constexpr size_type find_last_of(const CharT* s, size_type pos = npos) const;

// find_first_not_of()    返回首次出现不在给定子串中全部字符的位置。
// constexpr size_type find_first_not_of(basic_string_view v, size_type pos = 0) const noexcept;
// constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const noexcept;
// constexpr size_type find_first_not_of(const CharT* s, size_type pos, size_type count) const;
// constexpr size_type find_first_not_of(const CharT* s, size_type pos = 0) const;

// find_last_not_of()     返回最后一次出现不在给定子串中全部字符的位置。
// constexpr size_type find_last_not_of(basic_string_view v, size_type pos = npos) const noexcept;
// constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept;
// constexpr size_type find_last_not_of(const CharT* s, size_type pos, size_type count) const;
// constexpr size_type find_last_not_of(const CharT* s, size_type pos = npos) const;
}

