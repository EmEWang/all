#include "cpp11_1.h"

using namespace std;



void test1_cpp11_1_for()
{
    // 基于范围的for循环
    // for (元素类型 元素对象：容器对象)
    // {
    //     循环体
    // }
    //
    // 如果循环体由单条语句或者单个结构块组成，可以省略花括号
    // 用元素对象依次结合容器对象中的每一个元素，每结合一个元素，执行依次循环体，直至容器内的所有元素都被结合完为止.
    // 不依赖于下标元素，通用
    // 不需要访问迭代器，透明
    // 不需要定义处理函数，简洁
}


void test1_cpp11_1_listinitialization()
{
    // 1 C++98中允许{}对数组元素进行统一的列表初始值设定
    {
        int array1[] = { 1,2,3,4,5 };
        int array2[5] = { 0 };

        // 对于一些自定义的类型，却无法使用这样的初始化。
        vector<int> v{ 1,2,3,4,5 }; // C++98无法编译  每次定义vector时，都需要先把vector定义出来，然后使用循环对其赋初始值
    }

    // C++11扩大了{}(初始化列表)的使用范围，所有的内置类型和用户自定义的类型，使用初始化列表时，可添加等号(=)，也可不添加。
    // 注意：列表初始化可以在{}之前使用等号，其效果与不使用=没有什么区别。
    // 2 内置类型的列表初始化
    {
        // 内置类型变量
        int x1 = { 10 };
        int x2{ 10 };  // 同上 建议使用原来的
        int x3 = 1 + 2;
        int x4 = { 1 + 2 };
        int x5{ 1 + 2 };
        // 数组
        int arr1[5] { 1,2,3,4,5 };
        int arr2[5] = { 1,2,3,4,5 };
        int arr3[]{ 1,2,3,4,5 };
        int arr4[] = { 1,2,3,4,5 };
        // 动态数组，在C++98中不支持
        int* arr5 = new int[5]{ 1,2,3,4,5 };
        // 标准容器
        vector<int> v{ 1,2,3,4,5 }; // 这种初始化就很友好，不用push_back一个一个插入
        vector<int> v2 = { 1,2,3,4,5 };
        map<int, int> m{ {1,1}, {2,2,},{3,3},{4,4} };
        map<int, int> m2 = { {1,1}, {2,2,},{3,3},{4,4} };
    }

    // 标准库支持单个对象的列表初始化
    {
        class Point {
        public:
            Point(int x = 0, int y = 0) : _x(x), _y(y) {}
        private:
            int _x;
            int _y;
        };

        Point p = { 1, 2 };
        Point p2{ 1, 2 };//不建议
    }
}


#include <initializer_list>
template <class T>
class Vector {
public:
    Vector(initializer_list<T> l) : _capacity(l.size()), _size(0) {
        _array = new T[_capacity];
        for (auto e : l)
            _array[_size++] = e;
    }

    Vector<T>& operator=(initializer_list<T> l) {
        delete[] _array;
        size_t i = 0;
        for (auto e : l)
            _array[i++] = e;
        return *this;
    }
private:
    T* _array;
    size_t _capacity;
    size_t _size;
};
template <class T>
class Vector2 {
public:
    //Vector2() : _capacity(0), _size(0)
    //{
    //    _array = NULL;
    //}
private:
    T* _array;
    size_t _capacity;
    size_t _size;
};
void test1_cpp11_1_listinitialization2()
{
    // 多个对象的列表初始化
    // 多个对象想要支持列表初始化，需给该类(模板类)添加一个带有initializer_list(系统自定义的类模板)类型参数的构造函数。
    // 该类模板中主要有三个方法：begin()、end()迭代器以及获取区间中元素个数的方法size()
    {
        class Date
        {
        public:
            Date(int year = 0, int month = 1, int day = 1):_year(year), _month(month), _day(day){
                cout << "这是日期类" << endl;
            }

        private:
            int _year;
            int _month;
            int _day;
        };

        // C++11容器都实现了带有initializer_list类型参数的构造函数
        vector<Date> vd = { { 2021, 1, 11 }, Date{ 2022, 2, 12 }, { 2023, 3, 13 } };
        int size = vd.size();
    }

    {
        // 自定义类型 添加 initializer_list
        Vector<int> vin{ 5,4,3,2,2,1 };
        // Vector2<int> vin2{ 5,4,3,2,2,1 };   // 错误 C2440 “初始化” : 无法从“initializer list”转换为“Vector2<int>”
    }
}


void error_msg(initializer_list<string> str)      // 可变参数，所有参数类型一致
{
    for (auto beg = str.begin(); beg != str.end(); ++beg)
        cout << *beg << " ";
    cout << endl;
}
void test1_cpp11_1_listinitialization3()
{
    // initializer_list<T> lst;   // 默认初始化；T类型元素的空列表
    // initializer_list<T> lst{ a,b,c... };  // lst的元素数量和初始值一样多 lst的元素是对应初始值的副本
    // lst2(lst);
    // lst3 = lst;   // 拷贝或赋值一个initializer_list对象不会拷贝列表中的元素；拷贝后，原始列表和副本元素共享
    // lst.size();   // 列表中的元素数量
    // lst.begin();  // 返回指向lst中首元素的指针
    // lst.end();    // 返回指向lst中尾元素下一位置的指针

    // C++标准中一个非常轻量级的表示初始化器列表的类模板initializer_list及有关函数。
    // 为了编写能够处理不同数量实参(但是类型相同)，C++11新标准提供了initializer_list的方法。
    // 与vector不同的是，initializer_list对象中的元素永远是常量值，无法改变initializer_list对象中元素的值。
    // 在进行函数调用的时候需要使用花括号将所有的参数括起来。
    string error1 = "error1";
    string well = "well";
    // 调用
    error_msg({ "hello","error",error1 });     // error为string类型
    error_msg({ "hello2",well });              // well为string类型
}



void test1_cpp11_1_auto()
{
    // C++11中，使用auto来根据变量初始化表达式类型推导变量的实际类型，而且更加简洁。
    // 在定义变量时，必须先给出变量的实际类型，编译器才允许定义，但有些情况下可能不知道需要实际类型怎么给，或类型写起来特别复杂
    short a = 32670;
    short b = 32670;

    // c如果给成short，会造成数据丢失，如果能够让编译器根据a+b的结果推导c的实际类型，就不会存在问题
    short c = a + b;
    auto d = a + b;
    std::map<std::string, std::string> m{ { "apple", "苹果" }, { "banana", "香蕉" } };
    // 使用迭代器遍历容器, 迭代器类型太繁琐
    std::map<std::string, std::string>::iterator it = m.begin();
    while (it != m.end()) {
        cout << it->first << " " << it->second << endl;
        ++it;
    }
    auto its = m.begin();
    while (its != m.end()) {
        cout << its->first << " " << its->second << endl;
        ++its;
    }
}


void* GetMemory(size_t size){return malloc(size);}
template<class T1, class T2>
T1 Add(const T1& left, const T2& right){return left + right;}
void test1_cpp11_1_decltype()
{
    // 1 为什么需要decltype
    // auto使用的前提是：必须要对auto声明的类型进行初始化，否则编译器无法推导出auto的实际类型。
    // 但有时候可能需要根据表达式运行完成之后结果的类型进行推导，因为编译期间，代码不会运行，此时auto也就无能为力。
    // 如 上面的模板 T1 Add(const T1& left, const T2& right)
    // 如果能用加完之后结果的实际类型作为函数的返回值类型就不会出错，
    // 但这需要程序运行完才能知道结果的实际类型，即RTTI(Run - Time Type Identiﬁcation 运行时类型识别)。

    // 2 decltype
    // decltype是根据表达式的实际类型推演出定义变量时所用的类型，比如：
    double a = 10.9887;
    int b = 20;
    decltype(a + b) c;
    c = a + b;
    cout << typeid(c).name() << endl;             // double
    cout << c << endl;                            // 30.98807

    // 推演函数返回值的类型
    // 如果没有带参数，推导函数的类型
    cout << typeid(decltype(GetMemory)).name() << endl;   // void * __cdecl(unsigned int)
    // 如果带参数列表，推导的是函数返回值的类型,注意：此处只是推演，不会执行函数
    cout << typeid(decltype(GetMemory(0))).name() << endl;  // void*
}

template<typename T>
void printtype(T t){printf("type:%s\n", typeid(t).name());}
template<typename T>
void printtype(){printf("type:%s\n", typeid(T).name());}
void test1_cpp11_1_decltype2()
{
    int i = 4;
    int arr[5] = { 0 };
    int *ptr = arr;
    struct S{ double d; }s;
    void Overloaded(int);
    void Overloaded(char); // 重载的函数
    int && RvalRef();
    const bool Func(int);
    const bool& Func2(int);

// # define printvar(var)  {std::cout << #var << " ";printtype(var);}
# define printvar(var)  {std::cout << #var << " ";print_param_type<decltype(var)>();}
    // 规则一：推导为其类型
    decltype (arr) var1;              printvar(var1)  //var1 int [5]   标记符表达式
    decltype (ptr) var2;              printvar(var2)  //var2 int*      标记符表达式
    decltype (s.d) var3;              printvar(var3)  //var3 double    成员访问表达式
    //d ecltype(Overloaded) var4;//重载函数。编译错误。

    // 规则二：将亡值。推导为类型的右值引用。
    decltype (RvalRef()) var5 = 1;    printvar(var5)  // var5 int&&
    // std::cout << typeid(var5).name() << std::endl;

    // 规则三：左值，推导为类型的引用。
    decltype ((i))var6 = i;           printvar(var6)  //var6 int&
    decltype (true ? i : i) var7 = i; printvar(var7)  //var7 int&  条件表达式返回左值
    decltype (++i) var8 = i;          printvar(var8)  //var8 int&  ++i返回i的左值
    decltype(arr[5]) var9 = i;        printvar(var9)  //var9 int&  []操作返回左值
    decltype(*ptr)var10 = i;          printvar(var10) //var10 int& *操作返回左值
    decltype("hello")var11 = "hello"; printvar(var11) //var11 const char (&)[6]  字符串字面常量为左值，且为const左值。

    // 规则四：以上都不是，则推导为本类型
    decltype(1) var12;                printvar(var12) //var12 int
    decltype(Func(1))  var13=true;    printvar(var13) //var13 bool
    decltype(Func2(1)) var14=true;    printvar(var14) //var14 const bool&   注意这个与上面的差异
    decltype(i++) var15 = i;          printvar(var15) //var15 int i++返回右值
    // std::cout << (typeid(var6) == typeid(int&)) << std::endl;

    print_param_type<decltype (i),  decltype ((i))>();  //int   int&
    print_param_type<typename std::enable_if<true>::type>();  //void    std::enable_if默认
}

class Student{
public:
    static int total;
    string name;
    int age;
    float scores;
    int x;
};
void test1_cpp11_1_decltype3()
{
    {
    cout << "1---" << endl;
    // 1.1变量
    int n = 0;
    const int &r = n;
    Student stu;
    decltype(n) a = n; print_param_type<decltype(n)>();  //int   因为按规则1  n 为 int 类型
    decltype(r) b = n; print_param_type<decltype(r)>();  //const int&  理由同上
    // 1.2类成员访问表达式
    decltype(Student::total) c = 0; print_param_type<decltype(Student::total)>(); //int total为Student 的 int 成员变量
    decltype(stu.name) url = "www"; print_param_type<decltype(stu.name)>();//std::__cxx11::basic_string<char> 理由同上
    }

    {
    cout << "2---" << endl;
    // 2函数声明
    int& func_int_r(int, char);            //返回值为 int&
    int&& func_int_rr(void);               //返回值为 int&&
    int func_int(double);                  //返回值为 int
    const int& fun_cint_r(int, int, int);  //返回值为 const int&
    const int&& func_cint_rr(void);        //返回值为 const int&&
    //decltype类型推导
    int n = 100;
    decltype(func_int_r(100, 'A')) a = n; print_param_type<decltype(func_int_r(100, 'A'))>(); //int&   规则2
    decltype(func_int_rr()) b = 0;        print_param_type<decltype(func_int_rr())>();        //int&&
    decltype(func_int(10.5)) c = 0;       print_param_type<decltype(func_int(10.5))>();       //int
    decltype(fun_cint_r(1,2,3))  x = n;   print_param_type<decltype(fun_cint_r(1,2,3))>();    //const int &
    decltype(func_cint_rr()) y = 0;       print_param_type<decltype(func_cint_rr())>();       //const int&&
    }

    {
    cout << "3---" << endl;
    // 3左值或被()包围
    Student obj;
    //带有括号的表达式
    decltype(obj.x) a = 0;   print_param_type<decltype(obj.x)>();   //int   obj.x 为类成员访问表达式，按规则1
    decltype((obj.x)) b = a; print_param_type<decltype((obj.x))>(); //int&  obj.x 带有括号，按规则3
    //加法表达式
    int n = 0, m = 0;
    decltype(n + m) c = 0;     print_param_type<decltype(n + m)>(); //int  n+m 得到一个右值，按规则1
    decltype(n = n + m) d = c; print_param_type<decltype(n = n + m)>(); //int&  n=n+m 得到一个左值，按规则3
    }

    {
    cout << "4---" << endl;
    // 4区别 cv限制符   const 和 volatile 关键字的统称
    // const 关键字用来表示数据是只读的，也就是不能被修改；
    // volatile 和 const 是相反的，它用来表示数据是可变的、易变的，目的是不让 CPU 将数据缓存到寄存器，而是从原始的内存中读取。
    // 推导变量类型时，auto 和 decltype 对 cv 限制符的处理不同。decltype 会保留 cv 限定符，而 auto 有可能会去掉 cv 限定符。
    // auto 关键字对 cv 限定符的推导规则：
    //   如果表达式的类型不是指针或者引用，auto 会把 cv 限定符直接抛弃，推导成 non-const 或者 non-volatile 类型。
    //   如果表达式的类型是指针或者引用，auto 将保留 cv 限定符。
    //非指针非引用类型
    const int n1 = 0;
    auto n2 = 10;             print_param_type<decltype(n2)>();   // int
    n2 = 99;  //赋值不报错
    decltype(n1) n3 = 20;     print_param_type<decltype(n3)>();   // const int
    // n3 = 5;  //赋值报错

    //指针类型
    const int *p1 = &n1;
    auto p2 = p1;             print_param_type<decltype(p2)>();   // const int*
    // *p2 = 66;  //赋值报错
    decltype(p1) p3 = p1;     print_param_type<decltype(p3)>();   // const int*
    // *p3 = 19;  //赋值报错
    }
    {
    cout << "5---" << endl;
    // 5区别 引用
    // 当表达式的类型为引用时，auto 和 decltype 的推导规则也不一样；
    // decltype 会保留引用类型，而 auto 会抛弃引用类型，直接推导出它的原始类型。
    int n = 10;
    int &r1 = n;
    //auto推导
    auto r2 = r1;             print_param_type<decltype(r2)>();   // int
    r2 = 20;
    cout << n << ", " << r1 << ", " << r2 << endl; // 10, 10, 20
    //decltype推导
    decltype(r1) r3 = n;      print_param_type<decltype(r3)>();    // int&
    r3 = 99;
    cout << n << ", " << r1 << ", " << r3 << endl; // 99, 99, 99
    }

}

void test1_cpp11_1_type()
{
    int a = 10;
    int &ra = a;
    int &&rra = 10;
    int *pa = &a;

    void f0();
    int f1(int*,int);
    float* f2(int*,int,int*,float*);
    char* f3(float*,const int*,int*,float*,const int*);

    printf("int:%s 10:%s int&:%s int&&:%s\n",
        typeid(a).name(),typeid(10).name(), typeid(ra).name(),typeid(rra).name());
    printf("int:%s int&:%s int&&:%s\n",
        typeid(int).name(),typeid(int&).name(),typeid(int&&).name());
    printf("int == int&:%d int*:%s\n",
        typeid(a) == typeid(ra), typeid(pa).name());
    printf("f0:%s f1:%s f2:%s f3:%s\n",
        typeid(f0).name(),typeid(f1).name(),typeid(f2).name(),typeid(f3).name());

    // int:i 10:i int&:i int&&:i
    // int:i int&:i int&&:i
    // int == int&:1 int*:Pi
    // f0:FvvE f1:FiPiiE f2:FPfPiiS0_S_E f3:FPcPfPKiPiS0_S2_E
}

void test1_cpp11_1_type2()
{
    using namespace std;
    int a = 1;
    string s = "";
    cout << GetClearName(typeid(int&)) << endl;          // i -> int
    cout << GetClearName(typeid(vector<int>&)) << endl;  // St6vectorIiSaIiEE -> std::vector<int, std::allocator<int> >
    cout << type_name<const int&>() << endl;             // const int&
    print_param_type(string{"42"});                      // std::__cxx11::basic_string<char>&&
    print_param_type(s);                                 // std::__cxx11::basic_string<char>&
    print_param_type(3);                                 // int&&
    print_param_type(move(a));                           // int&&
    print_param_type(a);                                 // int&
    print_param_type<int, float>();                      // int  float
}

void test1_cpp11_1_type3()
{
    using namespace std;
    int a = 1;
    int b = 1;
    int &c = a;

    // typeid 方式
    typeid(a) == typeid(b)? cout << "yes\n" : cout << "no";   // yes
    typeid(a) == typeid(c)? cout << "yes\n" : cout << "no";   // yes

    // tmp 方式
    is_same_v<decltype(a),decltype(b)>?cout << "yes\n" : cout << "no\n";   // yes
    is_same_v<decltype(a),decltype(c)>?cout << "yes\n" : cout << "no\n";   // no
}

void test1_cpp11_1_sync_with_stdio()
{
    // static bool sync_with_stdio( bool sync = true );
    std::ios::sync_with_stdio(true);
    std::cout << "a\n";
    std::printf("b\n");
    std::cout << "c\n";

    std::ios::sync_with_stdio(false);
    std::cout << "1\n";
    std::printf("2\n");
    std::cout << "3\n";
}

class demo
{
public:
    demo(){printf("demo construct\n");}
    demo(int i){printf("demo construct int\n");}
    demo(const demo&other){printf("demo copy construct\n");}
    demo(demo&&other){printf("demo move construct\n");}
    demo& operator =(const demo&other){printf("demo assignment\n");return *this;}
    ~demo(){printf("demo destruct\n");}
};
demo getdemo(){return demo();}
void test1_cpp11_1_demo()
{
    // demo da = 1;
    demo de = getdemo();

    // 去掉优化后 实际输出 未定义移动构造函数之前
    // demo construct            <-- 执行 demo()
    // demo copy construct       <-- 执行 return demo()
    // demo destruct             <-- 销毁 demo() 产生的匿名对象
    // demo copy construct       <-- 执行 de = getdemo()
    // demo destruct             <-- 销毁 getdemo() 返回的临时对象
    // ----
    // demo destruct             <-- 销毁 de

    // 优化后    实际输出 未定义移动构造函数之前
    // demo construct
    // ----
    // demo destruct


    // 去掉优化后 实际输出 定义移动构造函数之后
    // 当类中同时包含拷贝构造函数和移动构造函数时，使用临时对象初始化当前类的对象，编译器会优先调用移动构造函数来完成此操作。
    //   只有当类中没有合适的移动构造函数时，编译器才会退而求其次，调用拷贝构造函数。
    // 在实际开发中，通常在类中自定义移动构造函数的同时，会再为其自定义一个适当的拷贝构造函数，
    //   由此当用户利用右值初始化类对象时，会调用移动构造函数；使用左值(非右值)初始化类对象时，会调用拷贝构造函数。
    // demo construct
    // demo move construct
    // demo destruct
    // demo move construct
    // demo destruct
    // ----
    // demo destruct

    // 优化后   实际输出 定义移动构造函数之后
    // demo construct
    // ----
    // demo destruct

    std::cout << "----"<< std::endl;
    // demo de3 = de;              // 拷贝构造函数
    // demo de4 = std::move(de);   // 移动构造函数
}
void test1_cpp11_1_demo2()
{
    {
    std::string str = "abc";
    std::string str2 = "123";

    std::vector<std::string> vct;
    vct.push_back(str);
    vct.push_back(move(str2));
    vct.emplace_back("sss");     // 不需要拷贝或者移动 直接在末尾构造

    // 使用move传递左值时，还需要注意一点就是：td::move()可以应用于左值，但是用后就表示当前的值不再需要了，
    // 如果后续使用了该值，则会产生意想不到的结果。
    std::cout << "str:"<< str << std::endl;    // str:abc
    std::cout << "str2:"<< str2 << std::endl;  // str2:
    }
    {
    demo de;
    std::vector<demo> vct;
    printf("1 拷贝\n");
    vct.push_back(de);
    printf("2 移动\n");
    vct.push_back(std::move(de));
    printf("3 emplace_back\n");
    vct.emplace_back();
    std::cout << "----"<< std::endl;
    // 使用/不使用 -fno-elide-constructors 结果一样
    // demo construct
    // 1 拷贝
    // demo copy construct
    // 2 移动
    // demo move construct
    // demo copy construct
    // demo destruct
    // 3 emplace_back
    // demo construct
    // demo copy construct
    // demo copy construct
    // demo destruct
    // demo destruct
    // ----
    // demo destruct
    // demo destruct
    // demo destruct
    // demo destruct

    // 解析 看以上情况
    // push_back(move(de)) 先移动 再拷贝
    // emplace_back() 先构造 再拷贝
    }
}




class ClassA{
public:
    ClassA(int a) : _a(a) {}
    ClassA() = default;                 // 显式缺省构造函数，由编译器生成
    ClassA& operator=(const ClassA& a); // 在类中声明，在类外定义时让编译器生成默认赋值运算符重载
private:
    int _a;
};
// ClassA& ClassA::operator=(const ClassA& a){ return *this; } // 类外实现
ClassA& ClassA::operator=(const ClassA& a) = default;          // 类外default
void test1_cpp11_1_default_delete()
{
    // 在C++中对于空类，编译器会生成一些默认的成员函数，
    // 如：构造函数、拷贝构造函数、运算符重载、析构函数和& 和const& 的重载、移动构造、移动拷贝构造等函数。
    // 如果在类中显式定义了，编译器将不会重新生成默认版本。
    // 有时候这样的规则可能被忘记，最常见的是声明了带参数的构造函数，必要时则需要定义不带参数的版本以实例化无参的对象。
    // 而且有时编译器会生成，有时又不生成，容易造成混乱，于是C++11让程序员可以控制是否需要编译器生成。

    // 1 显式缺省函数
    // 在C++11中，在默认函数定义或者声明时加上 = default (表示显式缺省函数)，从而显式的指示编译器生成该函数的默认版本。
    {
        class A {
        public:
            A(int a) : _a(a) {}
            A() = default; // 1.1 显式缺省构造函数，由编译器生成，比用户自己定义的默认构造函数获得更高的代码效率
            A(A& a) = default;
            A(A&& a) = default;

            // 1.2 "=default"函数既可以在类内定义(inline)，也可以在类外定义(out-of-line)。
            // A& operator=(const A& a);  // 类内声明 类外default
            A& operator=(const A& a) = default;    // 类内default
            A& operator=(A&& a) = default;         // 类内default
            // A& operator=(const A& a) { return *this; }; // 局部类只能类内实现 不能在类外实现
            ~A() = default;            // 局部类只能类内实现default 析构函数  不能在类外

            // 1.3 "=default" 仅适用于类的特殊成员函数，且该特殊成员函数没有默认参数。
            // int f() = default;      // error , 函数 f() 非类 X 的特殊成员函数
            // A(int, int) = default;  // error , 构造函数 A(int, int) 非 X 的特殊成员函数
            // A(int = 1) = default;   // error , 默认构造函数 A(int=1) 含有默认参数
        private:
            int _a;
        };
        // A& A::operator=(const A& a) {return *this;}; // 拷贝赋值操作符 全局类可类外实现  见ClassA
        // A& A::operator=(const A& a) = default;       // 拷贝赋值操作符 全局类可类外defaulted  见ClassA
        A a1(10);
        A a2;
        a2 = a1;
    }

    // 2 禁用/删除默认函数
    // 如果能想要限制某些默认函数的生成，在C++98中，是该函数设置成private，并且不给定义，这样只要其他人想要调用就会报错。
    // 在C++11中，只需在该函数声明加上 = delete (表示删除函数)即可，该语法指示编译器不生成对应函数的默认版本。
    {
        class A {
        public:
            A() = default;
            A(int a) : _a(a) {}              // 定义了一个构造函数 则默认构造函数必须显示指明 否则不会生成
            A(const A&) = delete;            // 2.1 禁止编译器生成默认的拷贝构造函数
            A& operator=(const A&) = delete; // 禁止编译器生成默认的赋值运算符重载

            // 2.2 "=delete"函数特性还可用于禁用类的某些转换构造函数，从而避免不期望的类型转换
            A(double)= delete;

            // 2.3 "=delete"函数特性还可以用来禁用某些用户自定义的类的 new 操作符，从而避免在自由存储区创建类的对象
            void *operator new(size_t) = delete;
            void *operator new[](size_t) = delete;
        private:
            int _a;
        };

        A a1(10);
        // A a2(a1);  // 编译失败，拷贝构造函数被禁用
        A a3(20);
        // a3 = a2;   // 编译失败，拷贝赋值操作符被禁用
        // A *pa = new A;      // 编译失败，new 操作符被禁用
        // A *pb = new A[10];  // 编译失败，new[] 操作符被禁用
    }
}



void test1_cpp11_1_override_final()
{
    // override作用是检查派生类虚函数是否重写了基类某个虚函数，如果没有重写编译报错
    // 可以避免 “在继承的时候写错了函数(参数类型、参数个数不符)，编译没问题但是程序运行时和预想的不一样”
    // 建议重写虚函数的时候加上 override
    {
        class A {
            virtual void foo() {};
            void bar() {};
        };

        class B:A {
            void foo() override {};       // OK：B::foo 覆盖 A::foo
            // void foo() const override; // 错误：B::foo 不覆盖 A::foo (签名不匹配)
            // void bar() override;       // 错误：A::bar 非虚
            // void bar2() override;      // 错误：A::bar2 不存在
        };
    }

    {
        //作用：指定某个虚函数不能在子类中被覆盖，或者某个类不能被子类继承。
        class Base {
            virtual void foo() {};
        };

        class A : Base {
            void foo() final {}; // Base::foo 被覆盖而 A::foo 是最终覆盖函数
            // void bar() final; // 错误：非虚函数不能被覆盖或是 final
        };

        class B final : A {      // class B 为 final
            // void foo() override; // 错误：foo 不能被覆盖，因为它在 A 中是 final
        };

        // class C:B {}; // 错误：B 为 final
    }
}


template <class T>
class clsX{
public:
    clsX() = default;

    template <class U>
    void get(U v){std::cout << "get:" << v << std::endl;}

    template <class U>
    static void get2(U v){std::cout << "get2:" << v << std::endl;}
};
void test1_cpp11_1_cls_tmp()
{
    clsX<int> cl1;
    cl1.get<int>(123);
    cl1.get(1234);
    clsX<int>::get2<int>(123);
}





// 引用折叠规则
// 当实参为左值或者左值引用（A&）时，函数模板中 T&& 将转变为 A&（A& && = A&）；
// 当实参为右值或者右值引用（A&&）时，函数模板中 T&& 将转变为 A&&（A&& && = A&&）

// 在实现完美转发时，只要函数模板的参数类型为 T&&，则 C++ 可以自行准确地判定出实际传入的实参是左值还是右值。
template <typename T>
void func_call(T&& t)
{
    //printf("call t:%d\n", t);
    std::cout << (std::is_lvalue_reference<T>::value?" lvalue_call:":" rvalue_call:")
        << t << " addr:%x" << &t <<std::endl;

    //t = 0;
    t = typename std::remove_reference<T>::type();     // 必须用 typename 指明是个类型
}


// is_reference (C++11) 检查类型是否为左值引用或右值引用 (类模板)
// is_rvalue_reference (C++11) 检查类型是否为右值引用 (类模板)
// is_lvalue_reference (C++11) 检查类型是否为左值引用 (类模板)
// 由此可知 无论左值还是右值 都能接受 其t要么变为左值引用 要么变为右值引用
// 函数中当前变量t为右值引用 其用它在调用其他函数func(t) 此时变为左值 因为当前t 能取其地址
template <typename T>
void func_perfect(T&& t)
{
    std::cout << "call:" << t << " addr:%x " << &t
        << (std::is_lvalue_reference<T>::value?" lvalue_reference":" rvalue_reference");
    func_call(t);
}

// 通过将函数模板的形参类型设置为 T&&，我们可以很好地解决接收左、右值的问题。
// 但除此之外，还需要解决一个问题，即无论传入的形参是左值还是右值，对于函数模板内部来说，形参既有名称又能寻址，
// 因此它都是左值。那么如何才能将函数模板接收到的形参连同其左、右值属性，一起传递给被调用的函数呢？

// C++11 标准的开发者已经帮我们想好的解决方案，该新标准还引入了一个模板函数 forword()，
// 我们只需要调用该函数，就可以很方便地解决此问题。仍以 function 模板函数为例，如下演示了该函数模板的用法：
template <typename T>
void func_call2(T& t){
    std::cout << " lvalue_call:" << t << " addr:%x" << &t<< std::endl;
    t = typename std::remove_reference<T>::type();
}
template <typename T>
void func_call2(const T& t){
    std::cout << " rvalue_call:" << t << " addr:%x" << &t<< std::endl;
    //t = typename std::remove_reference<T>::type();   // 不能改变
}
template <typename T>
void func_perfect2(T&& t){
    std::cout << "call:" << t << " addr:%x" << &t
        << (std::is_lvalue_reference<T>::value?" lvalue_reference":" rvalue_reference");
    func_call2(std::forward<T>(t));
}
void test1_cpp11_1_perfect()
{
    {
    printf("万能引用\n");
    // int n1 = int();
    int n = 5;
    int m = 6;
    int &rn = n;
    int &&rrn = 10;
    std::string str = "qwe";
    std::cout << "rn ";func_perfect(rn);
    std::cout << "m ";func_perfect(m);
    std::cout << "9 ";func_perfect(9);
    std::cout << "rrn ";func_perfect(rrn);
    std::cout << "str ";func_perfect(str);
    printf("n:%d m:%d rn:%d rrn:%d str:%s\n", n, m, rn, rrn, str.c_str());

    printf("1 ---\n");

    // 万能引用
    // rn call:5 addr:%x 0x7ffd5617b214 lvalue_reference lvalue_call:5 addr:%x0x7ffd5617b214
    // m call:6 addr:%x 0x7ffd5617b218 lvalue_reference lvalue_call:6 addr:%x0x7ffd5617b218
    // 9 call:9 addr:%x 0x7ffd5617b220 rvalue_reference lvalue_call:9 addr:%x0x7ffd5617b220
    // rrn call:10 addr:%x 0x7ffd5617b21c lvalue_reference lvalue_call:10 addr:%x0x7ffd5617b21c
    // str call:qwe addr:%x 0x7ffd5617b250 lvalue_reference lvalue_call:qwe addr:%x0x7ffd5617b250
    // n:0 m:0 rn:0 rrn:0 str:
    // 1 ---
    }

    {
    printf("万能引用 + 完美转发\n");
    // int n1 = int();
    int n = 5;
    int m = 6;
    int &rn = n;
    int &&rrn = 10;
    std::string str = "qwe";
    std::cout << "rn ";func_perfect2(rn);
    std::cout << "m ";func_perfect2(m);
    std::cout << "9 ";func_perfect2(9);
    std::cout << "rrn ";func_perfect2(rrn);
    std::cout << "str ";func_perfect2(str);
    printf("n:%d m:%d rn:%d rrn:%d str:%s\n", n, m, rn, rrn, str.c_str());
    printf("2 ---\n");

    // 万能引用 + 完美转发
    // rn call:5 addr:%x0x7ffd5617b210 lvalue_reference lvalue_call:5 addr:%x0x7ffd5617b210
    // m call:6 addr:%x0x7ffd5617b214 lvalue_reference lvalue_call:6 addr:%x0x7ffd5617b214
    // 9 call:9 addr:%x0x7ffd5617b218 rvalue_reference rvalue_call:9 addr:%x0x7ffd5617b218
    // rrn call:10 addr:%x0x7ffd5617b220 lvalue_reference lvalue_call:10 addr:%x0x7ffd5617b220
    // str call:qwe addr:%x0x7ffd5617b250 lvalue_reference lvalue_call:qwe addr:%x0x7ffd5617b250
    // n:0 m:0 rn:0 rrn:0 str:
    // 2 ---
    }

    int *pi = nullptr;
    int n =11;
    printf("%s\n", std::is_lvalue_reference<int&>::value?"lvalue_reference":"rvalue_reference");
    printf("3 ---\n");

    // lvalue_reference
    // 3 ---
}

void otherdef(int & t) {cout << "lvalue\n";}
void otherdef(const int & t) {cout << "rvalue\n";}
//重载函数模板，分别接收左值和右值
template <typename T>void functperf03(const T& t) {otherdef(t);}  //接收右值参数
template <typename T>void functperf03(T& t) {otherdef(t);}        //接收左值参数
void test1_cpp11_1_perfect2()
{
    // 事实上，C++98/03 标准下的 C++ 也可以实现完美转发，只是实现方式比较笨拙。
    // C++ 98/03 标准中只有左值引用，并且可以细分为非 const 引用和 const 引用。
    // 其中，使用非 const 引用作为函数模板参数时，只能接收左值，无法接收右值；
    // 而 const 左值引用既可以接收左值，也可以接收右值，但考虑到其 const 属性，
    // 除非被调用函数的参数也是 const 属性，否则将无法直接传递。
    // 这也就意味着，单独使用任何一种引用形式，可以实现转发，但无法保证完美。
    // 因此如果使用 C++ 98/03 标准下的 C++ 语言，我们可以采用函数模板重载的方式实现完美转发
    // 显然，使用重载的模板函数实现完美转发也是有弊端的，此实现方式仅适用于模板函数仅有少量参数的情况，
    // 否则就需要编写大量的重载函数模板，造成代码的冗余。
    int a = 10;
    functperf03(a);   // lvalue
    functperf03(10);  // rvalue
}


// 模板参数的按值传递和引用传递
template<typename Fn,typename ...Args>
auto call_by_value(Fn &&fn,Args... args){
    return fn(args...);
}
void func(int &a){
    a = 1;
}
void test1_cpp11_1_ref()
{
    int a = 0;
    call_by_value(func,a);           // 模板 默认按值传递
    std::cout << a << std::endl;

    call_by_value(func,std::ref(a)); // ref 底层以指针形式存储 实现引用方式传递
    std::cout << a << std::endl;
    // typename std::enable_if<true>::type;
}





// std::bind
// 头文件是<functional>，是一个函数适配器，接受一个可调用对象(callable object)，生成一个新的可调用对象来“适应”原对象的参数列表。

// std::bind函数有两种函数原型，定义如下：
// template< class F, class... Args >
// /*unspecified*/ bind( F&& f, Args&&... args );

// template< class R, class F, class... Args >
// /*unspecified*/ bind( F&& f, Args&&... args );

// std::bind返回一个基于f的函数对象，其参数被绑定到args上。
// f的参数要么被绑定到值，要么被绑定到placeholders(占位符，如_1, _2, ..., _n)。

// std::bind将可调用对象与其参数一起进行绑定，绑定后的结果可以使用std::function保存。std::bind主要有以下两个作用：
// 将可调用对象和其参数绑定成一个防函数；只绑定部分参数，减少可调用对象传入的参数。

// 1 std::bind绑定普通函数
// double callableFunc (double x, double y) {return x/y;}
// auto NewCallable = std::bind (callableFunc, std::placeholders::_1,2);
// std::cout << NewCallable (10) << '\n';
// bind的第一个参数是函数名，普通函数做实参时，会隐式转换成函数指针。
// 因此std::bind(callableFunc,_1,2)等价于std::bind (&callableFunc,_1,2)；
// _1表示占位符，位于<functional>中，std::placeholders::_1；
// 第一个参数被占位符占用，表示这个参数以调用时传入的参数为准，调用NewCallable时，传入了10，其实就相当于调用callableFunc(10,2);

// 2 std::bind绑定一个成员函数
// class Base
// {
// public:
//     void display_sum(int a1, int a2)
//     {
//         std::cout << a1 + a2 << '\n';
//     }
//     int m_data = 30;
// };
// int main()
// {
//     Base base;
//     auto newiFunc = std::bind(&Base::display_sum, &base, 100, std::placeholders::_1);
//     f(20); // should out put 120.
// }
// bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
// 必须显式地指定&Base::diplay_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Base::display_sum前添加&；
// 使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &base；

// 3 绑定一个引用参数
// 默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中。
// 但是，与lambda类似，有时对有些绑定的参数希望以引用的方式传递，或是要绑定参数的类型无法拷贝。

// #include <iostream>
// #include <functional>
// #include <vector>
// #include <algorithm>
// #include <sstream>
// using namespace std::placeholders;
// using namespace std;

// ostream & printInfo(ostream &os, const string& s, char c)
// {
//     os << s << c;
//     return os;
// }

// int main()
// {
//     vector<string> words{"welcome", "to", "C++11"};
//     ostringstream os;
//     char c = ' ';
//     for_each(words.begin(), words.end(), [&os, c](const string & s){os << s << c;});
//     cout << os.str() << endl;

//     ostringstream os1;  // ostream不能拷贝，若希望传递给bind一个对象，就必须使用标准库提供的ref函数
//     for_each(words.begin(), words.end(), bind(printInfo, ref(os1), _1, c));
//     cout << os1.str() << endl;
// }
// bind函数与占位符
bool great_than(int first,int second){
    printf("first %d second %d\n", first, second);
    return first > second;
}
void test1_cpp11_1_bind(){
    std::vector<int> data = {1,2,3,4,5};
    //找到第一个大于3的元素
    auto it = std::find_if(std::cbegin(data),std::cend(data),std::bind(great_than,std::placeholders::_1,3));
    printf("第一个大于3的元素 %d\n", *it);
}




// std::placeholders 占位符。表示新的函数对象中参数的位置。当调用新的函数对象时，新函数对象会调用被调用函数，
//  并且其参数会传递到被调用函数参数列表中持有与新函数对象中位置对应的占位符。
//  _1用于代替回调函数中的第一个参数， _2用于代替回调函数中的第二个参数
void func2(int a, int b){
    printf("[1] %d [2] %d \n", a, b);
}
void func3(int a, int b, int c){
    printf("[1] %d [2] %d [3] %d\n", a, b, c);
}
struct class2: public std::binary_function<int, int, void>{
    // typedef int     first_argument_type;   // binary_function 有这些定义 若不继承必须自己定义
    // typedef int     second_argument_type;
    // typedef bool     result_type;
    void operator ()(int a, int b)const{   // const 必须有 要不然编译不过
        printf("[1] %d [2] %d \n", a, b);
        // return a < b;
    }
};
void goodbye(const std::string& s){
    std::cout << "Goodbye " << s << '\n';
}
class Object {
public:
    void hello(const std::string& s)
    {
        std::cout << "Hello " << s << '\n';
    }
};
void test1_cpp11_1_placeholders(){
    {
        auto f1 = std::bind(func3, 11, std::placeholders::_1, 13);
        f1(1,2,3,4,5);             // 占位符 返回的类型 参数不限 只需要有占位符位置的参数即可
        f1(2);
    }

    {
        typedef std::function<void (int)> fun_1;    // 仿函数
        fun_1 f1 = std::bind(func3, 111, std::placeholders::_1, 113);
        f1(12);
    }

    {
        // bind1st 必须用二元谓词 函数不行
        // 其返回值为 binder1st 类型 重载 的() 必须为 const
        auto it = std::bind1st(class2(), 11);      // 类型为 binder1st
        std::bind1st(class2(), 11)(1);             // 调用
        // binder1st<class2 >(class2(), 10)(5);    // 直接用类型调用
        // binder1st<less<int> >(less<int>(), 10)(5);
        // std::cout << typeid(it).name() << std::endl;
    }

    {
        // bind2nd 必须用二元谓词
        auto it = std::bind2nd(class2(), 22);
        std::bind2nd(class2(), 11)(1);
    }

    // 1 定义
    // namespace placeholders {
    // extern /* unspecified */ _1;
    // extern /* unspecified */ _2;
    // extern /* unspecified */ _3;
    // ...
    // }
    // 其中_1, _2, _3是未指定的数字对象，用于function的bind中。
    // _1用于代替回调函数中的第一个参数， _2用于代替回调函数中的第二个参数，以此类推。
    // #include <functional>
    // #include <string>
    // #include <iostream>
    {
        typedef std::function<void(const std::string&)> ExampleFunction;
        Object instance;
        std::string str("World");
        ExampleFunction f = std::bind(&Object::hello, &instance, std::placeholders::_1);
        f(str);   // equivalent to instance.hello(str)
        f = std::bind(&goodbye, std::placeholders::_1);
        f(str);   // equivalent to goodbye(str)
    }

    // 2 std::is_placeholder 用于判断T是否为占位符，它有一个成员变量value。
    //   如果T是placeholder类型，value的值为1代表 _1，2代表 _2；如果T不是，则value为0。
    // #include <iostream>     // std::cout, std::boolalpha
    // #include <functional>   // std::is_placeholder, std::placeholders
    {
        using namespace std::placeholders;  // introduces _1
        std::cout << std::is_placeholder<decltype(_1)>::value << '\n';   // 1
        std::cout << std::is_placeholder<decltype(_2)>::value << '\n';   // 2
        std::cout << std::is_placeholder<int>::value << '\n';            // 0
    }

    // 3 std::is_bind_expression 判断是否是bind表达式，有value成员，返回值是true或false
    // #include <iostream>     // std::cout, std::boolalpha
    // #include <functional>   // std::bind, std::plus, std::placeholders, std::is_bind_expression
    {
        using namespace std::placeholders;  // introduces _1
        auto increase_int = std::bind (std::plus<int>(),_1,1);
        std::cout << std::boolalpha;
        std::cout << std::is_bind_expression<decltype(increase_int)>::value << '\n';   // true
    }
}
