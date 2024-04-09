#ifndef __MODULE1_C2_H__
#define __MODULE1_C2_H__


// 主要用于测试c


// 什么是字节对齐
//   计算机中内存大小的基本单位是字节（byte），理论上来讲，可以从任意地址访问某种基本数据类型，
//   但是实际上，计算机并非逐字节大小读写内存，而是以2,4,或8的 倍数的字节块来读写内存，
//   如此一来就会对基本数据类型的合法地址作出一些限制，即它的地址必须是2，4或8的倍数。
//   那么就要求各种数据类型按照一定的规则在空间上排列，这就是对齐。

// 总的来说，字节对齐有以下准则：
//   结构体变量的首地址能够被其对齐字节数大小所整除。
//   构体每个成员相对结构体首地址的偏移都是成员大小的 数倍，如不满足，对前一个成员填充字节以满足。
//   结构体的总大小为结构体对最大成员大小的整数倍，如不满足，最后填充字节以满足

// #pragma pack(n) 伪指令使得结构间以n字节对齐
// #pragma pack()/*还原默认对齐*/
// 对于单个结构体
// __attribute__((aligned (n)))，让结构成员对齐在n字节自然边界上。如果结构中有成员的长度大于n，则按照最大成员的长度来对齐。
// __attribute__ ((packed))，取消结构在编译过程中的优化对齐，也可以认为是1字节对齐。
// 测试 ubuntu 20.04 gcc9 默认 __attribute__((以aligned(1))) 对齐

#pragma pack(1)
struct stdataA{
    // int a;
    char b;
    short c;
};
#pragma pack()

struct stdataB{
    // int a;
    char b;
    short c;
}__attribute__ ((aligned(8)));

struct structC{
  int a;
  char b;
  long long c;
  char d;
};
// }__attribute__ ((aligned (1)));
// }__attribute__ ((packed));
struct structD{
  int a;
  char b;
  int c;
  char d;
};
// }__attribute__ ((aligned (1)));
// }__attribute__ ((packed));
struct structE{
  short int a;
  char b;
  short int c;
  char d;
};
// }__attribute__ ((aligned (1)));
// }__attribute__ ((packed));
struct structF{
  short int a;
  char b;
  int c;
  char d;
// };
}__attribute__ ((aligned(8)));
// }__attribute__ ((packed));
struct structG{
//   short int a;
  char b;
//   short int c;
//   char d;
};
// }__attribute__ ((aligned (1)));
// }__attribute__ ((packed));

// test
#include <stdio.h>
inline void test1_c2_bytealign()
{
    struct stdataA a, *pa=0;
    struct stdataB b, *pb=0;
    // 获取结构体成员偏移量
    // 方法1 结构体对象的成员之间相减   S s;        s.b-s.a
    // 方法2 把结构体地址指向地址 0x0，S s*=0;     (int)(&(s->a))
    // 方法3 内核代码 ./include/linux/stddef.h 的宏
    //   #ifndef __CHECKER__
    //   #undef offsetof
    //   #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
    //   #endif


    // 若去掉long  gcc则提示2个不同类型的指针相减
    // error: invalid operands of types ‘char*’ and ‘stdataA*’ to binary ‘operator-’
    printf("stdataA:%lu %p %ld %ld\n", sizeof(a), &a, (long)&a.b-(long)&a, (long)&a.c-(long)&a);
    // stdataA:3 0x7ffdbf47f17d 0 1


    // 若long改为int  gcc会提示 error: cast from ‘int*’ to ‘int’ loses precision [-fpermissive]
    // 因为Linux 64位系统上指针类型占用8个字节，而int类型占用4个字节，所以会出现loses precision。
    // 可以先将int* 转成long类型，long类型可以隐式类型转换到int类型
    printf("stdataB:%lu %p %ld %ld\n", sizeof(b), &b, (long)(&(pb->b)), (long)(&(pb->c)));
    // stdataB:8 0x7ffdbf47f180 0 2

#include <stddef.h>   // /usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h:406: 有定义下面的宏
//    #define offsetof(TYPE, MEMBER) ((size_t) &(((TYPE*)0)->MEMBER))
    printf("stdataB2:%lu %p %ld %ld\n", sizeof(b), &b, offsetof(stdataB, b), offsetof(stdataB, c));
    // stdataB2:8 0x7ffdbf47f180 0 2

    // 若改为void*  gcc提示 error: invalid use of ‘void’
    printf("stdataB3:%lu %p %ld\n", sizeof(b), &b, (char*)(&b.c)-(char*)(&b));
    // stdata:8 0x7ffdbf47f180 2


    printf("size of structC %lu\n", sizeof(structC)); // aligned(1)->24 packed->14 都不写->24
    printf("size of structD %lu\n", sizeof(structD)); // aligned(1)->16 packed->10 都不写->16
    printf("size of structE %lu\n", sizeof(structE)); // aligned(1)->8  packed->6  都不写->8
    printf("size of structF %lu\n", sizeof(structF)); // aligned(1)->12 packed->8  都不写->12
    printf("size of structG %lu\n", sizeof(structG)); // aligned(1)->1  packed->1  都不写->1  aligned(8)-> 8
}




// 单独指定结构体某个元素的值
struct st_index{
    int a;
    int b;
};
inline int st_index_ret_a(){return 11;}
inline int st_index_ret_b(){return 12;}
static const struct st_index st_index_1 = {
    .a      = st_index_ret_a(),
    .b      = st_index_ret_b()
};
static const struct st_index st_index_2 = {
    .a      = 1,
    .b      = 2
};
inline void test1_c2_struct()
{
    printf(" st_index_1 a %d b %d\n", st_index_1.a, st_index_1.b);
    printf(" st_index_2 a %d b %d\n", st_index_2.a, st_index_2.b);
}



#endif