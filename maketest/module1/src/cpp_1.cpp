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
    double d4 = DBL_MAX + DBL_MAX + DBL_MAX;

    int i1 = _finite(d1);
    int i2 = _finite(d2);
    int i3 = _finite(d3);
    int i4 = _finite(d4);

    printf("i1 %d d1 = %f\n", i1, d1);
    printf("i2 %d d2 = %f\n", i2, d2);
    printf("i3 %d d3 = %f\n", i3, d3);
    printf("i4 %d d4 = %f\n", i4, d4);
    printf("i4 %d d4 = %p\n", i4, &d4);
// i1 1 d1 = 1.100000
// i2 1 d2 = -1.100000
// i3 1 d3 = 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000
// i4 0 d4 = inf
// i4 0 d4 = 0x7ffe86267488


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



void test1_cpp_1_hash_simple()
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


struct st_key1_cpp_1{
    int i;
    int j;
    st_key1_cpp_1():i(0),j(0){}
    st_key1_cpp_1(int a, int b):i(a),j(b){}
};
struct hash1_cpp_1{
    size_t operator () (const st_key1_cpp_1 &t) const {return size_t(t.i);}
};
struct equal1_cpp_1{
    bool operator () (const st_key1_cpp_1 &t1, const st_key1_cpp_1 &t2) const {return t1.i == t2.i;}
};
void test1_cpp_1_hash_selfdef()
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
struct equal2cpp_1{
    bool operator () (const std::string &t1, const std::string &t2) const {return t1 == t2;}
};
void test1_cpp_1_hash_selfdef2()
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

