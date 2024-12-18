#include "cpp_1.h"





void test1_cpp_1_file()
{
    time_t now = time(0);
    std::ofstream fstr;
    fstr.open("11" , std::ifstream::binary);   // 创建文件
    // fstr.open("11", ios::in);               // 不创建文件
    int a = 0x1234;
    std::string str = "1234";

    if (!fstr.is_open()) {
        std::cout << "open file error" << std::endl;
        return;
    }

    fstr.clear();
    fstr.write((char *)&a,sizeof(a));
    fstr.write(str.c_str(), str.size());
    fstr.close();

    fstr.open("12", std::ios::trunc);     // ios::out | ios::binary | ios::ate | ios::app | ios::trunc 都创建文件
    if (!fstr.is_open()) {
        std::cout << "open file error" << std::endl;
        return;
    }
    fstr.close();
}

void test1_cpp_1_time()
{
    std::string str = "2022-06-09 13:33:33";
    int year = 2000, month = 1, day = 1, hour = 1, minute = 1, second = 1;
    int ret = sscanf(str.c_str(), "%d-%02d-%02d %02d:%02d:%02d", &year, &month, &day, &hour, &minute, &second);
    time_t t = time(0);
    str = ctime(&t);
    std::cout << str << std::endl;   // Fri Dec  1 09:27:44 2023
}

class base_cpp_1
{
    public:
    void a(){printf("base.a\n");}
    virtual void  b(){printf("base.b\n");}
};
class drive_cpp_1 : public base_cpp_1
{
    public:
    void a(){printf("drive.a\n");}
    virtual void  b(){printf("drive.b\n");}
};
void test1_cpp_1_class()
{
    drive_cpp_1 d;
    base_cpp_1* pb = new drive_cpp_1;
    drive_cpp_1* pd = new drive_cpp_1;

    d.a();                  // drive.a
    d.b();                  // drive.b
    d.base_cpp_1::a();      // base.a
    d.base_cpp_1::b();      // base.b
    pb->base_cpp_1::a();    // base.a
    pb->base_cpp_1::b();    // base.b
    pd->base_cpp_1::a();    // base.a
    pd->base_cpp_1::b();    // base.b
}


void test1_cpp_1_float_int()
{
    double d1 = 1.1;
    double d2 = -1.1;
    double d3 = DBL_MAX;
    double d4 = DBL_MAX + DBL_MAX;
    double d5 = DBL_MAX + 1.0e+292;
    double d6 = DBL_MAX + 1.0e+291;

    int i1 = _finite(d1);
    int i2 = _finite(d2);
    int i3 = _finite(d3);
    int i4 = _finite(d4);
    int i5 = _finite(d5);
    int i6 = _finite(d6);

    printf("i1 %d d1 = %f\n", i1, d1);
    printf("i2 %d d2 = %f\n", i2, d2);
    printf("i3 %d d3 = %f\n", i3, d3);
    printf("i4 %d d4 = %f %p\n", i4, d4,  &d4);
    printf("i5 %d d5 = %f\n", i5, d5);
    printf("i6 %d d6 = %f\n", i6, d6);
// i1 1 d1 = 1.100000
// i2 1 d2 = -1.100000
// i3 1 d3 = 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000
// i4 0 d4 = inf 0x7ffe86267488


    // 整数超过最大值
    {
        unsigned int nLen  = pow(2, 32)-1 ;    // #include <cmath>
        unsigned int nLen2 = UINT_MAX;         // 另一种形式
        printf("intmax:%u  %u\n", nLen, nLen2);   // 4294967295
        printf("intmax +1:%u  %u\n", nLen+1, nLen2+1);  // 0

        unsigned long long llu  = (unsigned long long)pow(2, 64) -1 ;
        unsigned long long llu2 = ULONG_LONG_MAX ;
        printf("long long max:%llu  %llu\n", llu, llu2);  // 18446744073709551615
        printf("long long max +1:%llu  %llu\n", llu+2, llu2+1);  // 0
    }
// intmax:4294967295  4294967295
// intmax +1:0  0
// long long max:18446744073709551614  18446744073709551615
// long long max +1:0
}





class MyInt_t{
public:
    explicit MyInt_t(int val) :m_t(val) {}
    ~MyInt_t() {std::cout << m_t << '\n';}
private:
    int m_t;
};
void funcCopy(MyInt_t t) {}
void funcPtr(MyInt_t* t) {}
void funcRef(MyInt_t& t) {}
void funcUniqPtr(std::unique_ptr<MyInt_t>t) {}
void funcSharedPtr(std::shared_ptr<MyInt_t>t){}
void test1_cpp_1_paramowner()
{
    // f(value)      f 是资源所有者 即有一份 value 的拷贝。f 会自动释放该资源。                           F.16
    // f(pointer*)   f 借用了资源 故无权删除该资源。f 在每次使用前都必须检查该指针是否为空指针。            I.11 和 F.7
    // f(reference&) f 借用了资源 与指针不同，引用的值总是合法的。                                        I.11 和 F.7
    // f(unique_ptr) f 是资源的独占所有者 调用方显式地把资源的所有权传给了被调用方。f 会自动释放该资源。     F.26
    // f(shared_ptr) f 是资源的共享所有者 延长资源的生存期 。若是资源的最后一个所有者，结束会导致资源的释放。 F.27
    // 传统 C++，只能使用原始指针来表达指针、引用、std::unique_ptr 或 std::shared_ptr 这四种传参方式的所有权语义。
    // 下面的代码说明了我的观点：
    //   void f(double* ptr){...}
    //   double* ptr = new double[5];
    //   f(ptr);
    // 1 传统 C++ 的关键问题是，谁是所有者？是使用该数组的 f 中的被调用方，还是创建该数组的的调用方？并不明确
    // 2 所以在应用层面使用 std::move 的意图并不在于移动，而是所有权的转移。
    //   举例来说，若对 std::unique_ptr 应用 std::move，会将内存的所有权转移到另一个 std::unique_ptr。
    //   auto uniquePtr1 = std::make_unique<int>(2011);              uniquePtr1 是原来的所有者
    //   std::unique_ptr<int> uniquePtr2{ std::move(uniquePtr1) };   uniquePtr2 将成为新的所有者
    std::cout << "--- test1_cpp_1_paramowner Begin" << '\n';

    MyInt_t myInt{ 1998 };
    MyInt_t* myIntPtr = &myInt;
    MyInt_t& myIntRef = myInt;
    auto uniqPtr = std::make_unique<MyInt_t>(2011);
    auto sharedPtr = std::make_shared<MyInt_t>(2014);

    funcCopy(myInt);
    funcPtr(myIntPtr);
    funcRef(myIntRef);
    funcUniqPtr(std::move(uniqPtr));
    funcSharedPtr(sharedPtr);

    std::cout << "--- test1_cpp_1_paramowner End" << '\n';
// --- test1_cpp_1_paramowner Begin
// 1998
// 2011
// --- test1_cpp_1_paramowner End
// 2014
// 1998

// 运行结果显示，有两个析构函数在 main 函数结束之前被调用，还有两个析构函数在 main 函数结束的地方被调用。
// main 函数结束之前析构的是 funcCopy(被拷贝到函数中)，funcUniqPtr(被移动到函数中)。
// funcCopy拷贝拷贝了一份新的 MyInt 到函数中，结束时析构，打印 1998。
// funcUniqPtr移动转移了智能指针资源的所有权，结束时，RAII 释放了内存，打印 2011。
// funcSharedPtr资源没转移，两对象共享(main中和函数中)，结束时引用计数减一不释放。main 结束时析构，打印 2014 。
// myInt 析构，打印 1998。注意到，打印了两次 1998，因为第一次析构的是复制到函数中的。
}


class g_cls{
public:
    static int m_s_i;
};
int g_cls::m_s_i = 1;
int g_i_a = 1;
static int gs_i_a = 11;
void test1_cpp_1_static()
{
    static int ls_i_a;
    int l_i_a;
    static int ls_i_10[10];
    int l_i_10[10];

    char aa[111];
    int bb[111];
    printf("aa=%ld bb=%ld\n", sizeof(aa), sizeof(bb) ); // 111 444

    printf("ls_i_a=%d l_i_a=%d\n", ls_i_a, l_i_a );  // 0  随机数
    printf("g_i:%p gs_i:%p ls_i:%p l_i:%p g_cls:%p\n", &g_i_a, &gs_i_a, &ls_i_a, &l_i_a, &(g_cls::m_s_i));
    printf("ls_i_10:%p l_i_10:%p\n", ls_i_10, l_i_10);
// g_i:0x55a36dbd702c gs_i:0x55a36dbd7030 ls_i:0x55a36dbd7034 l_i:0x7ffd85b26b2c g_cls:0x55a36dbd7028
// ls_i_10:0x55a36dbd78a0 l_i_10:0x7ffd85b26b30
}

void test1_cpp_1_memory()
{

}

