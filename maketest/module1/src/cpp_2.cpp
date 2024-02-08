#include "cpp_2.h"

int g_i = 1;
// using namespace std;
void test1_cpp_2_iterator()
{
    using namespace std;
    // STL 中有五种主要的迭代器类型，它们分别是：
    //   输入迭代器（Input Iterators）: 这种迭代器用于从容器中读取数据。它只支持单向遍历，即只能向前移动（通过 ++ 操作符）。输入迭代器只能进行一次读取，读取后迭代器就会前进到下一个元素。
    //   输出迭代器（Output Iterators）: 与输入迭代器相反，输出迭代器用于向容器中写入数据。它同样只支持单向遍历，且只能进行一次写入操作，写入后迭代器会自动前进到下一个位置。
    //   前向迭代器（Forward Iterators）: 前向迭代器类似于输入和输出迭代器，但它支持多次读写操作。它也只能单向遍历，但可以对同一个元素进行多次访问。
    //   双向迭代器（Bidirectional Iterators）: 如其名，双向迭代器可以在容器中向前和向后移动。它扩展了前向迭代器的功能，使得迭代器可以使用 -- 操作符向前移动。双向迭代器在像 list 和 set 这样的容器中非常有用。
    //   随机访问迭代器（Random Access Iterators）: 这是最强大的迭代器类型，它支持所有前面提到的迭代器的功能，并且能够进行随机访问。这意味着除了能够向前和向后移动，随机访问迭代器还能够直接跳跃到任意位置（如通过 + 或 - 操作符）。vector 和 deque 容器提供了随机访问迭代器。
    // 迭代器失效指的是当容器发生变化时，之前获取的迭代器不再指向有效的元素或者不再有意义，这种情况在 C++ STL 编程中比较常见。迭代器失效主要发生在以下几种情况：
    //   元素被删除或修改: 如果你删除了某个迭代器所指向的元素，那么这个迭代器就失效了。例如，在使用 vector 或 list 的 erase 方法删除元素后，指向被删除元素的迭代器会失效。
    //   容器被重新分配: 对于某些容器（如 vector），如果容量被重新分配（比如在添加元素时容量不足以容纳更多元素），那么指向容器内元素的所有迭代器、引用和指针都将失效。
    //   插入元素: 对于某些容器，如 vector 和 deque，在中间位置插入元素可能会导致指向插入位置之后元素的迭代器失效。
    // 应对迭代器失效
    //   谨慎操作: 在修改容器时，要小心处理迭代器。比如，在删除元素后，不要使用指向被删除元素的迭代器。
    //   更新迭代器: 某些操作（如 insert 和 erase）会返回一个新的迭代器，指向特定的元素。可以使用这些新的迭代器来继续操作。
    //   避免在循环中修改容器: 尽量避免在遍历容器的同时对其进行修改。如果需要这样做，可以使用新的迭代器来代替之前的迭代器。

    vector<string> vct1;
    vector<int> vct2;
    list<int> lst1;
    list<int> lst2;

    for (int i = 1; i < 9; ++i)
    {
        lst1.push_back(i);
    }
    auto func = [](list<int> lst)
    {
        for( auto it1 : lst) // for each( auto it1 : lst)  //错误
        {
            cout << it1 << " ";
        }
        cout << endl;
    };

    vct1.push_back("ab");
    vct1.push_back("cd");
    vct1.push_back("ef");
    auto it = vct1.begin();
    cout << *it << endl;

    vct2.push_back(1);
    vct2.push_back(2);
    vct2.push_back(3);
    auto it2 = vct2.begin();
    cout << *it2 << endl;   //cout << it2 << endl;    //错误

    func(lst1);

    list<int>::iterator it3 = lst1.begin();
    // auto it3 = lst1.begin();
    *(it3) = 11;     //it3 = 11；  // 错误
    cout << *it3 << endl;

    lst2.clear();
    copy_if(lst1.begin(), lst1.end(), back_inserter(lst2), bind2nd(greater<int>(), 5));   // > 5
    func(lst2);

    lst2.clear();
    copy_if(lst1.begin(), lst1.end(), back_inserter(lst2), not1(bind2nd(greater<int>(), 5)));  // <=5
    func(lst2);

    lst2.clear();
    copy_if(lst1.begin(), lst1.end(), back_inserter(lst2), bind2nd(modulus<int>(), 2));        // 奇数
    func(lst2);
}
#include <iterator>    // ostream_iterator istream_iterator
void test1_cpp_2_ostream_iterator()
{
    using namespace std;
    std::ostream_iterator<int> ostr(cout, " ");
    *ostr = 1;
    ++ostr;               // 要不要都一样 无实际意义
    *ostr = 2;
    *ostr = 3;
    cout << endl;

    typedef list<int> lstType; // 重命名一种类型
    // typedef typename list<int> lstType; // 重命名一种类型  vs2019上这么写

    list<int> lst;
    for (int i =1; i < 5; ++i)
    {
        lst.push_back(i);
    }

    copy(lst.begin(), lst.end(), ostr);
    cout << endl;

    copy(lst.begin(), lst.end(), ostream_iterator<lstType::value_type>(cout, " < ")); // value_type必须使用类型 ::
    cout << endl;
}
void test1_cpp_2_transform()
{
    using namespace std;
    list<string> lst;
    //generate_n(lst.begin(), )
    for (int i = 0; i < 5; ++i)
    {
        char temp[22];
        sprintf(temp, "%d", i);
        // sprintf_s(temp, "%d", i);   // vs2019
        lst.push_back(temp);
    }
    copy(lst.begin(), lst.end(), ostream_iterator<string>(cout, "\n"));
    cout << endl;
    transform(lst.begin(), lst.end(), lst.begin(), [](string& str) {return "GigabitE1/0/" + str + "_GigabitEthernet1/0/" + str + " Interface"; });
    copy(lst.begin(), lst.end(), ostream_iterator<string>(cout, "\n"));
    cout << endl;

    string str2 = "1;2;44;55;66";
    list<string> lst2;
    lst2.push_back("1");
    lst2.push_back("2");
    lst2.push_back("33");
    lst2.push_back("44");
    vector<int> vct2;
    transform(lst2.begin(), lst2.end(), back_inserter(vct2), [](string str) {return atoi(str.c_str()); });
    copy(vct2.begin(), vct2.end(), ostream_iterator<int>(cout, "\n"));
    cout << endl;
}
void test1_cpp_2_lamda()
{
    // 格式 [captrue] (params) mutable noexcept/throw() ->ret{ body };
    // 其中 capture是捕获列表；params是参数列表；mutable noexcept/throw()是函数选项；ret是返回值类型；body是函数体。
    {
        // lambda表达式的返回值通过返回值后置语法来定义，很多时候可以省略返回值类型，编译器根据return语句自动推导。
        auto f1 = [](int a) {return a + 1; };   //ok,return type is int
        // 但是初始化列表不能作为返回值的自动推导，需要显示给出具体的返回值类型。
        // auto f2_ = []() {return { 1,2 }; };       //error:无法推导出返回值类型
        // lambda表达式在没有参数列表的时候，参数列表可以省略。
        auto f3 = []() {return 1; };
        auto f4 = [] {return 1; }; // 省略空参数表 可省略()

        // mutable可以省略，如果使用则之前的 () 小括号将不能省略（参数个数可以为 0）。
        // 按值捕获 不允许在lambda表达式内修改其值，可以理解为这部分变量都是 const 常量，如要修改，必须使用 mutable 关键字。
        // 注意的是，这里修改的仅是拷贝的那一份的值，真正外部变量的值并不会发生改变。
        // 全局变量可以访问甚至修改 可以不用mutable
        int i =1;
        auto f5 = [=]()mutable{i+=1;}; // mutable 不能省略
        auto f6 = [=](){g_i+=1;};

        // noexcept/throw() 可以省略，如果使用，在之前的 () 小括号将不能省略（参数个数可以为 0）。
        // 默认情况下，lambda 函数体中可以抛出任何类型的异常。而标注 noexcept 关键字，则表示函数体内不会抛出任何异常；
        // 使用 throw() 可以指定 lambda 函数内部可以抛出的异常类型。
        // 标有 noexcept 而函数体内抛出了异常，或使用 throw() 限定了异常类型而函数体内抛出了非指定类型的异常，
        // 这些异常无法使用 try-catch 捕获，会导致程序执行失败。
        // auto except1 = []() throw(int){throw 10;};  //  ISO C++17 does not allow dynamic exception specifications
        auto except1 = []() {throw 10;};
        // auto except2 = []()noexcept{throw 100;}; // 调用崩溃 warning: throw will always call terminate() [-Wterminate]
        // auto except3 = []()throw(char){throw 10;};
        auto except3 = [](){throw 10;};
        try {except1();}
        catch (int) {std::cout << "捕获到了整形异常1\n";}
        try {
            // except2();
            except3();
        }
        catch (int) {std::cout << "捕获到了整形异常2\n";}

        // -> 返回值类型 指明 lambda 匿名函数的返回值类型。值得一提的是，如果 lambda 函数体内只有一个 return 语句，
        // 或者该函数返回 void，则编译器可以自行推断出返回值类型，此情况下可以直接省略-> 返回值类型。
    }

    // lambda表达式可以通过捕获列表捕获一定范围内的变量：
    // []不捕获任何变量；
    // [&]捕获外部作用域所有变量，并作为引用在函数体使用（按引用捕获）；
    // [=]捕获外部作用域作用变量，并作为副本在函数体使用（按值捕获）；
    // [=, &foo]按值捕获外部作用域所有变量，并按引用捕获foo变量；
    // [bar]按值捕获bar变量，同时不捕获其他变量；
    // [this]捕获当前类中的this指针，让lambda拥有和当前类成员函数同样的访问权限，如果已经使用了& 或者 = ，就默认添加此选项。
    //   捕获this的目的是可以在lambda中使用当前类的成员函数和成员变量。C20有更新见下
    {
        int a = 0, b = 2;
        //auto f1 = [] {return a; };                // error,没有捕获外部变量
        auto f2 = [&] {return a++; };               // ok,按引用捕获所有外部变量，并对a执行自加运算
        auto f3 = [=] {return a; };                 // ok,按值捕获所有外部变量，并返回a
        //auto f4 = [=] {return a++; };             // error,按值引用不能改变值
        //auto f5 = [a] {return a + b; };           // error,没有捕获b
        auto f6 = [a, &b] {return a + (b++); };     // ok,捕获a和b的值，并对b做自加运算
        auto f7 = [=, &b] {return a + (b++); };     // ok,捕获所有外部变量和b的引用，并对b做自加运算
    }

    class A
    {
    public:
        int mi = 0;

        void func(int x, int y)
        {
            // auto x1 = [] {return mi; };                     // error,没有捕获外部变量
            // ! https://stackoverflow.com/questions/54060011/deprecated-lambda-capture-in-c20
            // warning: implicit capture of ‘this’ via ‘[=]’ is deprecated in C++20 [-Wdeprecated]
            // [=]  -> [=, this]   隐式捕获this 20以后会有警告 推荐显示捕获this
            auto x2 = [=, this] {return mi + x + y; };         // ok，按值捕获所有外部变量
            // auto x2 = [=] {return mi + x + y; };            // ok，按值捕获所有外部变量  vs2019
            auto x3 = [&] {return mi + x + y; };               // ok,按引用捕获所有外部变量
            auto x4 = [this] {return mi; };                    // ok,捕获this指针
            //auto x5 = [this] {return mi + x + y; };          // error，没有捕获x,y
            auto x6 = [this, x, y] {return mi + x + y; };      // ok，捕获this，x，y
            auto x7 = [this] {return mi++; };                  // ok,捕获this指针，并修改成员的值
        }
    };

    {
        // lambda表达式其实是一个带有operator()的类，即仿函数，因此可以使用std::bind和std::function来存储和操作lambda表达式
        std::function<int(int)> f1 = [](int a) { return a; };
        std::function<int(void)> f2 = std::bind([](int a) {return a; }, 123);

        // 对于没有捕获任何变量的lambda表达式，还可以被转换成一个普通的函数指针：
        using func_t = int(*)(int);                        // c11 定义新类型 语法 同typedef c11支持定义模板类型
        func_t f = [](int a) {return a; };
        f(123);
    }

    {
        // lambda表达式可以说是定义仿函数闭包的语法糖，它捕获的任何外部变量都会转换为闭包类型的成员变量。
        // 而使用成员变量的类的operator(), 如果能直接转换为普通的函数指针，那lambda表达式本身的this指针会丢失，
        // 没有捕获任何外部变量的lambda表达式则不存在这个问题，所以按值捕获的外部变量无法修改。
        // 因为lambda表达式中的operator()默认是const的，const成员函数无法修改成员变量的值，而mutable则是取消operator()的const。
        // 所以，没有捕获变量的lambda表达式可以直接转换为函数指针，而捕获变量的lambda表达式则不能转换为函数指针。
        int a = 0;
        auto f1 = [=]() { return a; };                // ok
        // auto f2 = [=]() { return a++; };           // error
        auto f3 = [=]() mutable { return a++; };      // ok     f3();之后 a依然为0
        typedef void(*Ptr)(int*);                     //  定义新类型 语法
        Ptr p1 = [](int* p) {delete p; };             // ok,没有捕获的lambda表达式可以转换为函数指针
        // Ptr p2 = [&](int* p) {delete p; };         // error，有捕获的lambda表达式不能直接转换为函数指针，不能通过编译
    }

    {
        // lambda表达式的大致原理：每当你定义一个lambda表达式后，编译器会自动生成一个匿名类（这个类重载了()运算符），
        //  我们称为闭包类型（closure type）。
        // 运行时，这个lambda表达式就会返回一个匿名的闭包实例，是一个右值。所以，上面的lambda表达式的结果就是一个个闭包。
        // 对于复制传值捕捉方式，类中会相应添加对应类型的非静态数据成员。运行时，会用复制的值初始化这些成员变量，从而生成闭包。
        // 对于引用捕获方式，无论是否标记mutable，都可以在lambda表达式中修改捕获的值。
        //  至于闭包类中是否有对应成员，C++标准中给出的答案是：不清楚的，与具体实现有关。
        // lambda 表达式是不能被赋值的
        auto f1 = []() {std::cout << "a"; };
        auto f2 = []() {std::cout << "a"; };
        // f1 = f2;                 // error 无法赋值
        auto f3 = f1;               // ok    生成副本
    }

    {
        // 最好不要使用[=]和[&]默认捕获所有变量。
        // 默认引用捕获所有变量，你有很大可能会出现悬挂引用（Dangling references），因为引用捕获不会延长引用的变量的生命周期：
        // function<int(int)> addx(int x)
        // {
        //    return [&](int a) { return x + a; };
        // }
        // 上面函数返回一个lambda表达式，参数x仅是一个临时变量，函数add_x调用后就被销毁了，但返回的lambda表达式却引用了该变量，
        //  当调用这个表达式时，引用的是一个垃圾值，会产生没有意义的结果。这种情况，使用默认传值方式可以避免悬挂引用问题。

        // 但是采用默认值捕获所有变量仍然有风险，看下面的例子：
        class Filter
        {
        public:
            Filter(int divisorVal) :divisor{ divisorVal } {}
            std::function<bool(int)> getFilter()
            {
                return [=, this](int value) {return value % divisor == 0; };
                // return [=](int value) {return value % divisor == 0; }; // vs 2019
            }
        private:
            int divisor;
        };
        // 这个类中有一个成员方法，可以返回一个lambda表达式，这个表达式使用了类的数据成员divisor。
        // 而且采用默认值方式捕捉所有变量。你可能认为这个lambda表达式也捕捉了divisor的一份副本，但是实际上并没有。
        // 因为数据成员divisor对lambda表达式并不可见，你可以用下面的代码验证：
        // 类的方法，下面无法编译，因为divisor并不在lambda捕捉的范围
        // std::function<bool(int)> getFilter()
        // {
        //    return [divisor](int value) {return value % divisor == 0; };
        // }
        // 原代码中，lambda表达式实际上捕捉的是this指针的副本，所以原来的代码等价于：
        // std::function<bool(int)> getFilter()
        // {
        //    return [this](int value) {return value % this->divisor == 0; };
        // }
        // 尽管还是以值方式捕获，但是捕获的是指针，其实相当于以引用的方式捕获了当前类对象，
        //  所以lambda表达式的闭包与一个类对象绑定在一起了，这很危险，
        // 因为你仍然有可能在类对象析构后使用这个lambda表达式，那么类似“悬挂引用”的问题也会产生。
        //  所以，采用默认值捕捉所有变量仍然是不安全的，主要是由于指针变量的复制，实际上还是按引用传值

    }
}
void test1_cpp_2_for_each()
{
    using namespace std;

    vector<int> vct;
    for (int i = 1; i < 9 ; ++i)
    {
        vct.push_back(i);
        cout << i;
    }
    cout << endl;

    for_each(vct.begin(), vct.end(), [](int& i) {i++; });            // 引用 改变容器的值
    copy(vct.begin(), vct.end(), ostream_iterator<int>(cout, " "));  // 输出
    cout << endl;

    for_each(vct.begin(), vct.end(), [](int i) {cout << i << " < "; });  // 输出
    cout << endl;

    vector<int> vct2;
    for_each(vct.begin(), vct.end(), [&](int i) {vct2.push_back(++i); });
    transform(vct2.begin(), vct2.end(), ostream_iterator<int>(cout, " - "), [&](int i) {return i + 1; });  // 输出
    cout << endl;
}
void test1_cpp_2_count()
{
    using namespace std;

    list<int> lst;
    for (int i = 1; i < 9; ++i)
    {
        lst.push_back(i);
        cout << i;
    }
    cout << endl;

    cout << "[num3]" << count(lst.begin(), lst.end(), 3) << endl;
    cout << "[num 3< <7]" << count_if(lst.begin(), lst.end(), [](int i) { return i > 3 && i < 7; }) << endl;
    cout << "[num3 3<]" << count_if(lst.begin(), lst.end(), bind2nd(greater<int>(), 3)) << endl;
}
void test1_cpp_2_minmax()
{
    using namespace std;

    list<int> lst;
    for (int i = 1; i < 9; ++i)
    {
        lst.push_back(i);
        cout << i;
    }
    cout << endl;

    cout << "[min]" << *min_element(lst.begin(), lst.end()) << endl;
    cout << "[min]" << *min_element(lst.begin(), lst.end(), [](int i, int j) { return (i +3)%7 < (j + 3) % 7; }) << endl;
    cout << "[min]" << *min_element(lst.begin(), lst.end(), multiplies<int>()) << endl;
    transform(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "), bind2nd(multiplies<int>(), 2));
    cout << endl;

    cout << "[max]" << *max_element(lst.begin(), lst.end()) << endl;
    cout << "[max]" << *max_element(lst.begin(), lst.end(), [](int i, int j) { return (i + 3) % 7 < (j + 3) % 7; }) << endl;
    cout << "[max]" << *max_element(lst.begin(), lst.end(), multiplies<int>()) << endl;
}
void test1_cpp_2_find_search()
{
    using namespace std;

    list<int> lst;
    for (int i = 1; i < 9; ++i)
    {
        lst.push_back(i);
        cout << i;
    }
    cout << endl;

    // 搜寻n个连续元素
    string str = "abcccdefghijklmnopqrstuvwxyz";
    cout << "[c/3 ccc]" << *search_n(str.begin(), str.end(), 3, 'c') << endl;
    cout << "[c/3 ghi]" << *search_n(str.begin(), str.end(), 3, 'h', [](char c1, char c2) { return c2 < c1 + 2; }) << endl; // 其中 h传入c2
    cout << "[c/3 mno]" << *search_n(str.begin(), str.end(), 3, 'l', greater<char>()) << endl;

    // 搜寻第一个子区间
    string substr = "klm";
    cout << "[c/3 klm]" << *search(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
    cout << "[c/3 klm]" << *search(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c2 == c1 - 2; }) << endl;  //mno
    cout << "[c/3 klm]" << *search(str.begin(), str.end(), substr.begin(), substr.end(), greater<char>()) << endl;                           //lmn

    // 搜寻某个元素
    cout << "[find5]" << *find(lst.begin(), lst.end(), 5) << endl;
    cout << "[find5]" << *find_if(lst.begin(), lst.end(), [](int i) {return i > 7; }) << endl;
    cout << "[find5]" << *find_if(lst.begin(), lst.end(), bind2nd(greater<int>(), 5)) << endl;
    cout << "[find5]" << *find_if_not(lst.begin(), lst.end(), not1(bind2nd(greater<int>(), 5))) << endl;

    // 搜寻最后一个子区间
    str = "abcccdefghijklmnopqrklmstuvwxyz";
    substr = "klm";
    cout << "[klm]" << *find_end(str.begin(), str.end(), substr.begin(), substr.end()) << "[distance]" << distance(str.begin(), find_end(str.begin(), str.end(), substr.begin(), substr.end())) << endl;  //klm
    cout << "[klm]" << *find_end(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })        // lmn
        << "[distance]" << distance(str.begin(), find_end(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })) << endl;
    cout << "[klm]" << *find_end(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())        // jkl
        << "[distance]" << distance(str.begin(), find_end(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())) << endl;

    // 搜寻某些元素第一次出现的地点
    cout << "[klm]" << *find_first_of(str.begin(), str.end(), substr.begin(), substr.end()) << "[distance]" << distance(str.begin(), find_first_of(str.begin(), str.end(), substr.begin(), substr.end())) << endl;  //klm
    cout << "[klm]" << *find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })        // lmn
        << "[distance]" << distance(str.begin(), find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })) << endl;
    cout << "[klm]" << *find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())        // jkl
        << "[distance]" << distance(str.begin(), find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())) << endl;

    // 两个连续且相等的元素
    str = "abcddeg";
    cout << "[adjacent_find]"<< str << " " << *adjacent_find(str.begin(), str.end()) << endl;
    cout << "[adjacent_find]" << str << " " << *adjacent_find(str.begin(), str.end(), [](char c1, char c2) { return c1 + 2 == c2; }) << endl;

    // 计算范围中每个元素与其前一元素之间的差值，并将结果输出到目标范围，或计算将差值运算替换为其他指定二元运算的一般化程序的结果。
    str = "aabbccdefg";
    string strtemp = "";
    vector<int> vctint;
    adjacent_difference(str.begin(), str.end(), back_inserter(vctint));
    cout << "[adjacent_difference]" << str << " " << strtemp << endl;
    str = "abcdddefg";
    strtemp = "";
    // vctint.clear();
    vector<int> vctint2;
    adjacent_difference(str.begin(), str.end(), back_inserter(vctint2), [](char c1, char c2) { return (int)(c2 - c1); });          //c1 为后一个 c2为前一个
    cout << "[adjacent_difference]" << str << " " << strtemp << endl;
}
void test1_cpp_2_section()
{
    using namespace std;

    // 区间相等
    string str = "abcdefgh123456";
    string str2 = "bcdefgh123456";
    string substr = "bcd";
    cout << "[equal]" << equal(substr.begin(), substr.end(), str.begin() + 2) << endl;
    cout << "[equal]" << equal(substr.begin(), substr.end(), str.begin() + 5, [](char c1, char c2) { return c1 < c2; }) << endl;

    {
        // 区间第一处不同点
        string str = "abcdef";                                          // 字串小 目串大 first==end second!=end
        string substr = "abc";
        auto t1 = mismatch(substr.begin(), substr.end(), str.begin());  // 返回是个paire  first 是第一个区间的迭代器 second 是第二个
        cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")       //当first为sunstr.end时 说明没有不匹配的情况 但并能说明两个相等 因为str可能更大
            << "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;    //second 为str.end时
    }

    {
        string str = "ab";                                            // 字串大 目串小 first!=end second==end
        string substr = "abc";
        auto t1 = mismatch(substr.begin(), substr.end(), str.begin());  // 返回是个paire  first 是第一个区间的迭代器 second 是第二个
        cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")       //当first为sunstr.end时 说明没有不匹配的情况 但并能说明两个相等 因为str可能更大
            << "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;    //second 为str.end时
    }

    {
        string str = "abc";                                            // 字串 == 目串小 first==end second==end
        string substr = "abc";
        auto t1 = mismatch(substr.begin(), substr.end(), str.begin());  // 返回是个paire  first 是第一个区间的迭代器 second 是第二个
        cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")       //当first为sunstr.end时 说明没有不匹配的情况 但并能说明两个相等 因为str可能更大
            << "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;    //second 为str.end时
    }

    {
        string str = "bcd";
        string substr = "abc";
        auto t1 = mismatch(substr.begin(), substr.end(), str.begin(), [](char c1, char c2) {return c1 + 1 == c2; });
        cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")
            << "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;
    }

    {
        // 检验 小于 字典序
        string str = "abcdef";    //false
        string substr = "abc";
        cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
    }

    {
        string str = "abbcdef";   //true
        string substr = "abc";
        cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
    }

    {
        string str = "abc";      //false
        string substr = "abc";
        cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
    }

    {
        string str = "ab";       //true
        string substr = "abc";
        cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
    }
}
void test1_cpp_2_modify()
{
    using namespace std;

    string str = "abcdef";
    string str2 = "";
    copy(str.begin(), str.end(), ostream_iterator<char>(cout, " "));   // 输出
    cout << endl;

    copy(str.begin(), str.end(), back_inserter(str2));                 // 插入
    cout << str2 << endl;

    *str2.begin() = 'A';
    cout << str2 << endl;
    copy(str.begin(), str.end(), str2.begin());                        // 覆盖
    cout << str2 << endl;

    list<int> lst1;
    list<int> lst2;
    list<int> lst3;

    for (int i = 1; i < 6; ++i)
    {
        lst1.push_back(i);
        lst2.push_back(i * i);
        cout << i << " ";
    }
    cout << endl;

    transform(lst1.begin(), lst1.end(), ostream_iterator<int>(cout, " "), negate<int>());
    cout << endl;
    transform(lst1.begin(), lst1.end(), lst2.begin(), ostream_iterator<int>(cout, " "), multiplies<int>());
    cout << endl;
}
void test1_cpp_2_number()
{
    using namespace std;

    list<int> lst;
    for (int i = 1; i < 6; ++i)
    {
        lst.push_back(i);
    }

    // 和
    cout << "[accumulate 1-5]" << accumulate(lst.begin(), lst.end(), 0) << endl;  // 0 + 1 + 2 + 3 + 4 + 5;
    cout << "[accumulate 1-5]" << accumulate(lst.begin(), lst.end(), 0, [](int i, int j) {return i + j + 1; }) << endl;  //0 + 1 + 1 +   2 + 1 +   3 + 1 +   4 + 1 +   5 + 1;

    // 内积
    cout << "[inner_product 1-5]" << inner_product(lst.begin(), lst.end(), lst.begin(), 0) << endl;  //1 * 1 +   2 * 2 +   3 * 3 +   4 * 4 +   5 * 5 = 55;
    // initValue = op1(initValue, op2(elem1, elem2))
    //  0 +    0 + (1 + 1 + 2) + 1   (2 + 2 + 2) + 1   +    (3 + 3 + 2) + 1   +    (4 + 4 + 2) + 1   +    (5 + 5 + 2)  + 1 = 45;
    // init     i    i   j   2    1
    cout << "[inner_product 1-5]" << inner_product(lst.begin(), lst.end(), lst.begin(), 0, [](int i, int j) {return i + j + 1; }, [](int i, int j) {return i + j + 2; }) << endl;

    // 部分和
    cout << "[partial_sum 1-5]";
    partial_sum(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "));  //a1; a1 + a2; a1 + a2 + a3; a1 + a2 + a3 + a4;
    cout << endl;

    cout << "[partial_sum 1-5]";
    // 1 (1-2=2)2 (2-3=6)6 (6-4=24)24 (24-5=120)120
    //   i j      i j
    partial_sum(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "), [](int i, int j) { cout << "(" << i << "-" << j << "=" << i * j << ")";return i* j; });
    cout << endl;

    // 差额和
    cout << "[adjacent_difference 1-5]";
    adjacent_difference(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "));  //a1; a2 - a1; a3 - a2; a4 - a3; a5 - a4;
    cout << endl;

    cout << "[adjacent_difference 1-5]";
    // 1 (2-1=2)2 (3-2=6)6 (4-3=12)12 (5-4=20)20
    //    j i      j i
    adjacent_difference(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "), [](int i, int j) { cout << "(" << i << "-" << j << "=" << i * j << ")"; return i * j; });
    cout << endl;
}
void test1_cpp_2_fill()
{
    using namespace std;

    // std::fill函数的作用是：将一个区间的元素都赋予指定的值，即在[first, last)范围内填充指定值。
    // std::fill_n函数的作用是：在[fist, fist + count)范围内填充指定值。
    {
    std::vector<int> myvector(8); // myvector: 0 0 0 0 0 0 0 0
    std::fill(myvector.begin(), myvector.begin() + 4, 5); // myvector: 5 5 5 5 0 0 0 0
    std::fill(myvector.begin() + 3, myvector.end() - 2, 8); // myvector: 5 5 5 8 8 8 0 0
    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    }

    {
    float arr[10];
    std::fill(&arr[0], &arr[0] + 10, 1.23); // 1.230000  1.230000  1.230000  1.230000  1.230000  1.230000  1.230000  1.230000  1.230000  1.230000
    for (int i = 0; i < 10; i++)
        fprintf(stderr, "%f  ", arr[i]);
    fprintf(stderr, "\n");
    }

    {
    std::vector<int> myvector(8, 10); // myvector: 10 10 10 10 10 10 10 10
    std::fill_n(myvector.begin(), 4, 20); // myvector: 20 20 20 20 10 10 10 10
    std::fill_n(myvector.begin() + 3, 3, 33); // myvector: 20 20 20 33 33 33 10 10
    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    }
}


void test1_cpp_2_string(){
    using std::string;
    #define valname(val) (#val)
    #define valprint(val) std::cout << valname(val) << ":" << val << std::endl;
    // 1 定义
    // 定义的字符串过长自动截断 str=...large...
    {
    string str1 = "abc";  // 简单定义
    string str2 =         // 分行定义
        "abc\
123\
        end";
    string str3 =         // 拼接定义
        "abc"
        "123";
    string str4(          // C++ 11开始支持Raw string literal,格式 R"delimiter(raw_characters)delimiter"
        R"EOF(
<Auto>
    <Disk mxproptype="1">
        <Disk Name="F1" Label="L1" />
    </Disk>
</Auto>
)EOF");
    string str5 =
        R"(
<Auto>
    <Disk mxproptype="1">
        <Disk Name="F1" Label="L1" />
    </Disk>
</Auto>
)";

    valprint(str1)
    valprint(str2)
    valprint(str3)
    valprint(str4)
    valprint(str5)

    int len = 0;
    char cstr1[10] = "hello";      // 默认 窄字符
    wchar_t wcstr[10] = {0};       // 宽字符
    wchar_t wcstr2[10] = L"hello"; // L告诉编译器，这个字符串按照宽字符来存储(一个字符占两个字节)
    char* pc = (char*)wcstr;
    char* pc2 = (char*)(wcstr+1);
    len = (wcstr+1) - (wcstr);   valprint(len)                  // 1
    len = (char*)(wcstr+1) - (char*)(wcstr);   valprint(len)    // 4
    len = (cstr1+1) - (cstr1);   valprint(len)                  // 1
    }

    // 字符串 数字
    {
        string str1;
        char tmp[100] = {0};
        int i = atoi("123");  valprint(i)
        int i2,i3;
        str1="123 456"; sscanf(str1.c_str(), "%d %d", &i2, &i3);  valprint(i2)  valprint(i3)
        str1="1234567891234"; long long l1 = atoll(str1.c_str()); valprint(l1)

        // itoa函数头文件是stdio.h, 它不是一个标准的C函数，而是Windows特有的，如果在linux系统使用itoa函数，编译会通不过。
        // printf("%s\n", std::iota(123, tmp, 10));


        // 字符串中按照规定的格式选择字符 直到不匹配的字符停止 贪婪算法尽可能的多读
        str1 = "ccu_1 - 1#123";                    printf("%%origin:%s\n", str1.c_str());
        sscanf(str1.c_str(), "%[a-z]", tmp);       printf("%%[a-z]:%s\n", tmp); //字符串中按照 a-z 范围选择字符
        sscanf(str1.c_str(), "%[abcdefgu_]", tmp); printf("%%[abcdefgu_]:%s\n", tmp);//字符串中按照 abcdefgu_ 范围选择字符
        sscanf(str1.c_str(), "%[^#]", tmp);        printf("%%[^#]:%s\n", tmp);//字符串中 直到第一个 # 字符 停止  不包含 #
        sscanf(str1.c_str(), "%[a-z_1]", tmp);     printf("%%[a-z_1]:%s\n", tmp);//字符串中按照 a-z以及_1 范围选择字符
    }
    // 比较
    {
        string s1= "1";
        string s2 = "2";
        std::cout << "s1.compare(s2):" << s1.compare(s2) << std::endl;
        if (s1 == s2)
            std::cout << "equl" << std::endl;
        else
            std::cout << "no equl" << std::endl;
    }

    {
        // 自定义trim函数
        auto funcTrim = [](string szSrc, const char* pStr) -> string{
        std::string m_szSrc = szSrc;
        string::size_type pos = m_szSrc.find_last_not_of(pStr);
        if (pos != string::npos) {
            m_szSrc.erase(pos + 1);
            pos = m_szSrc.find_first_not_of(pStr);
            if (pos != string::npos) m_szSrc.erase(0, pos);
        }
        else
            m_szSrc.erase(m_szSrc.begin(), m_szSrc.end());
        return m_szSrc;
        };

        string str, str2;
        str = "abc def  ";       str2 = funcTrim(str, " ");  valprint(str)
        str = "abc11def112211 "; str2 = funcTrim(str, "11"); valprint(str)
        str = "abc11def112211";  str2 = funcTrim(str, "11"); valprint(str)
        str = "11abcdef11";      str2 = funcTrim(str, "11"); valprint(str)
    }

    {
        string szLabel = "ip-192.1681.1.1.1-company-co_123_test-net-Net_1234_test";
        string strTIp = "ip-";
        string strTCompany = "-company-";
        string strTNet = "-net-";
        size_t sCompanny = szLabel.find("-company-");
        size_t sNet = szLabel.find("-net-");
        string szCCU = szLabel.substr(strTIp.size(), sCompanny - strTIp.size());
        string strCompany = szLabel.substr(sCompanny + strTCompany.size(), sNet - sCompanny - strTCompany.size());
        string strNet = szLabel.substr(sNet + strTNet.size());
        valprint(szCCU) valprint(strCompany) valprint(strNet)
    }
    {
        // 从末尾开始提取IP
        string tmp = "1.3.6.1.4.1.25506.2.67.1.1.2.1.4.634.1.4.192.168.11.254";
        size_t pos = string::npos;
        string::reverse_iterator it = tmp.rbegin();
        string ret = "";
        string ret2 = "";
        string ret3 = "";
        string ret4 = "";
        int i = 0;
        int i2 = 0;
        for (it = tmp.rbegin(); it != tmp.rend() && i < 4; ++it)        {
            if (*it == '.')
                ++i;
            ++i2;
        }

        if (it == tmp.rend() || i < 4) { }

        int ii = std::distance(tmp.rbegin(), it);
        int ii2 = it - tmp.rbegin();
        ret = tmp.substr(tmp.length() - (it - tmp.rbegin()) + 1);
        ret2 = tmp.substr(tmp.length() - i2 + 1);
        ret3 = tmp.substr(tmp.length() - ii2 + 1);
        ret4.assign(it.base(), tmp.end());
        printf("ret:%s\n", ret.c_str());
    }

    {
        string str1 = "abc123 abc123";
        string str2 = "abc abc";
        string str3 = "";

        str3 = str1.replace(str1.find("123"), 2, "qazx");
        std::cout << str3 << std::endl;    // abcqazx3 abc123
        // str3 = str2.replace(str2.find("123"), 2, "qazx");  // 没找到则挂掉 string::npos
    }
    {
        string str = "abc fopen 123";
        if (str.find("fopen") != string::npos)
        {
            str.erase(str.find("fopen"), 1);        // 删除一个字符
        }
        std::cout << str << std::endl;     // abc open 123
    }
}
int compareLongs(const void* a, const void* b){return (*(long*)a-*(long*)b);}
#include <stdlib.h>
void test1_cpp_2_array()
{
    using namespace std;
    const int ASIZE = 10;
    cout << "test1_cpp_2_array\n";
    array<long, ASIZE> c;
    clock_t timeStart = clock();
    for(long i=0; i< ASIZE; i++) c[i] = rand();
    cout << "milli-seconds : " << (clock()-timeStart) << endl;
    cout << "array.size()" << c.size() << endl;
    cout << "array.front()" << c.front() << endl;
    cout << "array.back()" << c.back() << endl;
    cout << "array.data()" << c.data() << endl;
    long target = 11;
    timeStart = clock();
    qsort(c.data(), ASIZE, sizeof(long), compareLongs);
    long *pItem = (long*)bsearch(&target, c.data(), ASIZE, sizeof(long), compareLongs);
    cout << "qsort()+bsearch(), milli-seconds : " <<(clock() -  timeStart) << endl;
    if (pItem != NULL) cout << "found," <<*pItem << endl;
    else cout << "not found!" << endl;
}
void test1_cpp_2_vector()
{
    // vector<int> vec;                //声明一个int型向量
    // vector<int> vec(5);             //声明一个初始大小为5的int向量
    // vector<int> vec(10, 1);         //声明一个初始大小为10且值都是1的向量
    // vector<int> vec(tmp);           //声明并用tmp向量初始化vec向量
    // vector<int> tmp(vec.begin(), vec.begin() + 3);        // 用向量vec的第0个到第2个值初始化tmp
    // int arr[5] = {1, 2, 3, 4, 5};
    // vector<int> vec(arr, arr + 5);                // 将arr数组的元素用于初始化vec向量 不包括arr[4]
    // vector<int> vec(&arr[1], &arr[4]); // 将arr[1]~arr[4]范围内的元素作为vec的初始值


    // push_back和emplace_back  https://zhuanlan.zhihu.com/p/183861524
    // 1 push_back只能接受该类型的对象，emplace_back 还能接受该类型的构造函数的参数
    class New {int i;std::string st;
    public:
    New(int ii, std::string s):i(ii) , st(s) { }
    ~New( ) { }
    };
    std::vector<New> vec={ {21, "String"} , New{45 , "tinger"} } ;
    vec.push_back( New(34 , "Happy" ) ) ;        // 传入的是一个对象
    // vec.push_back( 901 , "Doer" ) ;              // Error!!
    vec.emplace_back( New(78 , "Gomu gomu" ) );  // work fine
    vec.emplace_back( 41 , "Shanks" ) ;          // work fine

    // 2 性能 内置类型都一样  用户自定义的类emplace_pack仅在通过 使用 构造参数 传入 的时候更高效
    class A {public:
    A () { x = 0; std::cout << "A ()" << std::endl; } // 无参构造函数
    A (int x_arg) : x (x_arg) { std::cout << "A (x_arg), x=" << x << std::endl; }  // 有参构造函数
    A (const A &rhs) noexcept { x = rhs.x + rhs.x * 10; std::cout << "A (A &), x=" << x << std::endl; }  // 拷贝构造函数
    A (A &&rhs) noexcept { x = rhs.x + rhs.x * 100; std::cout << "A (A &&), x=" << x <<  std::endl; }  // 移动构造函数
    ~A() { std::cout << "~A () | " << x << std::endl; }  // 析构函数
    private: int x;
    };

    {
    // 2.1 通过构造参数向vector中插入对象（emplace_back很高效）
    std::vector<A> a;
    std::cout << "call emplace_back 2.1: \n";
    a.emplace_back(1);
    // (1) direct object creation inside vector
    }

    {
    std::vector<A> a;
    std::cout << "call push_back 2.1: \n";
    a.push_back(2);
    // (1) create temp object and
    // (2) then move to vector and
    // (3) free temp object
    }

    {
    // 2.2 插入临时对象（二者一样！调用移动构造函数）
    // 插入对象都需要三步走：建临时对象->移动->销毁临时对象
    std::vector<A> a;
    std::cout << "call emplace_back 2.2: \n";
    a.emplace_back(A(1));
    // (1) create temp object and
    // (2) then move to vector and
    // (3) free temp object
    }

    {
    std::vector<A> a;
    std::cout << "call push_back 2.2: \n";
    a.push_back(A(2));
    // (1) create temp object and
    // (2) then move to vector and
    // (3) free temp object
    }

    {
    // 2.3 插入对象实例（二者还是一样！调用拷贝构造函数）
    std::vector<A> a;
    std::cout << "call emplace_back 2.3: \n";
    A obj(1);
    a.emplace_back(obj);
    // (1) copy to vector and
    // (2) free temp object
    }

    {
    std::vector<A> a;
    std::cout << "call push_back 2.3: \n";
    A obj(2);
    a.push_back(obj);
    // (1) copy to vector and
    // (2) free temp object
    }

}
bool mycompare(std::string& strA, std::string& strB) {
    int lengA = strA.length();
    int lengB = strB.length();
    if (lengA < lengB) {
        int i = strB.find(strA.c_str());
        if (i == 0) {
            if (strB.at(i + lengA) == '.') return false;
            else return true;
        }
        return strA < strB;
    }
    if (lengA == lengB) return strA < strB;
    else {
        int i = strA.find(strB.c_str());
        if (i == 0) {
            if (strA.at(i + lengB) == '.') return true;
            else return false;
        }
        return strA < strB;
    }
}
bool mycompare2(std::string& strA, std::string& strB) {
    int lengA = strA.length();
    int lengB = strB.length();
    if (lengA < lengB) return true;
    if (lengA == lengB) return strA < strB;
    else return false;
}
void test1_cpp_2_list()
{
    // list<int> a; // 定义一个int类型的列表a
    // list<int> a(10); // 定义一个int类型的列表a，并设置初始大小为10
    // list<int> a(10, 1); // 定义一个int类型的列表a，并设置初始大小为10且初始值都为1
    // list<int> b(a); // 定义并用列表a初始化列表b
    // deque<int> b(a.begin(), ++a.end()); // 将列表a中的第1个元素作为列表b的初始值
    // int n[] = { 1, 2, 3, 4, 5 };//使用数组来初始化向量
    // list<int> a(n, n + 5); // 将数组n的前5个元素作为列表a的初值
    using namespace std;
    {
        list<int> ll1;
        list<int> ll2;
        list<int> ll3;
        list<int> ll4;
        list<int> ll5;
        list<int> ll6;
        ll1.push_back(1);
        ll1.push_back(2);
        ll1.push_back(3);

        ll2.push_back(1);
        ll2.push_back(4);
        ll2.push_back(3);

        ll1.sort();
        ll1.unique();
        ll2.sort();

        set_difference(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), insert_iterator<list<int> >(ll3, ll3.begin()));      // S1 - S2
        set_union(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), back_inserter<list<int> >(ll4));                          // S1 + S2
        set_intersection(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), back_inserter(ll5));                                // S1 ^ S2
        set_symmetric_difference(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), insert_iterator<list<int> >(ll6, ll6.begin())); // S1 n S2 + S2 n S1

        printf("------------set_difference--------------\n");
        for (auto it = ll3.begin(); it != ll3.end(); ++it) {
            printf("%d\n", *it);
        }

        printf("------------set_union--------------\n");
        for (auto it = ll4.begin(); it != ll4.end(); ++it) {
            printf("%d\n", *it);
        }

        printf("------------set_intersection--------------\n");
        for (auto it = ll5.begin(); it != ll5.end(); ++it) {
            printf("%d\n", *it);
        }

        printf("------------set_symmetric_difference--------------\n");
        for (auto it = ll6.begin(); it != ll6.end(); ++it) {
            printf("%d\n", *it);
        }
    }

    {
        list<int> lst = { 1,2,3,4,5 };
    }

    // 删除指针类型 看是否调用析构
    {
        class iint {
        public:
            iint() {}
            iint(int i) { m_i = i; }
            ~iint() { printf("destruct %d\n", m_i); }
            int m_i;
        };

        list<iint*> lst;
        lst.push_back(new iint(1));
        lst.push_back(new iint(2));
        lst.push_back(new iint(3));

        for (auto it = lst.begin(); it!=lst.end();)
        {
            iint* pp = *it;
            lst.erase(it++);
            delete pp;
        }
        printf("erase %ld\n", lst.size());         // 0
        lst.clear();
    }

    // 指定比较方法
    {
        list<string> lst;
        lst.push_back("1.sd1");
        lst.push_back("1.sd1.1");
        lst.push_back("1.sd");
        lst.push_back("1.s");
        //lst.push_back("1.sd2");
        //lst.push_back("1.sd1.1.1");
        //lst.push_back("1.sd2.1");
        //lst.push_back("1.sd1.1");

        auto ff = [&lst](const string msg) {
            printf("%s\n", msg.c_str());
            int index = 0;
            for (auto i : lst)
            {
                printf("%d %s\n", ++index,i.c_str());
            }
            printf("\n");
        };

        ff("no sort");
        lst.sort(mycompare2);
        ff("sorted");
    }
}
void test1_cpp_2_forward_list()
{
    // https://elloop.github.io/c++/2015-12-25/learning-using-stl-7-std-forward-list
    // constructor
    // forward_list<T> c                    默认构造函数，构造一个空的列表。
    // forward_list<T> c(c2)                使用c2来拷贝构造c，c2中所有元素都被拷贝
    // forward_list<T> c = c2               使用c2来拷贝构造c，c2中所有元素都被拷贝
    // forward_list<T> c(rValue)            移动构造函数，使用右值rValue的内容来构造c。
    // forward_list<T> c = rValue           移动构造函数，使用右值rValue的内容来构造c。
    // forward_list<T> c(n)                 构造一个含有n个元素的列表，每个元素使用默认构造函数创建
    // forward_list<T> c(n, elem)           构造一个含有n个elem元素的列表
    // forward_list<T> c(begin, end)        使用[begin, end)之间的元素初始化c
    // forward_list<T> c(initiallist)       使用初始化列表initiallist来初始化c
    // forward_list<T> c = initiallist      使用初始化列表initiallist来初始化c

    // 非修改类接口 nonmodifying operations.
    // c.empty()        是否是空列表
    // c.max_size()        最大可能的容量
    // c1 == c2        是否相等，内部对所有elems调用==
    // c1 != c2        !(c1 == c2)
    // c1 < c2        小于
    // c1 > c2        c2 < c1
    // c1 <= c2        !(c2 < c1)
    // c1 >= c2        !(c1 < c2)
    // 注意：性能考虑，forward_list不提供size()，“不比手写的C风格单链表有更多的时间和空间上的开销”的标准设计目标.

    // 赋值操作 assignments
    // c1 = c2                 c2所有元素赋值给c1
    // c1 = rValue             move rValue所有元素给c1
    // c1 = initiallist        initiallist所有元素赋值给c1
    // c1.assign(initiallist)  分配initiallist给c1
    // c1.assign(n, elem)      分配n个elem
    // c1.assign(begin, end)   分配[begin, end)给c1
    // c1.swap(c2)             交换c1, c2
    // swap(c1, c2)            交换c1, c2

    // 元素访问 element access
    // 同样是出于简单高效的设计目标，forward_list只有一个直接访问元素的接口：c.front().
    // c.front()返回第一个元素，这个接口内部并不会检查是不是存在第一个元素。如果调用了，但是元素不存在，那么导致未定义行为。
    // 既然只有一个接口返回第一个元素，那么怎么来遍历所有元素呢？
    // 有两种方式：iterators.   range-based for loops. (其本质依然是使用iterators)

    // 迭代器函数 iterator functions.
    // c.begin()                指向第一个元素的迭代器
    // c.end()                  最后一个元素的下一个位置
    // c.cbegin()               const begin()
    // c.cend()                 const end()
    // c.before_begin()         第一个元素前一个位置
    // c.cbefore_begin()        const before_begin()
    // 使用迭代器是遍历forward_list所有元素的方式之一, 这一点和其他类型的容器类似，不必细说，待会看代码的例子就明了了。
    // 注意: 对end()和before_begin()迭代器的直接操作都是未定义的行为，有可能造成运行时错误：
    // *c.before_begin();      // undefined behaviour
    // *c.end();               // undefined behaviour
    // 一般没人会像上面这样写，但是有时候连我自己都不知道我会对这两个位置进行解引用，比如我从一个函数的返回值得到了一个pos，然后我没有对pos进行合法性检查就直接*pos。

    // 插入、移除元素 modifying operations
    // c.push_front()                         在开头插入元素
    // c.pop_front()                          删掉开头元素
    // c.insert_after(pos, elem)              在pos之后插入元素, 返回新元素的位置
    // c.insert_after(pos, n, elem)           在pos之后插入n个元素elem, 返回第一个新元素的位置
    // c.insert_after(pos, begin, end)        在pos之后插入元素[begin, end), 返回第一个新元素的位置
    // c.insert_after(pos, initiallist)       在pos之后插入initiallist, 返回第一个新元素的位置
    // c.emplace_after(pos, args...)          在pos之后插入args…元素，返回第一个新元素的位置
    // c.emplace_front(args...)               在开头插入元素args…, 无返回值
    // c.erase_after(pos)                     删掉pos后面那个元素
    // c.erase_after(begin, end)              删掉(begin, end)之间的元素
    // c.remove(val)                          移除所有值为val的元素
    // c.remove_if(op)                        删掉所使得op(elem)为true的元素
    // c.resize(n)                            调整个数为n，如果变大了，那多出来的用默认构造函数来创建
    // c.resize(n, elem)                      调整个数为n，如果变大了，那多出来的用elem的来拷贝构造
    // c.clear()                              清除所有元素
    // 手写过单链表这种数据结构的人都会知道，对单链表的插入和删除操作都需要指定一个位置，并且这个位置要是被改动元素之前的位置，这是因为单链表不能够“回头”，比如我要删除第N个元素，我不仅要删掉第N个，还需要修改第N-1个元素，使它的跟第N+1个连在一起。
    // 这个道理在std::forward_list上的体现就是，插入和删除forward_list的操作跟其他的标准容器的接口不太一样：
    // 1. forward_list的接口总是需要一个“位置”参数pos, 要处理的元素就是在pos的后面；
    // 2. forward_list的接口总是以 _after结尾，意思是在某个参数之后进行操作。

    // 连接(splice)和变序类操作
    // c.unique()                                       删除连续相同的元素
    // c.unique(op)                                     删除连续使得op(elem) == true的元素
    // dst.splice_after(dstPos, src)                    把src里的全部元素移动到dst中的dstPos之后
    // dst.splice_after(dstPos, src, srcPos)            把src里的srcPos后面的一个元素移动到dst中的dstPos之后
    // dst.splice_after(dstPos, src, srcBegin, srcEnd)  把src里(srcBegin, srcEnd)之间的元素移动到dst中的dstPos之后
    // c.sort()                                         使用默认的<来给c中的元素排序
    // c.sort(op)                                       使用op来给c中的元素排序
    // c.merge(c2)                                      移动c2中的元素到c中，假定二者原来都已序，那么移动之后c仍然有序
    // c.merge(c2, op)                                  移动c2中的元素到c中，假定二者原来都按op已序，那么移动之后c仍然按op有序
    // c.reverse()                                      所有元素反序
    // 注意：splice_after中涉及到的dst, src可以是同一个forward_list, 此时，这个操作就是在列表内部来移动元素。splice_after的位置参数不要使用end(), 这将导致未定义行为。
}
void test1_cpp_2_deque()
{
    // 动态大小：std::deque 具有动态大小的能力，可以根据需要自动增加或减小。
    // 快速插入和删除：相对于 std::vector，std::deque 在头部和尾部进行插入和删除操作的时间复杂度是常数级别的，即 O(1)。
    // 随机访问：与 std::vector 类似，std::deque 支持通过索引进行随机访问，可以以常数时间 O(1) 访问指定位置的元素。
    // 双向迭代器：std::deque 提供了双向迭代器，可以遍历从头到尾或者从尾到头的元素序列。
    // 低效的中间插入和删除：相对于头部和尾部的操作，std::deque 在中间进行插入和删除操作的时间复杂度是线性级别的，即 O(n)，因为它需要移动元素块。
    // deque<int> a; // 定义一个int类型的双端队列a
    // deque<int> a(10); // 定义一个int类型的双端队列a，并设置初始大小为10
    // deque<int> a(10, 1); // 定义一个int类型的双端队列a，并设置初始大小为10且初始值都为1
    // deque<int> b(a); // 定义并用双端队列a初始化双端队列b
    // deque<int> b(a.begin(), a.begin()+3); // 将双端队列a中从第0个到第2个(共3个)作为双端队列b的初始值
    // int n[] = { 1, 2, 3, 4, 5 };
    // deque<int> a(n, n + 5); // 将数组n的前5个元素作为双端队列a的初值
    // deque<int> a(&n[1], &n[4]); // 将n[1]、n[2]、n[3]作为双端队列a的初值 不包括arr[4]元素
    // deque 与 vector 的用法基本一致，除了以下几处不同：
    // deque 没有 capacity() 函数，而 vector 有；
    // deque 有 push_front() 和 pop_front() 函数，而 vector 没有；
    // deque 没有 data()和reserve() 函数，而 vector 有。
}
void test1_cpp_2_map()
{
    // 1 map中用[]访问元素
    // 若该key存在，则访问取得value值；
    // 若该key不存在，访问仍然成功，取得value对象默认构造的值。具体如下：
    //   用[]访问，但key不存在时，C++会利用该key及默认构造的value，组成{ key，value }对，插入到map中。
    //   value为 string对象，则构造空串；value为int对象，构造为0。
    // 注：因此在访问map元素时，应先用map.find查找该元素，找到后再访问。
    // 同时，用法mymap2["str"]++; 常用于词频统计，存在则加一，不存在则创建后赋值为1。

    // 2 Map中的元素是自动按key升序排序

    // 3 map中元素的删除：
    //   my_Map.erase(my_Itr);
    //   my_Map.erase("c");
    // 还是注意，第一种情况在迭代期间是不能被删除的，道理和foreach时不能删除元素一样。

    // map<string,itemS>::iterator   it;
    // for (it = mymap.begin(); it != mymap.end(); it++)
    // {
    //    if (it->second.a > 100)
    //    {
    //        i = mymap.erase(it);     ----->正确
    //            mymap.erase(it);     ----->it失效
    //    }
    // }

    // C98    1 3 不返回值
    //  1 void erase(iterator position);
    //  2 size_type erase(const key_type & k);   // 返回删除的数量
    //  3 void erase(iterator first, iterator last);

    // C11  1 3返回  return an iterator to the element that follows the last element removed (or map::end, if the last element was removed).
    //  1 iterator  erase(const_iterator position);
    //  2 size_type erase(const key_type & k);   // 返回删除的数量
    //  3 iterator  erase(const_iterator first, const_iterator last);
    {
        std::map<std::string, void*> map1;
        int i1 = 11;
        int i2 = 12;
        int i3 = 13;
        map1["111"] = &(i1);
        map1["222"] = &(i2);
        map1["333"] = &(i3);

        // 1
        for (auto it = map1.begin(); it != map1.end(); ++it)
        {
            if (*((int*)(it->second)) == 11)
            {
                auto it2 = map1.erase(it);
                printf("[%s-%s]\n", "11", (it2 == map1.end()? "end":it2->first.c_str()));
                break;
            }
        }
        // 2
        for (auto it = map1.begin(); it != map1.end(); ++it)
        {
            if (*((int*)(it->second)) == 12)
            {
                auto it2 = map1.erase(it);
                printf("[%s-%s]\n", "12", (it2 == map1.end() ? "end" : it2->first.c_str()));
                break;
            }
        }
        // 3
        for (auto it = map1.begin(); it != map1.end(); ++it)
        {
            if (*((int*)(it->second)) == 13)
            {
                auto it2 = map1.erase(it);
                printf("[%s-%s]\n", "13", (it2 == map1.end() ? "end" : it2->first.c_str()));
                break;
            }
        }
        // [11-222]
        // [12-333]
        // [13-end]

        // 即使是 把 1 2 注释掉 3的输出也是 故erase返回的是下一个
        // [13-end]
    }

    {
        std::map<std::string, void*> map1;
        int i1 = 11;
        int i2 = 12;
        int i3 = 13;
        map1["111"] = &(i1);
        map1["222"] = &(i2);
        map1["333"] = &(i3);

        auto it = map1.find("555");

        printf("[%s-%x]\n", "555", ((it == map1.end()) ? 5 : 9));   // 没有key则抛出异常 out_of_range
        // [555-5]
    }
    try{
        std::map<std::string, void*> map1;
        int i1 = 11;
        int i2 = 12;
        int i3 = 13;
        map1["111"] = &(i1);
        map1["222"] = &(i2);
        map1["333"] = &(i3);


        printf("[%s-%p]\n", "111", map1["111"]);
        printf("[%s-%p]\n", "222", map1["222"]);
        printf("[%s-%p]\n", "333", map1["333"]);
        printf("[%s-%x]\n", "444", ((map1["444"] == NULL) ? 4 : 9));    // 没有key则默认添加之 value 为null
        printf("[%s-%x]\n", "555", ((map1.at("555") == NULL) ? 5 : 9)); // 没有key则抛出异常 out_of_range
        // [111 - 93fd98]
        // [222 - 93fd94]
        // [333 - 93fd90]
        // [444 - 4]
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of Range Exception at " << e.what();
    }

    {
        std::map<std::string, int> map1;
        int i1 = 11;
        int i2 = 12;
        int i3 = 13;
        map1["111"] = i1;
        map1["222"] = i2;
        map1["333"] = i3;

        printf("[%s-%d]\n", "111", map1["111"]);
        printf("[%s-%d]\n", "222", map1["222"]);
        printf("[%s-%d]\n", "333", map1["333"]);
        printf("[%s-%d]\n", "444", ((map1["444"] == 0) ? 4 : 9));   // 没有key则默认添加之 value 为0
        // [111 - 11]
        // [222 - 12]
        // [333 - 13]
        // [444 - 4]
    }
}
void test1_cpp_2_set()
{
    std::set<std::string> myset1;//调用默认构造函数，创建空的 set 容器
    std::set<std::string> myset2{"/java/","/stl/","/python/"};//支持在创建 set 容器的同时，对其进行初始化
    std::set<std::string> myset3(myset2); // 拷贝构造函数
    std::set<std::string> myset4(++myset2.begin(), myset2.end()); // 支持取已有 set 容器中的部分元素，来初始化新 set 容器

    // begin()             返回指向第一个元素的迭代器
    // end()               返回指向迭代器的最末尾处（即最后一个元素的下一个位置）
    // clear()             清除所有元素
    // count()             返回某个值元素的个数
    // empty()             如果集合为空，返回true
    // equal_range()       返回集合中与给定值相等的上下限的两个迭代器
    // erase()             删除集合中的元素
    // find()              返回一个指向被查找到元素的迭代器
    // get_allocator()     返回集合的分配器
    // insert()            在集合中插入元素
    // lower_bound()       返回指向大于（或等于）某值的第一个元素的迭代器
    // key_comp()          返回一个用于元素间值比较的函数
    // max_size()          返回集合能容纳的元素的最大限值
    // rbegin()            返回指向集合中最后一个元素的反向迭代器
    // rend()              返回指向集合中第一个元素的反向迭代器
    // size()              集合中元素的数目
    // swap()              交换两个集合变量
    // upper_bound()       返回大于某个值元素的迭代器
    // value_comp()        返回一个用于比较元素间的值的函数
}
void test1_cpp_2_hash_simple()
{
#ifdef __linux__
    __gnu_cxx::hash_map<int, std::string> hsm;
    __gnu_cxx::hash_set<int> hss;
#else
    stdex::hash_map<int, std::string> hsm;
    stdex::hash_set<int> hss;
#endif

    // 或者使用 hash_multimap
    hsm[1] = "a";
    hsm[2] = "ab";
    hsm[3] = "abc";
    hsm[4] = "abcd";
    printf("hsm size %lu buck %lu\n", hsm.size(), hsm.bucket_count()); // hsm size 4 buck 193

    // 或者使用 hash_multiset
    hss.insert(1);
    hss.insert(2);
    hss.insert(3);
    hss.insert(4);
    printf("hss size %lu buck %lu\n", hss.size(), hss.bucket_count()); // hss size 4 buck 193

    std::unordered_map<int, std::string> uom;
    uom[1] = "a";
    uom[2] = "ab";
    uom[3] = "abc";
    uom[4] = "abcd";
    printf("uom size %lu buck %lu\n", uom.size(), uom.bucket_count()); // uom size 4 buck 13

    std::unordered_set<int> uos;
    uos.insert(1);
    uos.insert(2);
    uos.insert(3);
    uos.insert(4);
    printf("uos size %lu buck %lu\n", uos.size(), uos.bucket_count()); // uos size 4 buck 13
}
struct st_key1_cpp_1{int i;int j;st_key1_cpp_1():i(0),j(0){}st_key1_cpp_1(int a, int b):i(a),j(b){}};
struct hash1_cpp_1{size_t operator () (const st_key1_cpp_1 &t) const {return size_t(t.i);}};
struct equal1_cpp_1{bool operator () (const st_key1_cpp_1 &t1, const st_key1_cpp_1 &t2) const {return t1.i == t2.i;}};
void test1_cpp_2_hash_selfdef()
{
#ifdef __linux__
    typedef __gnu_cxx::hash_map<st_key1_cpp_1, std::string, hash1_cpp_1, equal1_cpp_1> myhsm;
    typedef __gnu_cxx::hash_set<st_key1_cpp_1, hash1_cpp_1, equal1_cpp_1> myhss;
#else
    typedef stdext::hash_map<st_key1_cpp_1, std::string, hash1_cpp_1, equal1_cpp_1> myhsm;
    typedef stdext::hash_set<st_key1_cpp_1, hash1_cpp_1, equal1_cpp_1> myhss;
#endif

    // 或者使用 hash_multimap
    myhsm hsm;
    hsm[st_key1_cpp_1(1,2)] = "a";
    hsm[st_key1_cpp_1(2,2)] = "b";
    // hsm.insert(make_pair(st_key1_cpp_1(1,2), "a")); // hash_multimap
    // hsm.insert(make_pair(st_key1_cpp_1(2,2), "b")); // hash_multimap
    // hsm.insert(make_pair(st_key1_cpp_1(2,2), "c")); // hash_multimap
    printf("hsm size %lu buck %lu\n", hsm.size(), hsm.bucket_count());      // hsm size 2 buck 193
    printf("hsm find %s\n", hsm.find(st_key1_cpp_1(2,2))->second.c_str());  // hsm find b

    // 或者使用 hash_multiset
    myhss hss;
    hss.insert(st_key1_cpp_1(1,2));
    hss.insert(st_key1_cpp_1(2,2));
    printf("hss size %lu buck %lu\n", hss.size(), hss.bucket_count());      // hss size 2 buck 193

    typedef std::unordered_map<st_key1_cpp_1, std::string, hash1_cpp_1, equal1_cpp_1> myuom;
    myuom uom;
    uom[st_key1_cpp_1(1,2)] = "a";
    uom[st_key1_cpp_1(2,2)] = "b";
    uom[st_key1_cpp_1(2,2)] = "c";
    printf("uom size %lu buck %lu\n", uom.size(), uom.bucket_count());      // uom size 2 buck 13

    typedef std::unordered_set<st_key1_cpp_1, hash1_cpp_1, equal1_cpp_1> myuos;
    myuos uos;
    uos.insert(st_key1_cpp_1(1,2));
    uos.insert(st_key1_cpp_1(2,2));
    printf("uos size %lu buck %lu\n", uos.size(), uos.bucket_count());      // uos size 2 buck 13
}
struct hash2_cpp_1{
    // size_t operator () (const std::string &t) const {return t.size();}
    size_t operator () (const std::string &t) const {return __gnu_cxx::__stl_hash_string(t.c_str());} // 利用系统定义的字符串hash函数
};
struct equal2cpp_1{bool operator () (const std::string &t1, const std::string &t2) const {return t1 == t2;}};
void test1_cpp_2_hash_selfdef2()
{
#ifdef __linux__
    __gnu_cxx::hash_map<std::string, std::string, hash2_cpp_1> hmss; // hash_map<std::string, std::string>编译不过
    // __gnu_cxx::hash_map<string, string, hash2_cpp_1, equal2cpp_1> hmss;
#else
    stdext::hash_map<string, string> hmss;  // vs2019
#endif

    hmss["1"] = "111";
    hmss["2"] = "222";
    hmss["3"] = "333";
    for (auto it : hmss)
    {
        printf("%s : %s\n", it.first.c_str(), it.second.c_str());
    }
    printf("szie:%ld bucket_count:%ld\n", hmss.size(), hmss.bucket_count()); // 元素个数 桶大小
// 3 : 333
// 2 : 222
// 1 : 111
// szie:3 bucket_count:193

    std::unordered_map<std::string, std::string> umss;
    umss["11"] = "111";
    umss["12"] = "222";
    umss["13"] = "333";
    for (auto it : umss)
    {
        printf("%s : %s\n", it.first.c_str(), it.second.c_str());
    }
    printf("szie:%ld bucket_count:%ld\n", umss.size(), umss.bucket_count());
// 13 : 333
// 12 : 222
// 11 : 111
// szie:3 bucket_count:13
}



