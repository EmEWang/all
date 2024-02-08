
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <array>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <thread>

#ifdef TC12
#include "/home/lixiang/code/gperftools/src/windows/gperftools/tcmalloc.h"
#elif MI12
// #include "/home/lixiang/code/mimalloc/include/mimalloc.h"
#else
#endif

void testthread1();
void testthread2();
void testmalloc();
void testmalloc2();
void teststl();
void teststl2();
void teststl3();

//262144
struct myst_simple{
    int i;
    float f;
    char charr[1222];
    std::string str;
    std::pair<int, const char*> pr;
};
struct myst{
    int i;
    float f;
    char charr[122];
    std::string str;
    std::pair<int, const char*> pr;

    char *pch;
    myst():i(1),f(1.1),str("abc"),pch(NULL){
        pr = std::make_pair(12, "sdf");
    }
    myst(const myst& other):i(other.i),f(other.f),str(other.str),pr(other.pr){
        // pch = other.pch;
        // other.pch = NULL;
    }
    myst(myst&& other):i(other.i),f(other.f),str(other.str),pr(other.pr){
        pch = other.pch;
        other.pch = NULL;
    }

    myst& operator=(myst&& other){
        i=other.i;
        f=other.f;
        pch = other.pch;
        other.pch = NULL;
        str=other.str;
        pr=other.pr;
        return *this;
    }
    myst& operator=(myst& other){
        i=other.i;
        f=other.f;
        // pch = other.pch;
        // other.pch = NULL;
        str=other.str;
        pr=other.pr;
        return *this;
    }
    ~myst(){
        if(pch!=NULL){
            // printf("eeeeeeeeeeeeeeeeee\n");
            delete[] pch;
            pch=NULL;
            // printf("ffffffffffffffff\n");
        }
    }
};

int params(int argc, char**argv);
int isimple = 0;
unsigned int ithread = 5;
unsigned int mallocopen = 0;
unsigned int mallocsize = 0;
unsigned int icount = 0;
unsigned int icount2 = 0;
unsigned int stlvector = 0;
unsigned int stllist = 0;
unsigned int stlmap = 0;
unsigned int newsize = 0;

int main(int argc, char**argv) {
    // std::cout << "alignof std::max_align_t:" << alignof(std::max_align_t) << '\n';
    // double *ptr = (double*) malloc(sizeof(double) * 3 );
    // std::cout << "alignof double:" << alignof(*ptr) << '\n';
    // char *ptr2 = (char*) malloc(1);
    // std::cout << "alignof char*: " << alignof(*ptr2) << '\n';
    // void *ptr3;
    // std::cout << "sizeof void*:" << sizeof(ptr3) << " alignof void*:" << alignof(ptr3) << '\n';
    // return 0;

    #ifdef TC12
    std::cout << "TCMALLOC\n";
    #elif MI12
    std::cout << "MIMALLOC\n";
    #else
    std::cout << "deault\n";
    #endif

    if(params(argc, argv) != 0) return 0;
    std::thread *threadx = new std::thread[ithread];
    for (size_t i = 0; i < ithread; i++) threadx[i] = std::thread(testthread1);
    for (size_t i = 0; i < ithread; i++) threadx[i].join();
    // std::thread thread1(testthread1);
    // testmalloc();
    // thread1.join();
    std::cout << "finish\n";
    // getchar();
    return 0;
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
            printf("调用格式:\n");
            printf("xxx [选项1 [参数1] ] [选项2 [参数2] ] ...\n");
            printf("选项 参数说明:\n");
            printf("[thread num] 启动线程数 num表示线程数量\n");
            printf("[malloc] 启动malloc方式测试\n");
            printf("[mallocsize num] 调整malloc申请内存大小\n");
            printf("[vector] 启动vector方式测试\n");
            printf("[list] 启动list方式测试\n");
            printf("[map] 启动map方式测试\n");
            printf("[newsize num] 调整new申请内存大小\n");
            printf("[count num] 主循环次数 num表示数量\n");
            printf("[count2 num] 次循环次数 num表示数量\n");
            return -1;
        }
        else if (strcmp(argv[i], "thread") == 0)
        {
            if ( i+1 > argc)
            {
                printf("no thread num params\n");
                return -1;
            }
            else
            {
                ithread = atoi(argv[i+1]);
            }

            i++;
        }
        else if (strcmp(argv[i], "count") == 0)
        {
            if ( i+1 > argc)
            {
                printf("no count params\n");
                return -1;
            }
            else
            {
                icount = atoi(argv[i+1]);
            }

            i++;
        }
        else if (strcmp(argv[i], "count2") == 0)
        {
            if ( i+1 > argc)
            {
                printf("no count2 params\n");
                return -1;
            }
            else
            {
                icount2 = atoi(argv[i+1]);
            }

            i++;
        }
        else if (strcmp(argv[i], "mallocsize") == 0)
        {
            if ( i+1 > argc)
            {
                printf("no mallocsize params\n");
                return -1;
            }
            else
            {
                mallocsize = atoi(argv[i+1]);
            }

            i++;
        }
        else if (strcmp(argv[i], "newsize") == 0)
        {
            if ( i+1 > argc)
            {
                printf("no newsize params\n");
                return -1;
            }
            else
            {
                newsize = atoi(argv[i+1]);
            }

            i++;
        }
        else if (strcmp(argv[i], "simple") == 0)
        {
            isimple = 1;
        }
        else if (strcmp(argv[i], "malloc") == 0)
        {
            mallocopen = 1;
        }
        else if (strcmp(argv[i], "vector") == 0)
        {
            stlvector = 1;
        }
        else if (strcmp(argv[i], "list") == 0)
        {
            stllist = 1;
        }
        else if (strcmp(argv[i], "map") == 0)
        {
            stlmap = 1;
        }
        else
        {
            printf("incrrect params %s\n", argv[i]);
        }
    }

    return 0;
}
void print(const std::string& str, int count = 0, int count2 = 0) {
    std::cout << "tid:" << std::this_thread::get_id() <<" " << str << " " << sizeof(myst_simple) << " newsize " << newsize
         << " count "<< count << " * count2 "<< count2 <<  '\n';
}

void testmalloc() {
    // 4-5 3-4   2-3   2-3   0.8          25+
    // 1-7 9-15 16-31 33-48 49-127-262144-以上
    int size = 262145;
    unsigned long count = 10000;
    unsigned long count2 = 1000;

    (mallocsize > 0)?(size = mallocsize):(size);
    (icount > 0)?(count = icount):(count);
    (icount2 > 0)?(count2 = icount2):(count2);

    for (size_t i = 0; i < count; i++)
    {
        for (size_t i = 0; i < count2; i++)
        {
            // #ifdef TC12
            // std::cout << "TC12\n";
            // char *ptr = (char*) tc_malloc(size);
            // tc_free(ptr);
            // #elif MI12
            // std::cout << "MI12\n";
            // char *ptr = (char*) mi_malloc(size);
            // mi_free(ptr);
            // #else
            // std::cout << "other\n";
            // char *ptr = (char*) malloc(size);
            // free(ptr);
            // #endif

            char *ptr = (char*) malloc(size);
            free(ptr);
        }
    }
    std::cout << "tid:" << std::this_thread::get_id() << " size " << size << " " << count << " * "<< count2 << '\n';
}
void testmalloc2() {
    // int size = 127;
    // unsigned long count = 100000000;
    // unsigned long count2 = 60;
    // for (size_t i = 0; i < count2; i++){
    //     for (size_t i = 0; i < count; i++){
    //         char *ptr = (char*) tc_malloc(size);
    //         tc_free(ptr);
    //     }
    // }
    // std::cout << "testmalloc2 " << " size " << size << " " << count << " * "<< count2 << '\n';
}

void testthread1() {
    if (mallocopen) testmalloc();
    if (stlvector) teststl();
    if (stllist) teststl2();
    if (stlmap) teststl3();
}
void testthread2() {
    // void*p = dlopen("/home/lixiang/code/gperftools/build/libtcmalloc.so",  RTLD_NOW);
    // if (p == NULL) {
    //     std::cout << "dlopen error" << std::endl;
    //     return;
    // }

    // void *handle = NULL;
    // handle = dlsym(handle, "malloc");
    // if (handle == NULL) {
    //     std::cout << "handle error" << std::endl;
    //     return;
    // }

    // void *handle2 = NULL;
    // handle2 = dlsym(handle2, "free");
    // if (handle2 == NULL) {
    //     std::cout << "handle2 error" << std::endl;
    //     return;
    // }

    testmalloc2();

    // dlclose(handle);
    // dlclose(handle2);
}

void teststl() {
    if (isimple) {
        std::vector<myst_simple> vct;
        unsigned long count = 100;
        unsigned long count2 = 100;
        (icount > 0)?(count = icount):(count);
        (icount2 > 0)?(count2 = icount2):(count2);

        for (size_t i = 0; i < count; i++) {
            for (size_t i = 0; i < count2; i++) {
                myst_simple st;
                // if (newsize > 0) {
                //     char *pcr = new char[newsize];
                //     st.pch = pcr;
                // }
                vct.push_back(st);
                // vct.emplace_back(st);
            }
            vct.clear();
        }
        print("vector_s", count, count2);
    }
    else {
        std::vector<myst> vct;
        unsigned long count = 100;
        unsigned long count2 = 100;
        (icount > 0)?(count = icount):(count);
        (icount2 > 0)?(count2 = icount2):(count2);

        for (size_t i = 0; i < count; i++) {
            for (size_t i = 0; i < count2; i++) {
                myst st;
                if (newsize > 0) {
                    char *pcr = new char[newsize];
                    st.pch = pcr;
                }
                // vct.push_back(st);
                vct.emplace_back(st);
            }
            vct.clear();
        }
        print("vector", count, count2);
    }
}
void teststl2() {
    if (isimple) {
        std::list<myst_simple> vct;
        unsigned long count = 10000;
        unsigned long count2 = 100;
        (icount > 0)?(count = icount):(count);
        (icount2 > 0)?(count2 = icount2):(count2);

        for (size_t i = 0; i < count; i++) {
            myst_simple st;
            for (size_t i = 0; i < count2; i++) {
                // if (newsize > 0) {
                //   char *pcr = new char[newsize];
                //   delete[] pcr;
                //   st.pch = pcr;
                // }
                vct.push_back(st);
                // vct.push_back(std::move(st));
            }
            vct.clear();
        }
        print("list_s", count, count2);
    }
    else {
        std::list<myst> vct;
        unsigned long count = 10000;
        unsigned long count2 = 100;
        (icount > 0)?(count = icount):(count);
        (icount2 > 0)?(count2 = icount2):(count2);

        for (size_t i = 0; i < count; i++) {
            myst st;
            for (size_t i = 0; i < count2; i++) {
                if (newsize > 0) {
                    char *pcr = new char[newsize];
                    // delete[] pcr;
                    st.pch = pcr;
                }
                // vct.push_back(st);
                vct.push_back(std::move(st));
            }
            vct.clear();
        }
        print("list", count, count2);
    }
}
void teststl3() {
    if(isimple) {
        std::map<int, myst_simple> vct;
        unsigned long count = 100;
        unsigned long count2 = 100;
        (icount > 0)?(count = icount):(count);
        (icount2 > 0)?(count2 = icount2):(count2);

        for (size_t i = 0; i < count; i++) {
            for (size_t i = 0; i < count2; i++) {
                myst_simple st;
                // if (newsize > 0) {
                //     char *pcr = new char[newsize];
                //     st.pch = pcr;
                // }
                vct[i]=st;
                // vct[i]=std::move(st);
            }
            vct.clear();
        }
        print("map_s", count, count2);
    }
    else {
        std::map<int, myst> vct;
        unsigned long count = 100;
        unsigned long count2 = 100;
        (icount > 0)?(count = icount):(count);
        (icount2 > 0)?(count2 = icount2):(count2);

        for (size_t i = 0; i < count; i++) {
            for (size_t i = 0; i < count2; i++) {
                myst st;
                if (newsize > 0) {
                    char *pcr = new char[newsize];
                    st.pch = pcr;
                }
                // vct[i]=st;
                vct[i]=std::move(st);
            }
            vct.clear();
        }
        print("map", count, count2);
    }
}
