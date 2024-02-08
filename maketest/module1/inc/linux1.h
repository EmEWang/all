#ifndef __MODULE1_LINUX1_H__
#define __MODULE1_LINUX1_H__

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

// 主要用于测试linux调用



// 用户态使用 glibc/backtrace 追踪函数调用堆栈定位段错误
// https://kernel.blog.csdn.net/article/details/84189280
// #include <execinfo.h>

//  Store up to SIZE return address of the current program state in
//    ARRAY and return the exact number of values stored.
// int backtrace(void **array, int size);

//  Return names of functions from the backtrace list in ARRAY in a newly
//    malloc()ed memory block.
// char **backtrace_symbols(void *const *array, int size);

//  This function is similar to backtrace_symbols() but it writes the
//    result immediately to a file.
// void backtrace_symbols_fd(void *const *array, int size, int fd);

// 使用它们的时候有一下几点需要我们注意的地方：
// backtrace的实现依赖于栈指针(fp寄存器), 在gcc编译过程中任何非零的优化等级（-On参数）
//   或加入了栈指针优化参数 -fomit-frame-pointer 后多将不能正确得到程序栈信息;
// backtrace_symbols的实现需要符号名称的支持, 在gcc编译过程中需要加入 -rdynamic 参数
// 内联函数没有栈帧, 它在编译过程中被展开在调用的位置；
// 尾调用优化(Tail-call Optimization)将复用当前函数栈, 而不再生成新的函数栈, 这将导致栈信息不能正确被获取。

// int backtrace(void **buffer,int size)
// 该函数用于获取当前线程的调用堆栈,

// 参数:
// 获取的信息将会被存放在 buffer 中,它是一个指针列表.
// 参数 size 用来指定 buffer 中可以保存多少个 void* 元素.

// 函数返回值:
// 实际获取的指针个数, 最大不超过 size大小.

// 在 buffer 中的指针实际是从堆栈中获取的返回地址, 每一个堆栈框架有一个返回地址

// 注意:某些编译器的优化选项对获取正确的调用堆栈有干扰,另外内联函数没有堆栈框架;删除框架指针也会导致无法正确解析堆栈内容


// char ** backtrace_symbols (void *const *buffer, int size)
// backtrace_symbols 将从 backtrace 函数获取的信息转化为一个字符串数组.

// 参数:
// buffer 应该是从 backtrace 函数获取的指针数组
// size 是该数组中的元素个数(backtrace 的返回值)

// 函数返回值:
// 一个指向字符串数组的指针, 它的大小同 buffer 相同.
// 每个字符串包含了一个相对于buffer中对应元素的可打印信息.
// 它包括函数名，函数的偏移地址,和实际的返回地址

// 现在, 只有使用ELF二进制格式的程序才能获取函数名称和偏移地址. 在其他系统,只有16进制的返回地址能被获取.
// 另外,你可能需要传递相应的符号给链接器,以能支持函数名功能
// (比如,在使用GNU ld链接器的系统中,你需要传递(-rdynamic)， -rdynamic可用来通知链接器将所有符号添加到动态符号表中，
//   如果你的链接器支持-rdynamic的话，建议将其加上！)
// 该函数的返回值是通过malloc函数申请的空间,因此调用者必须使用free函数来释放指针.
// 注意 : 如果不能为字符串获取足够的空间函数的返回值将会为NULL


// void backtrace_symbols_fd (void *const *buffer, int size, int fd)
// backtrace_symbols_fd 与 backtrace_symbols 函数具有相同的功能, 不同的是它不会给调用者返回字符串数组,
//   而是将结果写入文件描述符为fd 的文件中, 每个函数对应一行.它不需要调用malloc函数,
//   因此适用于有可能调用该函数会失败的情况



/* Obtain a backtrace and print it to @code{stdout}. */
inline void print_trace (void)
{
	void    * array[10];
	size_t  size;
	char    ** strings;
	size_t  i;

	size = backtrace(array, 10);
	strings = backtrace_symbols (array, size);
	if (NULL == strings)
	{
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	printf ("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		printf ("%s\n", strings[i]);

	free (strings);
	strings = NULL;
}

/* A dummy function to make the backtrace more interesting. */
inline void dummy_function (void)
{
	print_trace();
}



// addr2line -C -f -e ./maketest 0x557d3bd6f9b2    对应错误的行号
// objdump -DS ./handler | grep -6  "400b90"
    // 使用 objdump 将函数的指令信息 dump 出来.
    // 其中 -D 参数表示显示所有汇编代码, -S 表示将对应的源码也显示出来
    // 最后用 grep 显示地址 0x400b90 处前后 6 行的信息
#include <signal.h>

/* Obtain a backtrace and print it to stdout. */
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
inline void dump_stack(void)
{
	void *array[30] = { 0 };
	size_t size = backtrace(array, ARRAY_SIZE(array));
	char **strings = backtrace_symbols(array, size);
	size_t i;

	if (strings == NULL)
	{
		perror("backtrace_symbols.");
		exit(EXIT_FAILURE);
	}

	printf("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		printf("%s\n", strings[i]);

	free(strings);
	strings = NULL;

	exit(EXIT_SUCCESS);
}

inline void sighandler_dump_stack(int sig)
{
	psignal(sig, "handler");
	dump_stack();
	signal(sig, SIG_DFL);
	raise(sig);
}

inline void func_c()
{
	*((volatile int *)0x0) = 0x9999; /* ERROR */
}

inline void func_b()
{
	func_c();
}

inline void func_a()
{
	func_b();
}




#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <dlfcn.h>
#include <execinfo.h>
#include "/usr/include/dlfcn.h"

// 需要 SO_LIBS=-ldl -pthread -lrt   其中 -ldl 必须 后2个 可选
inline void showBacktrace()
{
        void * ret = __builtin_return_address(1);
        printf("ret address [%p]\n", ret);
        void * caller = __builtin_frame_address(0);
        printf("call address [%p]\n", caller);
#ifdef __cplusplus
        Dl_info dlinfo;

        void *ip = ret;
        if(!dladdr(ip, &dlinfo)) {
                perror("addr not found\n");
                return;
        }

        const char *symname = dlinfo.dli_sname;
        int f = 0;
        fprintf(stderr, "% 2d: %p %s+%u (%s)\n",
                        ++f,
                        ip,
                        symname, 0,
// (unsigned)(ip - dlinfo.dli_saddr),

                        dlinfo.dli_fname);
#endif
}

inline int MyFunc_A()
{
        showBacktrace();
        return 10;
}

inline int MyFunc_B()
{
        return MyFunc_A();
}










// test
inline void test1_linux1_backtrace()
{
    // 1
    dummy_function();

    MyFunc_B();

    // 2
    if (signal(SIGSEGV, sighandler_dump_stack) == SIG_ERR)
		perror("can't catch SIGSEGV");
	func_a();
}


#endif
