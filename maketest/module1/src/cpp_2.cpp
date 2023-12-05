#include "cpp_2.h"



using namespace std;

void test1_cpp_2_iterator()
{
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
        std::map<string, void*> map1;
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
        std::map<string, void*> map1;
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
        std::map<string, void*> map1;
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
    catch (const out_of_range& e) {
        cout << "Out of Range Exception at " << e.what();
    }

    {
        std::map<string, int> map1;
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


bool mycompare(std::string& strA, std::string& strB) {
    int lengA = strA.length();
    int lengB = strB.length();
    if (lengA < lengB) {
        int i = strB.find(strA.c_str());
        if (i == 0) {
            if (strB.at(i + lengA) == '.') {
                return false;
            }
            else {
                return true;
            }
        }
        return strA < strB;
    }
    if (lengA == lengB) {
        return strA < strB;
    }
    else {
        int i = strA.find(strB.c_str());
        if (i == 0) {
            if (strA.at(i + lengB) == '.') {
                return true;
            }
            else {
                return false;
            }
        }
        return strA < strB;
    }
}
bool mycompare2(std::string& strA, std::string& strB) {
    int lengA = strA.length();
    int lengB = strB.length();
    if (lengA < lengB) {
        return true;
    }
    if (lengA == lengB) {
        return strA < strB;
    }
    else {
        return false;
    }
}
void test1_cpp_2_list()
{
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



void test1_cpp_2_transform()
{
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
    // 格式 [captrue] (params) opt->ret{ body };
    // 其中 capture是捕获列表；params是参数列表；opt是函数选项；ret是返回值类型；body是函数体。
    {
        // lambda表达式的返回值通过返回值后置语法来定义，很多时候可以省略返回值类型，编译器根据return语句自动推导。
        auto f1 = [](int a) {return a + 1; };   //ok,return type is int
        // 但是初始化列表不能作为返回值的自动推导，需要显示给出具体的返回值类型。
        // auto f2_ = []() {return { 1,2 }; };       //error:无法推导出返回值类型
        // lambda表达式在没有参数列表的时候，参数列表可以省略。
        auto f3 = []() {return 1; };
        auto f4 = [] {return 1; }; //省略空参数表
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
        auto f1 = []() {cout << "a"; };
        auto f2 = []() {cout << "a"; };
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



