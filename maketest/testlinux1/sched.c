#include "sched.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "features.h"
// #define __USE_GNU  不能使用这个
// #define _GNU_SOURCE    # 用这个代替之 目前用编译-D指定

// 设置进程调度策略和优先级
// sched_setscheduler 设置实时进程 需要root权限
// sched_setscheduler 设置普通进程 不需要root权限
void testsched();

// 强制某个线程在指定的cpu运行
void testbindcpu();

int main()
{
    // testsched();
    testbindcpu();
    getchar();
    return 0;
}

void testsched()
{
    struct sched_param sp;
    sp.sched_priority = 22;   // 实时进程
    int ret = sched_setscheduler(0, SCHED_FIFO, &sp);
    if (ret == 0)
    {
        printf("sched_setscheduler 实时进程 success.\n");
    }
    else
    {
        printf("sched_setscheduler 实时进程 error %s.\n", strerror(errno));
        sp.sched_priority = 0;  // 普通进程必须为0
        ret = sched_setscheduler(0, SCHED_IDLE, &sp); // ! 用gcc编译不过 g++可以 ; gcc 需要使用 -D__GNU_SOURCE
        // ret = sched_setscheduler(0, SCHED_OTHER, &sp);
        if (ret == 0)
        {
            printf("sched_setscheduler 普通进程 success.\n");
        }
        else
        {
            printf("sched_setscheduler 普通进程 error %s.\n", strerror(errno));
        }
    }
}


// #define _GNU_SOURCE    # 同样需要这个
#include <time.h>
// #include <sched.h>     # 同样需要这个
#include <pthread.h>
void test_thread(void* cpu_id) {
    int cpuid = (int)(long)cpu_id;

    // 设置运行时指定cpu
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpuid, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0) {
        printf("Error: setaffinity() cpuid %d\n", cpuid);
        // 多加个(long)只是为了  warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
        pthread_exit((void*)(long)cpuid);
    }

    // 获取当前运行的cpu
    cpu_set_t mask2;
    CPU_ZERO(&mask2);
    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask2) < 0) {
        printf("Error: getaffinity() cpuid %d\n", cpuid);
        pthread_exit((void*)(long)cpuid);
    }
    // 检测当前运行的cpu
    if (CPU_ISSET(cpuid, &mask2))
        printf("thread(%ld) in cpuid %d is running\n", (long)pthread_self(), cpuid);
    else
        printf("thread(%ld) not in cpuid %d is running\n", (long)pthread_self(), cpuid);
    pthread_exit((void*)(long)(cpuid+100));
}
void testbindcpu()
{
    int res;
    void *thread_result;
    const int size = 10;
    long ret[size];
    pthread_t test_thread_ctrl[10];
    for (int i = 0; i < size; ++i)
        pthread_create(&(test_thread_ctrl[i]), NULL, (void*)test_thread, (void*)(long)i);
    for (int i = 0; i < size; ++i){
        res = pthread_join(test_thread_ctrl[i], &thread_result);
        ret[i] = (long)thread_result;
    }

    for (int i = 0; i < size; i++)
    {
        printf("thread ret %ld\n", ret[i]);
    }
}