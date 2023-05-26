#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

// #include "testlib1.h"

void printzzz(const char* str)
{
    printf("printzzz 111 [%s]\n", str);
}

// void* malloc(unsigned long size)
// {
//     printf(" 111 \n");
//     return NULL;
// }

// 改写系统随即方法
int rand()
{
	return 55;
}

// linux中woami是会调用底层的puts方法。
// -ldl 显示方式加载动态库，可能会调用dlopen、dlsym、dlclose、dlerror
// -D_GNU_SOURCE 以GNU规范标准编译，如果不加上这个参数会报RTLD_NEXT未定义的错误
int puts(const char *message) {
	int (*new_puts)(const char *message);
	int result;
	new_puts = dlsym(RTLD_NEXT, "puts");
	printf("my puts this is id:%d\n",getuid());     //获取他的uid并输出
	result = new_puts(message);
	return result;
}

// 若没有1 2当执行后，在我们测试的操作系统环境中(centos 7.5)，我们发现陷入了死循环。unbuntu20.04中测试没这个问题
int strcmp(const char *s1, const char *s2) {
	printf("my strcmp\n");
    // 由于我们通过 LD_PRELOAD 劫持了函数，劫持后启动了一个新进程，若不在新进程启动前取消 LD_PRELOAD，则将陷入无限循环，
	//   所以必须得删除环境变量 LD_PRELOAD，最直观的做法是调用 unsetenv("LD_PRELOAD")。
	// 执行命令编译生成 aaa.so：
	// gcc -shared -fPIC aaa.c -o aaa.so
	// 然后通过环境变量 LD_PRELOAD 来设置 libaaa.so 能被其他调用它的程序优先加载：
	// export LD_PRELOAD=$PWD/libaaa.so
	// # 也可以直接 LD_PRELOAD=$PWD/libaaa.so ./xxx
    if(getenv("LD_PRELOAD") == NULL)return 0;      // 1 getenv是获取环境变量 当他为空时我们已经不需要执行了
    unsetenv("LD_PRELOAD");                        // 2 unsetenv删除环境变量的函数 调用一次就可以直接删除了
    // system("ls");
    return 0;
}



// 系统执行main()函数之前调用
__attribute__((constructor)) void begin_() {
    printf("begin_ LD_PRELOAD=%s \n", getenv("LD_PRELOAD"));
}

// 系统在main()函数退出或者调用了exit()之后调用
__attribute__((destructor)) void after_() {
	printf("after_ LD_PRELOAD=%s \n", getenv("LD_PRELOAD"));
}
