// #include <stdio.h>
// #include <stdlib.h>

// #include <iostream>
// #include <cstddef>
// #include <bits/c++config.h>
// #include <ostream>
// #include <istream>

// #include <ios>
// #include <bits/ostream_insert.h>

// #include <iosfwd>
// #include <exception> 		// For ios_base::failure
// #include <bits/char_traits.h> 	// For char_traits, streamoff, streamsize, fpos
// #include <bits/localefwd.h>	// For class locale
// #include <bits/ios_base.h>	// For ios_base declarations.
// #include <streambuf>
// #include <bits/basic_ios.h>

// #include <bits/localefwd.h>
// #include <bits/locale_classes.h>
// #include <bits/locale_facets.h>
// #include <bits/streambuf_iterator.h>
// #include <bits/move.h>

// #include <streambuf>
// #include <debug/debug.h>

// #include <bits/c++config.h>
// #include <iosfwd>
// #include <bits/localefwd.h>
// #include <bits/ios_base.h>
// #include <bits/cpp_type_traits.h>
// #include <ext/type_traits.h>

// #include <ext/atomicity.h>
// #include <bits/localefwd.h>
// #include <bits/locale_classes.h>

// #include <bits/localefwd.h>
// #include <string>
// #include <ext/atomicity.h>

// #include <bits/c++config.h>
// #include <bits/stringfwd.h>
// #include <bits/char_traits.h>  // NB: In turn includes stl_algobase.h
// #include <bits/allocator.h>
// #include <bits/cpp_type_traits.h>
// #include <bits/localefwd.h>    // For operators >>, <<, and getline.
// #include <bits/ostream_insert.h>
// #include <bits/stl_iterator_base_types.h>
// #include <bits/stl_iterator_base_funcs.h>
// #include <bits/stl_iterator.h>
// #include <bits/stl_function.h> // For less
// #include <ext/numeric_traits.h>
// #include <bits/stl_algobase.h>
// #include <bits/range_access.h>
// #include <bits/basic_string.h>
// #include <bits/basic_string.tcc>


// #include <ext/atomicity.h>
// #include <ext/alloc_traits.h>
// #include <debug/debug.h>

#include <malloc.h>
// #include <sys/malloc.h>
// #include <mm_malloc.h>
// #include <stdlib.h>

#include <chrono>
#include <string.h>

#include <vector>
#include <memory_resource>

#include "tracknew.hpp"

using namespace std;
using namespace std::chrono;
struct st
{
    int i;
    float f;
};

class timeuse
{
public:
    chrono::time_point<steady_clock, chrono::nanoseconds> m_start;
    chrono::time_point<steady_clock, chrono::nanoseconds> m_end;

    timeuse(){m_start = steady_clock::now(); m_end = steady_clock::now();}
    void reset(){m_start = steady_clock::now();}
    void status(){
        m_end = steady_clock::now();
        //auto int_ms = duration_cast<chrono::milliseconds>(m_end - m_start);
        auto int_ms = duration_cast<chrono::microseconds>(m_end - m_start);
        printf("used time %fs\n", int_ms.count()/1000000.0);
    }

};

int params(int argc, char**argv);
void test1();
void test123();
void test2();
void test3();
int isys = 0;
int ipmr = 0;

std::string addrrange(const void* addr, const void* start, size_t len)
{
    if(addr >= start && addr < (start + len))
        return "in";
    return "out";
}


int main(int argc, char**argv) {

    if(params(argc,argv) < 0)
        return 1;

    // int size = 12801;

    // unsigned int count = 10000;
    // for (int i = 0; i < count; i++)
    // {
    //     char *ptr = (char*) malloc(size);
    //     free(ptr);
    // }

    // st* pst = new st;
    // pst->i = 0;
    // pst->f = 1.1f;

    // delete pst;
    // printf("--------- size %d count %u\n", size, count);



    printf("--- pmr start ---\n");

    test123();

    printf("--- pmr end ---\n");
    return 0;
}

void test1()
{
    int count = 10;
    int count2 = 50000;

    if(isys == 1)
    {
        printf("使用默认分配器\n");
        TrackNew::reset();
        timeuse tu;
        tu.reset();

        std::vector<std::string> coll;
        for (int i = 0; i < count; i++)
        {
            for (int i = 0; i < count2; ++i) {
                coll.emplace_back("just a non-SSO string");
            }
            coll.clear();
        }

        // for (int i = 0; i < 1; i++)
        // {
        //     void * pp = malloc(100);
        //     free(pp);
        // }

        tu.status();
        TrackNew::status();
    }

    if(ipmr == 1)
    {
        printf("使用内存分配器\n");
        TrackNew::reset();
        timeuse tu;
        tu.reset();

        // 在栈上分配一些内存：
        std::array<std::byte, 8000000> buf;

        // const static long numm = 2000000;
        // char cc[numm];

        // 将它用作vector的初始内存池：
        std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};

        // std::pmr::unsynchronized_pool_resource pool;
        // std::pmr::monotonic_buffer_resource pool{cc, numm};
        std::pmr::vector<std::string> coll{&pool};
        // std::pmr::vector<std::pmr::string> coll{&pool};

        for (int i = 0; i < count; i++)
        {
            for (int i = 0; i < count2; ++i) {
                coll.emplace_back("just a non-SSO string");
            }
            static const char* pp = 0;
            printf("count %d coll[0] %p step %ld start %p  end %p %s\n",
            i, coll[0].c_str(), coll[0].c_str() - pp, buf.data(), buf.data() + buf.size(),
            (coll[0].c_str()>=(char*)(buf.data()) && coll[0].c_str()<=(char*)(buf.data() + buf.size()) ? "in":"out"));
            pp = coll[0].c_str();
            coll.clear();
        }

        tu.status();
        TrackNew::status();
    }

    // {
    //     printf("比较\n");
    //     TrackNew::reset();
    //     timeuse tu;
    //     tu.reset();

    //     {
    //     pmr::monotonic_buffer_resource res(100000);
    //     // pmr::vector<vector<int>> vec1(&res);
    //     // pmr::vector<pmr::vector<int>> vec2(&res);
    //     pmr::vector<int> vec1(&res);
    //      for (size_t i = 0; i < count; i++)
    //     {
    //         for (int i = 0; i < count2; ++i)
    //         {
    //             vec1.push_back(123);
    //         }
    //         vec1.clear();
    //     }
    //     }

    //     tu.status();
    //     TrackNew::status();


    //     TrackNew::reset();
    //     tu.reset();
    //     {
    //     vector<int> vec1;
    //      for (size_t i = 0; i < count; i++)
    //     {
    //         for (int i = 0; i < count2; ++i)
    //         {
    //             vec1.push_back(123);
    //         }
    //         vec1.clear();
    //     }
    //     }
    //     tu.status();
    //     TrackNew::status();
    // }
}

int params(int argc, char**argv)
{
    if (argc == 1)
    {
        return -1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            // printf("调用格式:\n");
            // printf("xxx [选项1 [参数1] ] [选项2 [参数2] ] ...\n");
            // printf("选项 参数说明:\n");
            // printf("[thread num] 启动线程数 num表示线程数量\n");
            // printf("[malloc] 启动malloc方式测试\n");
            // printf("[mallocsize num] 调整malloc申请内存大小\n");
            // printf("[vector] 启动vector方式测试\n");
            // printf("[list] 启动list方式测试\n");
            // printf("[map] 启动map方式测试\n");
            // printf("[newsize num] 调整new申请内存大小\n");
            // printf("[count num] 主循环次数 num表示数量\n");
            // printf("[count2 num] 次循环次数 num表示数量\n");
            return -1;
        }
        // else if (strcmp(argv[i], "thread") == 0)
        // {
        //     if ( i+1 > argc)
        //     {
        //         printf("no thread num params\n");
        //         return -1;
        //     }
        //     else
        //     {
        //         ithread = atoi(argv[i+1]);
        //     }

        //     i++;
        // }
        // else if (strcmp(argv[i], "count") == 0)
        // {
        //     if ( i+1 > argc)
        //     {
        //         printf("no count params\n");
        //         return -1;
        //     }
        //     else
        //     {
        //         icount = atoi(argv[i+1]);
        //     }

        //     i++;
        // }
        // else if (strcmp(argv[i], "count2") == 0)
        // {
        //     if ( i+1 > argc)
        //     {
        //         printf("no count2 params\n");
        //         return -1;
        //     }
        //     else
        //     {
        //         icount2 = atoi(argv[i+1]);
        //     }

        //     i++;
        // }
        // else if (strcmp(argv[i], "mallocsize") == 0)
        // {
        //     if ( i+1 > argc)
        //     {
        //         printf("no mallocsize params\n");
        //         return -1;
        //     }
        //     else
        //     {
        //         mallocsize = atoi(argv[i+1]);
        //     }

        //     i++;
        // }
        // else if (strcmp(argv[i], "newsize") == 0)
        // {
        //     if ( i+1 > argc)
        //     {
        //         printf("no newsize params\n");
        //         return -1;
        //     }
        //     else
        //     {
        //         newsize = atoi(argv[i+1]);
        //     }

        //     i++;
        // }
        // else if (strcmp(argv[i], "simple") == 0)
        // {
        //     isimple = 1;
        // }
        // else if (strcmp(argv[i], "malloc") == 0)
        // {
        //     mallocopen = 1;
        // }
        // else if (strcmp(argv[i], "vector") == 0)
        // {
        //     stlvector = 1;
        // }
        // else if (strcmp(argv[i], "list") == 0)
        // {
        //     stllist = 1;
        // }
        // else if (strcmp(argv[i], "map") == 0)
        // {
        //     stlmap = 1;
        // }
        else if (strcmp(argv[i], "sys") == 0)
        {
            isys = 1;
        }
        else if (strcmp(argv[i], "pmr") == 0)
        {
            ipmr = 1;
        }
        else
        {
            printf("incrrect params %s\n", argv[i]);
        }
    }

    return 0;
}


void test2()
{
    string *pstr = new string("123");

    void *pv = malloc(12);
}
void test3()
{
    string *pstr = new string("123");
}
void test123()
{
    {
    int i =1;
    string str1("123");
    string str2("12345678901234");
    string str3("123456789012345");
    string str4("1234567890123456"); // string > 15 堆上分配内存

    vector<int> vcti;                // vector 堆上分配内存
    vector<string> vctstr;                // vector
    vcti.emplace_back(1);
    printf("i:%p str1_d:%p str2_d:%p str3_d:%p str4_d:%p\n", &i, str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());
    printf("i:%p  &str1:%p  &str2:%p  &str3:%p  &str4:%p\n", &i, &str1, &str2, &str3, &str4);
    printf("vcti:%p data:%p\n", &vcti, vcti.data());

    vctstr.emplace_back(str1);
    vctstr.emplace_back(str4);

    printf("vctstr[0]_d:%p vctstr[1]_d:%p\n", vctstr[0].c_str(), vctstr[1].c_str());
    printf(" &vctstr[0]:%p  &vctstr[1]:%p\n", &vctstr[0], &vctstr[1]);
    }


    {
    char arr[1000];
    std::pmr::monotonic_buffer_resource pool(arr, sizeof(arr));
    std::pmr::vector<std::string> vct1(&pool);
    std::string str1{"my string"};
    std::string str2{"my string with some value"};
    vct1.emplace_back(str1);
    vct1.emplace_back(str2);

    printf("arr:%p arr_end:%p\n", arr, arr + sizeof(arr));
    printf("1  &vct1:%p vct1[0]_d:%p [%s] vct1[1]_d:%p [%s]\n",
      &vct1, vct1[0].c_str(), addrrange(vct1[0].c_str(), arr, sizeof(arr)).c_str(),
             vct1[1].c_str(), addrrange(vct1[1].c_str(), arr, sizeof(arr)).c_str());
    printf("1  &vct1:%p  &vct1[0]:%p [%s]  &vct1[1]:%p [%s]\n",
      &vct1, &vct1[0], addrrange(&vct1[0], arr, sizeof(arr)).c_str(),
             &vct1[1], addrrange(&vct1[1], arr, sizeof(arr)).c_str());
    }

    {
    char arr[5000];
    std::pmr::monotonic_buffer_resource pool(arr, sizeof(arr));
    std::pmr::vector<std::pmr::string> vct1(&pool);
    std::pmr::string str1{"my string"};
    std::pmr::string str2{"my string with some value"};
    vct1.emplace_back(str1);
    vct1.emplace_back(str2);

    printf("arr:%p arr_end:%p\n", arr, arr + sizeof(arr));
    printf("2  &vct1:%p vct1[0]_d:%p [%s] vct1[1]_d:%p [%s]\n",
      &vct1, vct1[0].c_str(), addrrange(vct1[0].c_str(), arr, sizeof(arr)).c_str(),
             vct1[1].c_str(), addrrange(vct1[1].c_str(), arr, sizeof(arr)).c_str());
    printf("2  &vct1:%p  &vct1[0]:%p [%s]  &vct1[1]:%p [%s]\n",
      &vct1, &vct1[0], addrrange(&vct1[0], arr, sizeof(arr)).c_str(),
             &vct1[1], addrrange(&vct1[1], arr, sizeof(arr)).c_str());
    }



    {
    std::string s{"my string with some value"};
    std::pmr::string ps{std::move(s), std::pmr::new_delete_resource()}; // 拷贝
    printf("str s:%p str ps:%p\n", s.c_str(), ps.c_str());
    }

}