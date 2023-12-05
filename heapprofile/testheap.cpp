#include <iostream>
// #include "google/heap-profiler.h"
#include <unistd.h>

void test1()
{
    int i = 100;
    while(i--) {
        char *buf = new char[1024*1024];
    }
}

void test2()
{
    int i = 100;
    while(i--) {
        char *buf = new char[1024];
        delete buf;
    }
}

void test3()
{
    int i = 100;
    while(i--) {
        char *buf = new char[1024];
        // delete buf;
    }
}

void test4()
{
    int i = 100;
    while(i--) {
        char *buf = new char[1024];
        // delete buf;
    }
}


int main()
{
    // HeapProfilerStart("./test.log");

    int index = 0;
    while (1)
    {
        int i = 100;
        while(i--) {
            char *buf = new char[1024];
            // delete buf;
        }
        test2();
        test3();
        test4();

        sleep(1);
        printf("%d\n", ++index);
        if (index > 4)
        {
            // break;
        }

    }

    // int i = 100;
    // while(i--) {
    //     char *buf = new char[1024*1024];
    // }
    // test1();
    // test2();
    // HeapProfilerStop();
    // return 0;
}