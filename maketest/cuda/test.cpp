// # include <stdio.h>
// int main()
// {
//     printf("123\n");
//     return 0;
// }

/*
* 文件名 helloworld.cu
* 编译： nvcc -o helloworld helloworld.cu
*/
// #include <iostream>
#include <stdio.h>

#include <unistd.h>

#include "cuda.h"
#include "cuda_runtime.h"
// #include <linux/cuda.h>

// __global__  用于修饰在gpu上运行且由cpu调用的函数
// __device__  用于修饰在gpu上运行且由gpu调用的函数,本例不涉及
// __host__    用于修饰在cpu上运行的函数，一般缺省

// __global__ void k_add (int a, int b, int* c ){
//     *c = a+b;
// }

void testmalloc()
{
    for (size_t i = 0; i < 1000; i++)
    {
        char *pc = (char*)malloc(1024);
        free(pc);
    }
}
void testmalloc_leak()
{
    for (size_t i = 0; i < 1000; i++)
    {
        char *pc = (char*)malloc(1024);
        free(pc);
    }
}


void testcudaMalloc()
{
    int count = 1000/sizeof(int);
    int size = 1000;
    for (size_t i = 0; i < 1000; i++)
    {
        int h_c;
        int *d_c;
        cudaMalloc((void**)&d_c, sizeof(int)*size);
        // k_add<<<1,1>>>(2,7,d_c);
        cudaMemcpy(&h_c, d_c,sizeof(int),cudaMemcpyDeviceToHost);
        cudaFree(d_c);
        // printf("%d\n",h_c);
    }
}

void testcudaMalloc_leak()
{
    int count = 1000/sizeof(int);
    int size = 1000;
    for (size_t i = 0; i < 1000; i++)
    {
        int h_c;
        int *d_c;
        cudaMalloc((void**)&d_c, sizeof(int)*size);
        // k_add<<<1,1>>>(2,7,d_c);
        cudaMemcpy(&h_c, d_c,sizeof(int),cudaMemcpyDeviceToHost);
        // cudaFree(d_c);
        // printf("%d\n",h_c);
    }
}

int main(void)
{
    int h_c;       // h前缀表示host,指cpu的变量
    int *d_c;      // d前缀表示device,指gpu的变量

    for (size_t i = 0; i < 1000; i++)
    {
        testmalloc();
        testmalloc_leak();
        testcudaMalloc();
        testcudaMalloc_leak();

        sleep(3);
    }


    // cudaMalloc功能类似malloc
    // 第一个参数是指向地址的地址变量(&d_c)，第二个参数是分配显存的大小
    // 函数会修改&d_c指向的变量，完成对d_c的赋值
    // (void**)是为了让函数无需关心d_c的类型
    // cudaMalloc((void**)&d_c, sizeof(int));

    // gpu函数调用时有<<< >>>
    // 其中第一个变量表示使用几个线程块，第二个变量表示一个线程块使用几个线程
    // k_add<<<1,1>>>(2,7,d_c);

    // cudaMemcpy功能类似memcpy
    // 在cpu中不能解引用gpu变量，必须先将变量从显存复制到内存上才能访问
    // 最后一个参数指定复制的方向
    // cudaMemcpyHostToHost, cudaMemcpyHostToDevice, cudaMemcpyDeviceToHost及cudaMemcpyDeviceToDevice
    // cudaMemcpy(&h_c, d_c,sizeof(int),cudaMemcpyDeviceToHost);

    // cudaFree功能类似free
    // cudaFree(d_c);

    // printf("%d\n",h_c);
    return 0;
}


