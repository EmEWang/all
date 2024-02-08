
#include <stdio.h>

#include <iostream>

#include <unistd.h>

#include "cuda.h"
#include "cuda_runtime.h"
// #include "device_launch_parameters.h"
// #include "cuda_runtime_api.h"
// #include "cuda_runtime.h"


#define CHECK(call)                                                     \
do                                                                      \
{                                                                       \
    const cudaError_t error_code = call;                                \
    if (error_code != cudaSuccess)                                      \
    {                                                                   \
        printf("CUDA Error:\n");                                        \
        printf("    File:   %s\n", __FILE__);                           \
        printf("    Line:   %d\n", __LINE__);                           \
        printf("    Error code: %d\n", error_code);                     \
        printf("    Error text: %s\n", cudaGetErrorString(error_code)); \
        exit(1);                                                        \
    }                                                                   \
}                                                                       \
while(0);                                                               \


int main(void)
{
    int dev = 0;
    cudaDeviceProp devProp;
    CHECK(cudaGetDeviceProperties(&devProp, dev));
    // cudaGetDeviceProperties(&devProp, dev);
    std::cout << "使用GPU device " << dev << ": " << devProp.name << std::endl;
    std::cout << "SM的数量：" << devProp.multiProcessorCount << std::endl;
    std::cout << "每个线程块的共享内存大小：" << devProp.sharedMemPerBlock / 1024.0 << " KB" << std::endl;
    std::cout << "每个线程块的最大线程数：" << devProp.maxThreadsPerBlock << std::endl;
    std::cout << "每个EM的最大线程数：" << devProp.maxThreadsPerMultiProcessor << std::endl;
    std::cout << "每个SM的最大线程束数：" << devProp.maxThreadsPerMultiProcessor / 32 << std::endl;
    return 0;
}
