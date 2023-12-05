#ifndef __MODULE1_CPP17_1_H__
#define __MODULE1_CPP17_1_H__

#include <utility>
#include <map>
#include <iostream>
#include <stdio.h>

using namespace std;

// 主要用于测试c++17



// 需要c++17 支持  make CXXFLAGS=-std=c++17
inline void test1_cpp17_1()
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


// 需要c++17 支持  make CXXFLAGS=-std=c++17
inline std::string_view GetStringView()
{
    std::string name = "xunwu";
    return std::string_view(name);  //离开作用域时，name已经被回收销毁
}
inline void test1_cpp17_1_string_view()
{
    #include <string_view> // 头文件
    // std::string_view是一个字符串的视图，视图并不会真正分配存储空间，而只是原始数据的一个只读窗口，
    // 可以认为它是一个内存的观察者。只是拥有一个字符串的查看功能，并不真正的创建或者拷贝字符串。
    // 只是记录原始字符串的起始指针以及字符串的长度，这个结构不会占用太多内存，开销非常小。
    // 比std::string的性能要高很多，因为每个std::string都独自拥有一份字符串的拷贝。
    // 当只是查看字符串的函数中可以直接使用std::string_view来代替

    // std::string_view为什么性能高？
    // 我们一直在强调std::string_view非常高效，原因如下：
    // std::string_view采用享元设计模式，通常以ptr和length的结构来实现，非常轻便。
    // std::string_view上的字符串操作具有和std::string同类操作一致的复杂度。
    // std::string_view中的字符串操作大多数是constexpr的，都可在编译器执行，省去了运行时的复杂度。

    // std::string_view的使用陷阱
    // data()的使用需谨慎
    // data()会返回的是起始位置的字符指针，若以其返回值进行输出打印，会一直输出直到遇到\0结束符。
    // 如果通过一个没有\0的字符数组来初始化一个std::string_view对象，很有可能会出现内存问题，
    // 所以我们在将std::string_view类型的数据传入接收字符串的函数时要非常小心。
    // 要注意引用对象的生命周期
    // std::string_view不持有所指向内容的所有权，所以如果把std::string_view局部变量作为函数返回值，
    // 则在函数返回后，内存会被释放，将出现悬垂指针或悬垂引用。

    // 1 默认构造函数
    // constexpr basic_string_view() noexcept;
    // 2 拷贝构造函数
    // constexpr basic_string_view(const string_view& other) noexcept = default;
    // 3 直接构造，构造一个从s所指向的字符数组开始的前count个字符的视图
    // constexpr basic_string_view(const CharT* s, size_type count);
    // 4 直接构造，构造一个从s所指向的字符数组开始，到\0之前为止的视图，不包含空字符
    // constexpr basic_string_view(const CharT* s);

    // std::string_view foo(std::string("abc"));
    // 这个过程其实包含三步：第一步构造std::string的临时对象a，
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
    std::string_view stringView5 ;
    stringView5 = GetStringView();
    std::cout << "stringView5: " << stringView5 << std::endl;    // stringView6:

    // 成员函数
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

        std::string_view sv2 = sv.substr(0, 5);
        std::cout << "sv2=" << sv2 << " size()=" << sv2.size() << " data()=" << sv2.data() << std::endl;

        // *** std::operator""sv; 表示按照字面值转换为std::string_view
        std::string_view sv3 = "12345\0 678"sv;//或std::string_view sv4("hello\0 zhxilin"sv)
        std::cout << "sv3=" << sv3 << " size()=" << sv3.size() << " data()=" << sv3.data() << std::endl;
        for (size_t i = 0; i < 10; i++)
        {
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wformat"
            printf("sv3[%x]%x ", i, (int)sv3[i]);     // 局部屏蔽-Wformat 警告 或改 sv3[%lx]%x
            #pragma GCC diagnostic pop
        }
        printf("\n");

        std::string_view sv4("hello\0 444");
        std::cout << "sv4=" << sv4 << " size()=" << sv4.size() << " data()=" << sv4.data() << std::endl;

        // sv=hello:111 size()=9 data()=hello:111
        // sv2=hello size()=5 data()=hello:111
        // sv3=12345 678 size()=10 data()=12345
        // sv3[0]31 sv3[1]32 sv3[2]33 sv3[3]34 sv3[4]35 sv3[5]0 sv3[6]20 sv3[7]36 sv3[8]37 sv3[9]38
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





#endif