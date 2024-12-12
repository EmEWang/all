
https://zhuanlan.zhihu.com/p/655099766     # 深入讲解内存分配函数 malloc 原理及实现
https://zhuanlan.zhihu.com/p/657696118     # C语言 内存管理




Linux-C进程内存布局(虚拟内存VM)
————————————————————————————————————   0xFFFF FFFF  32B   0xFFFF FFFF FFFF FFFF  64B
内核(kernel)    以上区域
                    |————————————————————                 0xFFFF 8000 0000 0000  64B
                    |annoical addredss 空洞 64B 特有
————————————————————————————————————   0xC000 0000  32B   0x0000 7FFF FFFF F000  64B
栈(stack)
    ↓           | 环境变量
                | 命令行参数
                | 局部变量

文件映射与匿名映射区
    ↓

    ↑
堆(heap)
————————————————————————————————————
数据段
                | .bss(Block Started by Symbol)段  未初始化全局/静态变量
                | .data(data segment)段            已初始化全局/静态变量
                | .rodata(read only data)段  只读变量(const修饰的变量) 字符串变量 常量数据(printf 的格式化字符也算)
————————————————————————————————————   代码段 和 数据段 之间有一段隔离区 64B 特有
代码段
                | .text 用户代码
                | .init 系统初始化代码
————————————————————————————————————   0x0840 8000  32B   0x0000 0000 0040 0000  64B
不可访问
————————————————————————————————————   0x0000 0000  32B   0x0000 0000 0000 0000  64B

1 栈空间有限，尤其在嵌入式环境下。因此不可以用来存储尺寸太大的变量。默认8M。ulimit -s 查看/设置
  栈内存的分配和释放，都是由系统规定的，我们无法干预。
  栈维护了一个函数调用过程中所需要的信息，被称为栈帧。栈帧中一般维护了以下几类重要的数据：
  函数返回地址：记录了函数执行完成后，退出函数调用时需要执行的下一条指令
  函数参数：在调用子函数时，程序将函数参数依序保存在栈上
  局部变量：函数调用过程中使用的非静态局部变量均默认保存在栈上，函数退出后，这些变量也会被释放而不可使用
  保存的寄存器(环境变量等)：保存了函数调用前后需要保持不变的寄存器

2 变量
auto     自动变量，函数中的局部变量，数据在动态存储区，调用该函数时系统会给分配存储空间，函数结束时自动释放。
register 寄存器变量，C允许将局部变量的值放在CPU中的寄存器中，只有局部自动变量和形式参数可以作为寄存器变量。
extern   外部变量(即全局变量)，函数外部定义；作用域为从变量定义处开始，到本程序文件的末尾。
static   静态局部变量，在静态存储区分配，整个程序运行期间都不释放。全局静态变量在声明他的文件之外是不可见的。

变量           作用范围        生存周期       存储区         自动初始化      其他
局部变量       函数/局部内     函数/局部内     栈             否
全局变量       整个程序        整个程序运行期  data/bss       自动初始化0     其他源文件需要用extern声明这个全局变量
静态局部变量    所定义的函数    整个程序运行期  data/bss       自动初始化0     第一次使用前只被初始化一次
静态全局变量    所定义的文件    整个程序运行期  data/bss       自动初始化0     static定义  无法在其他文件中使用

malloc    只申请空间，空间内容为随机值，不初始化；
calloc    申请空间，空间全部初始化为0。
realloc   重新申请空间，不初始化；



EOF 一般定义为 -1
int fgetc(FILE *fp) ; 中
fgetc() reads the next character from stream and returns it as an unsigned char cast to an int, or EOF on end of file or error。
"unsigned char cast to an int",unsigned char 转换成的 int 是不会出现 负数 的，所以 EOF 可以和文件里面的字符区别开来。


int len = sizeof(array)/sizeof(array[1]);  // 数组的长度 = 数组所占的大小/单个数组元素所占的大小


1 位操作代码
#define SET_BIT(reg, bit)    ((reg) |= (1 << (bit)))       // 设置某个位为1
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1 << (bit)))      // 清除某个位为0
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit)))       // 切换某个位的状态
#define READ_BIT(reg, bit)   (((reg) >> (bit)) & 1)        // 读取某个位的值
这些宏定义可以在操作寄存器位时提供方便。例如，使用SET_BIT(PORTA, 3)可以将寄存器PORTA的第3位设置为1。


2 延迟函数
void delay_ms(unsigned int ms) {
    for (unsigned int i = 0; i < ms; i++) {
        for (volatile unsigned int j = 0; j < 6000; j++) {
            // 空循环一段时间
        }
    }
}
这是一个简单的毫秒级延迟函数。通过嵌套循环来实现一定的延迟时间，可以用于需要精确延迟的场景。


3 外部中断处理
#include <avr/interrupt.h>
void init_external_interrupt() {
    // 配置外部中断触发条件
    // ...
    // 启用外部中断
    sei();
}

ISR(INT0_vect) {
    // 外部中断0中断处理程序
}

ISR(INT1_vect) {
    // 外部中断1中断处理程序
}
这段代码使用了Atmel AVR微控制器的外部中断处理机制。通过配置外部中断触发条件和编写中断处理程序，可以实现对外部事件的实时响应。


4 字节序转换
uint16_t swap_bytes(uint16_t value) {
    return (value << 8) | (value >> 8);
}
这段代码用于交换一个16位整数的高低字节顺序，常用于处理不同字节序的数据。


5 CRC校验
uint16_t calculate_crc(const uint8_t *data, size_t length) {
    uint16_t crc = 0;
    for (size_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x8005;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}
这段代码用于计算循环冗余校验(CRC)，常用于数据传输的完整性校验。


6 字符串拷贝
char *string_copy(char *dest, const char *src) {
    char *p = dest;
    while ((*p++ = *src++)) ;
    return dest;
}
这段代码实现了字符串拷贝功能，将源字符串复制到目标字符串，包括字符串结尾的空字符。


7.内存复制
void *memory_copy(void *dest, const void *src, size_t count) {
    char *d = dest;
    const char *s = src;
    while (count--) {
        *d++ = *s++;
    }
    return dest;
}
这段代码实现了内存复制功能，将源内存区域的数据复制到目标内存区域，逐字节复制指定数量的数据。


8 位字段操作
struct {
    unsigned int flag1: 1;
    unsigned int flag2: 1;
    unsigned int flag3: 1;
    // ...
} status;

void set_flag(unsigned int *flags, unsigned int position) {
    *flags |= (1 << position);
}

void clear_flag(unsigned int *flags, unsigned int position) {
    *flags &= ~(1 << position);
}

int check_flag(unsigned int flags, unsigned int position) {
    return (flags >> position) & 1;
}
这段代码演示了如何使用位字段(bit fields)操作来管理标志位。
结构体status中的每个成员都只占据一个位，可以通过位操作函数来设置、清除和检查特定位置的标志位。


9.时钟周期计数
#include <stdint.h>
uint32_t get_cycle_count() {
    uint32_t cycle_count;
    __asm__ volatile("rdcycle %0" : "=r"(cycle_count));
    return cycle_count;
}
这段代码使用了嵌入式处理器的内置指令来获取时钟周期计数。通过读取处理器的计数寄存器，可以精确测量代码段的执行时间，用于性能优化和调试。



https://mp.weixin.qq.com/s/tim50z93e-E-Jbl08rDY2A  # Linux内核中常用的C语言技巧
GUN C
1 typeof
#define max(a,b) ((a) > (b) ? (a) : (b))  # 比较两个数大小返回最大值的经典宏写法

int x = 1, y = 2;
printf("max=%d\n", max(x++, y++));        # max=3  这是错误的结果，我们希望的是max(1,2)，返回max=2。
printf("x = %d, y = %d\n", x, y);         # x=2，y=4

#define max(a, b) ({        \             # Linux内核中 如果不知道具体的数据类型，可以使用typeof类转换宏
    typeof(a) _a = (a);      \            # GNU C中，若知道a和b的类型，可在宏里面定义变量，将a, b赋值给变量，然后再比较
    typeof(b) _b = (b);      \            # 定义一个b类型的变量_b，将b赋值给_b
    (void) (&_a == &_b);   \              # 判断两个数的类型是否相同，如果不相同，会抛出一个警告。因为a和b的类型不一样，
    _a > _b ? _a : _b; })                 # 其指针类型也会不一样，两个不一样的指针类型进行比较操作，会抛出一个编译警告。

//typeof的参数可以是表达式或类型
//参数是类型
typeof(int *) a,b;//等价于：int *a,*b;

//参数是表达式
int foo();
typeof(foo()) var;//声明了int类型的var变量，因为表达式foo()是int类型的。由于表达式不会被执行，所以不会调用foo函数。


2 零长数组
零长数组，又叫柔性数组。而它的作用主要就是为了满足需要变长度的结构体，因此有时也习惯性地称为变长数组。
用法：在一个结构体的最后, 申明一个长度为0的数组, 就可以使得这个结构体是可变长的。
对于编译器来说, 此时长度为0的数组并不占用空间, 因为数组名本身不占空间, 它只是一个偏移量,
 数组名这个符号本身代表了一个不可修改的地址常量

结构体中定义零长数组：
<mm/percpu.c>
struct pcpu_chunk {
    struct list_head  list;
    unsigned long    populated[];  /* 变长数组 */
};
数据结构最后一个元素被定义为零长度数组，不占结构体空间。这样，我们可以根据对象大小动态地分配结构的大小。

struct line {
    int length;
    char contents[0];
};
struct line *thisline = malloc(sizeof(struct line) + this_length);
thisline->length = this_length;
如上例所示，struct line数据结构定义了一个int length变量和一个变长数组contents[0]， 这个struct line数据结构的大小
 只包含int类型的大小，不包含contents的大小，也就是 sizeof (struct line) = sizeof (int)。
创建结构体对象时，可根据实际的需要指定这个可变长数组的长度，并分配相应的空间，如上述实例代码分配了this_length 字节的内存，
 并且可以通过contents[index]来访问第index个地址的数据。


3 case范围
GNU C语言支持指定一个case的范围作为一个标签，如：
case low ...high:
case 'A' ...'Z':
这里low到high表示一个区间范围，在ASCII字符代码中也非常有用。下面是Linux内核中的代码例子。

<arch/x86/platform/uv/tlb_uv.c>

static int local_atoi(const char *name){
    int val = 0;
    for (;; name++) {
        switch (*name) {
            case '0' ...'9':
                val = 10*val+(*name-'0');
                break;
            default:
                return val;
        }
    }
}
另外，还可以用整形数来表示范围，但是这里需要注意在“...”两边有空格，否则编译会出错。

<drivers/usb/gadget/udc/at91_udc.c>

static int at91sam9261_udc_init(struct at91_udc *udc){
    for (i = 0; i < NUM_ENDPOINTS; i++) {
        ep = &udc->ep[i];
        switch (i) {
            case 0:
                ep->maxpacket = 8;
                break;
            case 1 ... 3:
                ep->maxpacket = 64;
                break;
            case 4 ... 5:
                ep->maxpacket = 256;
                break;
        }
    }
}


4 标号元素
GNU C语言可以通过指定索引或结构体成员名来初始化，不必按照原来的固定顺序进行初始化。
结构体成员的初始化在 Linux 内核中经常使用，如在设备驱动中初始化file_operations数据结构：

<drivers/char/mem.c>
static const struct file_operations zero_fops = {
    .llseek      = zero_lseek,
    .read        = new_sync_read,
    .write       = write_zero,
    .read_iter     = read_iter_zero,
    .aio_write     = aio_write_zero,
    .mmap        = mmap_zero,
};
如上述代码中的zero_fops的成员llseek初始化为zero_lseek函数，read成员初始化为new_sync_read函数，依次类推。
 当file_operations数据结构的定义发生变化时，这种初始化方法依然能保证已知元素的正确性，对于未初始化成员的值为0或者NULL。


5 可变参数宏
在GNU C语言中，宏可以接受可变数目的参数，主要用在输出函数里。例如：
<include/linux/printk.h>
#define pr_debug(fmt, ...) \
dynamic_pr_debug(fmt, ##__VA_ARGS__)
“...”代表一个可以变化的参数表，“__VA_ARGS__”是编译器保留字段，预处理时把参数传递给宏。
 当宏的调用展开时，实际参数就传递给dynamic_pr_debug函数了。


6 函数属性
GNU C语言允许声明函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute），
 以便编译器进行特定方面的优化和更仔细的代码检查。特殊属性语法格式为：
__attribute__ ((attribute-list))
attribute-list的定义有很多，如noreturn、format以及const等。此外，还可以定义一些和处理器体系结构相关的函数属性，
 如ARM体系结构中可以定义interrupt、isr等属性。

下面是Linux内核中使用format属性的一个例子。
<drivers/staging/lustru/include/linux/libcfs/>
int libcfs_debug_msg(struct libcfs_debug_msg_data *msgdata,const char *format1, ...)__attribute__ ((format (printf, 2, 3)));
libcfs_debug_msg()函数里声明了一个format函数属性，它会告诉编译器按照printf的参数表的格式规则对该函数参数进行检查。
 数字2表示第二个参数为格式化字符串，数字3表示参数“...”里的第一个参数在函数参数总数中排在第几个。

noreturn属性告诉编译器，该函数从不返回值，这可以消除一些不必要的警告信息。例如以下函数，函数不会返回：
void __attribute__((noreturn)) die(void);

const 属性会让编译器只调用该函数一次，以后再调用时只需要返回第一次结果即可，从而提高效率。
static inline u32 __attribute_const__ read_cpuid_cachetype(void){
    return read_cpuid(CTR_EL0);
}

Linux还有一些其他的函数属性，被定义在compiler-gcc.h文件中。
#define __pure           __attribute__((pure))
#define __aligned(x)        __attribute__((aligned(x)))
#define __printf(a, b)      __attribute__((format(printf, a, b)))
#define __scanf(a, b)       __attribute__((format(scanf, a, b)))
#define noinline          __attribute__((noinline))
#define __attribute_const__   __attribute__((__const__))
#define __maybe_unused      __attribute__((unused))
#define __always_unused      __attribute__((unused))


7 变量属性和类型属性
变量属性可以对变量或结构体成员进行属性设置。类型属性常见的属性有alignment、packed和sections等。

alignment属性规定变量或者结构体成员的最小对齐格式，以字节为单位。
struct qib_user_info {
    __u32 spu_userversion;
    __u64 spu_base_info;
} __aligned(8);
在这个例子中，编译器以8字节对齐的方式来分配qib_user_info这个数据结构。

packed属性可以使变量或者结构体成员使用最小的对齐方式，对变量是以字节对齐，对域是以位对齐。
struct test{
 char a;
    int x[2] __attribute__ ((packed));
};
x成员使用了packed属性，它会存储在变量a后面，所以这个结构体一共占用9字节。


8 内建函数
内建函数以“_builtin_”作为函数名前缀。下面介绍Linux内核常用的一些内建函数。

__builtin_constant_p(x)：判断x是否在编译时就可以被确定为常量。如果x为常量，该函数返回1，否则返回0。

__builtin_expect(exp, c)：这里的意思是exp==c的概率很大，用来引导GCC编译器进行条件分支预测。开发人员知道最可能执行哪个分支，
 并将最有可能执行的分支告诉编译器，让编译器优化指令序列，使指令尽可能地顺序执行，从而提高CPU预取指令的正确率。
#define __swab16(x)        \
(__builtin_constant_p((__u16)(x)) ?  \
___constant_swab16(x) :      \
__fswab16(x))__builtin_expect(exp, c)

Linux内核中经常见到likely()和unlikely()函数，本质也是 __builtin_expect()：
#define LIKELY(x) __builtin_expect(!!(x), 1) //x很可能为真
#define UNLIKELY(x) __builtin_expect(!!(x), 0) //x很可能为假

__builtin_prefetch(const void *addr, int rw, int locality)：主动进行数据预取，
 在使用地址addr的值之前就把其值加载到cache中，减少读取的延迟，从而提高性能。
该函数可以接受3个参数：
第一个参数addr表示要预取数据的地址；
第二个参数rw表示读写属性，1表示可写，0表示只读；
第三个参数locality表示数据在cache中的时间局部性，其中0表示读取完addr的之后不用保留在cache中，
 而1～3表示时间局部性逐渐增强。如下面的prefetch()和prefetchw()函数的实现。
<include/linux/prefetch.h>
#define prefetch(x) __builtin_prefetch(x)
#define prefetchw(x) __builtin_prefetch(x,1)

下面是使用prefetch()函数进行优化的一个例子。
<mm/page_alloc.c>
void __init __free_pages_bootmem(struct page *page, unsigned int order){
    unsigned int nr_pages = 1 << order;
    struct page *p = page;
    unsigned int loop;
    prefetchw(p);
    for (loop = 0; loop < (nr_pages - 1); loop++, p++) {
        prefetchw(p + 1);
        __ClearPageReserved(p);
        set_page_count(p, 0);
    }
    …
}
在处理struct page数据之前，通过prefetchw()预取到cache中，从而提升性能。


9 asmlinkage
在标准C语言中，函数的形参在实际传入参数时会涉及参数存放问题。
对于x86架构，函数参数和局部变量被一起分配到函数的局部堆栈里。x86中对asmlinkage的定义：

<arch/x86/include/asm/linkage.h>
#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))

attribute((regparm(0)))：告诉编译器该函数不需要通过任何寄存器来传递参数，只通过堆栈来传递。

对于ARM来说，函数参数的传递有一套ATPCS标准，即通过寄存器来传递。
ARM中的R0～R4寄存器存放传入参数，当参数超过5个时，多余的参数被存放在局部堆栈中。所以，ARM平台没有定义asmlinkage。

<include/linux/linkage.h>
#define asmlinkage CPP_ASMLINKAGE
#define asmlinkage CPP_ASMLINKAGE


10 UL
在Linux内核代码中，我们经常会看到一些数字的定义使用了UL后缀修饰。
数字常量会被隐形定义为int类型，两个int类型相加的结果可能会发生溢出。
因此使用UL强制把int类型数据转换为unsigned long类型，这是为了保证运算过程不会因为int的位数不同而导致溢出。

1 ：表示有符号整型数字1
UL：表示无符号长整型数字1





https://juejin.cn/post/7113553874962776095  # c/c++中，预编译指令用法汇总
https://www.cnblogs.com/limanjihe/p/10155100.html # C/C++中的预编译指令
1 概述
一般来说c/c++ 程序的编译过程分为如下几个阶段：预处理、编译、汇编、链接。
其中预处理阶段，读取c源程序，对其中的伪指令（以#开头的指令）和特殊符号进行处理。
或者说是扫描源代码，对其进行初步的整理和转换，产生新的源代码（还是文本文件）提供给编译器。
预处理过程先于编译器对源代码进行处理。目前绝大多数编译器都包含了预处理程序，但通常认为它们是独立于编译器的。
预处理过程读入源代码，检查包含预处理指令的语句和宏定义，并对源代码进行相应的转换。预处理过程还会删除程序中的注释和多余的空白字符。
                                                         printf.o
 hello.c             hello.i           hello.s           hello.o           hello
—————————> 预处理器 —————————> 编译器 —————————> 汇编器 —————————> 连接器 ———————>
文本源文件         预处理后文本      汇编程序文本    可重定位程序二进制  可执行程序二进制

预处理过程由独立的程序执行，与 c/c++语言无关，故而遵循与c/c++不同的语法规则。预处理语句遵循以下几个语法规则：
  预处理指令必须为所在行的第一个非空白字符；
  一条完整的预处理指令必须处于同一行中；
  预处理指令与 c/c++ 语句不同，在指令末尾不应该加入分号( ';' )。
预处理程序依次扫描源文件，并对遇到的预处理指令进行处理，直到扫描完所有源文件内容，完成预处理过程，
 经过预处理过程的文件一般使用 .i 作为后缀。


2 预编译指令
#define   //宏定义命名，定义一个标识符来表示一个常量
#include  //文件包含命令，用来引入对应的头文件或其他文件
#undef    //来将前面定义的宏标识符取消定义
#ifdef    //条件编译
#ifndef   //条件编译
#if       //条件编译
#else     //条件编译
#elif     //条件编译
#endif    //条件编译
#error    //用于生成一个编译错误消息

__DATE__  //当前日期，一个以 “MMM DD YYYY” 格式表示的字符串常量
__TIME__  //当前时间，一个以 “HH:MM:SS” 格式表示的字符串常量。
__FILE__  //这会包含当前文件名，一个字符串常量。
__LINE__  //这会包含当前行号，一个十进制常量。
__STDC__  //当编译器以 ANSI 标准编译时，则定义为 1；判断该文件是不是标准 C 程序。


2.1 #define
#define又称宏定义，标识符为所定义的宏名，简称宏。
#define指令可以认为是给表达式"起"一个别名,在预处理器进行处理时,会将所有出现别名的地方替换为对应的表达式,
表达式可以是数字、字符串、计算表达式。其特点是定义的标识符不占内存，只是一个临时的符号，预编译后这个符号就不存在了。
其一般用法如下：

#define  标识符  表达式   //注意, 最后没有分号
/*例子*/
#define MACRO EXPRESSION  //预处理在源程序中遇到MACRO时,会将其替换为EXPRESSION

在使用#define语句时,有几个地方需要注意:

预处理程序仅进行字符对象的替换,即将字符串MACRO替换为字符串EXPRESSION，并不会对替换的内容进行语义解析，
 故而在使用#define定义常量的别名时应该注意直接替换是否会造成潜在的语义改变；
#define指令将MACRO后的第一个空白字符作为MACRO与EXPRESSION的分界,EXPRESSION部分对应为自MACRO后
 第一个空白字符开始到行尾换行符的所有内容。例如在#define后面加上错误的分号(;)，也会被宏替换进去；
#define指令还可以定义接收参数的宏，用于定义某些重复使用但又比较简单的计算流程，比如进行两个数大小的比较。


2.2 #include
#include叫做文件包含命令，用来引入对应的头文件(.h文件)或其他文件。其一般有两种形式，#include <stdio,h>和#include "stdio.h"。
当预处理器遇到#include指令时，会将该指令指定的头文件内容复制到源文件 #include指令所在的位置，
 即使用指定头文件的内容替换#include指令所在行。
使用尖括号< >和双引号" "的区别在于头文件的搜索路径不同：
  使用尖括号< >，编译器会到系统路径下查找头文件；
  而使用双引号" "，编译器首先在当前目录下查找头文件，如果没有找到，再到系统路径下查找；
  使用双引号比使用尖括号多了一个查找路径，它的功能更为强大。


2.3 #undef
#undef移除（取消定义）之前使用#define创建的标识符(宏)。因此，后续出现的标识符(宏)被预处理器忽略。
若要使用#undef删除带参数标识符（带参数宏），请仅#undef 标识符，不用带参数列表。如下代码示例：

#define WIDTH 80
#define ADD( X, Y ) ((X) + (Y))
.
.
.
#undef WIDTH
#undef ADD


2.4 条件编译（一）
该#if指令包含#elif、#else和#endif指令，控制源文件部分编译。
当某个条件表达式的值为真时，则预处理器会将对应的代码片段包含进源文件中，而其他部分则被直接忽略。
在源文件中，每个#if指令都必须由结束的#endif指令匹配。
在#if指令和#endif指令之间可以有任意数目的#elif指令，但最多只允许有一个#else指令。
如果存在#else指令，然后其后面只能接上#endif指令，如下代码所示。
要强调的一点是，预处理指令均由预处理器进行处理，所以其支持的判断表达式与 c/c++ 本身支持的表达式有所区别。
预处理指令中条件判断中的条件表达式仅可以包括 #define定义的常量、整型、以及这些量构成的算数和逻辑表达式
（可以看到 c/c++ 程序中定义的变量是不被支持的，同时也不支持对浮点型的判断 ）。

注意如果要完成多个宏定义控制同一代码分支的功能，可以使用如下例子2的写法，#if defined TEST1 || defined TEST2。

#if 条件表达式1
    code1
#elif 条件表达式2
    code2
#elif 条件表达式3
    code3
#else
    code4
#endif

/*例子1*/
#define OPTION 2

#if OPTION == 1
cout << "Option: 1" << endl;
#elif OPTION == 2
cout << "Option: 2" << endl; //选择这句
#else
cout << "Option: Illegal" << endl;
#endif

/*例子2*/
/* TEST1 或 TEST2被定义，则选择执行printf1，否则执行printf2 */
#if defined TEST1 || defined TEST2
 printf1(".....");
#else
 printf2(".....");
#endif

/* TEST1 或 TEST2未被定义，则选择执行printf1，否则执行printf2 */
#if !defined TEST1 || !defined TEST2
 printf1(".....");
#else
 printf2(".....");
#endif


2.5 条件编译（二）
预处理指令#ifndef、#ifdef的效果等价于指令#if与defined运算符一同使用的场合。如下代码所示，例子1展示了两种等价的写法。
但是如果要完成多个宏定义控制同一代码分支的功能，还是需要用#if defined TEST1 || defined TEST2的写法，如条件编译（一） 章节所述。
/*上面两个的写法等价于下面的两个写法*/
#ifdef 宏定义
#ifndef 宏定义

#if defined 宏定义
#if !defined 宏定义

/*例子1*/
#if defined( TEST )
    code
#endif

#ifdef TEST
    code
#endif

#if !defined( TEST )
    code
#endif

#ifndef TEST
    code
#endif


2.6 #error
#error指令将使编译器显示一条错误信息，然后停止编译，用法如下。
在代码分支较多时，无法判断编译哪一个代码分支，可以用#error指令进行标记。
当然在实际工作中，很多时候是写一段乱代码在分支中，看是否有编译报错来判断。
但最好是使用已经设计好的#error指令，其可以显示一条自定义报错信息。

#if !defined(__cplusplus)
#error C++ compiler required.
#endif

#error指令在编译时输出编译错误信息，可以方便程序员检查出现的错误。
void test5()
{
#define OPTION 3
#if OPTION == 1
    cout << "Option： 1" << endl;
#elif OPTION == 2
    cout << "Option: 2" << endl;
#else
#error ILLEGAL OPTION! //fatal error C1189: #error :  ILLEGAL OPTION!
#endif
}


2.7 特殊符号
预编译程序可以识别一些特殊符号。预编译程序对于在源程序中出现的这些特殊符号将用合适的值进行替换。
这些特殊符号包括：__DATE__、 __TIME__、__FILE__、 __LINE__、 __STDC__。注意，是双下划线，而不是单下划线 ：

__FILE__包含当前程序文件名的字符串；
__LINE__表示当前行号的整数；
__DATE__包含当前日期的字符串；
__STDC__如果编译器遵循ANSI C标准，它就是个非零值；
__TIME__包含当前时间的字符串。

#include<stdio.h>

int main()
{
    printf("Hello World!\n");
    printf("%s\n", __FILE__);
    printf("%d\n", __LINE__);
    printf("%s\n", __DATE__);
    printf("%d\n", __TIME__);
    printf("%d\n", __STDC__);

 return 0;
}

2.7.1 #line指令
C语言中可以使用__FILE__表示本行语句所在源文件的文件名，使用__LINE__表示本行语句在源文件中的位置信息。
#line指令可以重新设定这两个变量的值，其语法格式为
#line number["filename"]
其中第二个参数文件名是可省略的，并且其指定的行号在实际的下一行语句才会发生作用。
void test4()
{
    cout << "Current File: " << __FILE__ << endl; //Current File: d:\test.cpp
    cout << "Current Line: " << __LINE__ << endl; //Current Line: 48
    #line 1000 "wrongfile"
    cout << "Current File: " << __FILE__ << endl; //Current File: d:\wrongfile
    cout << "Current Line: " << __LINE__ << endl; //Current Line: 1001
}


2.8 讨论#和##
字符串化运算符#将宏参数转换为字符串文本；标记粘贴运算符##把两个参数粘贴在一起，其含义就是粘贴之后所形成标识符的定义。
如下例子1，定义了一个带参数的宏paster(n)，在调用paster(9);后，宏展开为printf_s( "token" #9 " = %d", token##9 );，
#9的含义为字符串"9"，token##9的含义为token9，其是一个标识符，类型为int，值为9。
如下例子2#define STR(s) #s，利用#可以很轻松定义出一个字符串转换函数。

/*例子1*/
#include <stdio.h>
#define paster(n) printf_s( "token" #n " = %d", token##n )
int token9 = 9;

int main()
{
   paster(9); //输出：token9 = 9
}

/*例子2*/
#define STR(s)     #s


2.9 杂项
2.9.1 多行宏定义的使用
\是续行操作符，也就是宏定义一行写不完，需要多行写，就需要在每一行的后面加上续行操作符，
注意字符\后要紧跟回车键，中间不能有空格或其他字符。

#define __HAL_RCC_GPIOC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);\
/* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)


2.10 #pragma指令
设定编译器的状态或者是指示编译器完成一些特定的动作，它有许多不同的参数。

2.10.1 #pragma once
在头文件的最开始加入这条指令可以保证头文件只被编译一次。
它可以实现上述使用#ifndef实现不重复包含头文件同样的功能，但可能会有部分编译系统不支持。

2.10.2 #pragma message
该指令能够让编译器遇到这条指令时就在编译输出窗口中将消息文本打印出来。
其使用方法为：#pragma message(“消息文本”)，通过这条指令我们可以方便地记录在是否在源代码中定义过某个宏，如
#define ISPC
#ifdef ISPC
#pragma message("Macro ISPC is defined") //编译输出：Macro ISPC is defined
#endif

2.10.3 #pragma warning
该指令能够控制编译器发出警告的方式，其用法举例如：#pragma warning(disable : 4507 34; once : 4385; error : 164)
这个指令有三部分组成，其中disable部分表示忽略编号为4507和34的警告信息，once部分表示编号为4385的警告信息只显示一次，error部分表示把编号为164的警告信息当做错误。
另外，其还有两个用法
#pragma warning(push [, n])：保存所有警告信息的现有的警告状态，后面n是可选的，表示把全局警告等级设为n。
#pragma warning(pop)：弹出最后一个警告信息，取消在入栈和出栈之间所作的一切改动。
具体例如如下：
void test6()
{
#pragma warning(push) //保存编译器警告状态
#pragma warning(disable:4305) //取消4305的警告
    bool a = 5; //无警告信息
#pragma warning(pop) //恢复之前的警告
    bool b = 5; // warning C4305: 'initializing' : truncation from 'int' to 'bool'
}

2.10.4 #pragma comment
该指令将一个注释记录放入一个对象文件或可执行文件中。其使用方法为：
#pragma comment(comment-type ,["commentstring"])
comment-type ：是一个预定义的标识符，指定注释的类型，应该是compiler，exestr，lib，linker之一。
#pragma comment(lib, "my.lib")  // lib关键字，可以帮我们连入一个库文件

2.10.5 #pragma hdrstop
该指令表示预编译头文件到此为止，后面的头文件不进行预编译。

2.10.6 #pragma resource
该指令表示把指定文件中的资源加入工程，如
#pragma resource "*.dfm"

2.10.7 #pragma code_seg
该指令能够设置程序中函数代码存放的代码段，开发驱动程序的时候会使用到。使用方法为：
#pragma code_seg(["section-name" [,"section-class"] ])。

2.10.8 #pragma data_seg
该指令建立一个新的数据段并定义共享数据。一般用于DLL中，在DLL中定义一个共享的有名字的数据段，
这个数据段中的全局变量可以被多个进程共享，否则多个进程之间无法共享DLL中的全局变量。其使用方法为：
#pragma data_seg("MyData")
int value; //共享数据
#pragma data_seg()

2.10.9 #pragma pack
该指令规定数据在内存中的对齐长度，具体可以参考这里。

#pragma pack(1)
struct S{char a; int b; };
void test7(){ cout << sizeof(S) << endl; }


3 总结
c/c++ 程序的编译过程分为如下几个阶段：预处理、编译、汇编、链接；
预处理过程由独立的程序执行，与c/c++语言无关，故而遵循与c/c++不同的语法规则；
如果要完成多个宏定义控制同一代码分支的功能，可以使用如下的写法，#if defined TEST1 || defined TEST2；
预编译程序可以识别一些特殊符号，这些特殊符号包括：__DATE__、 __TIME__、__FILE__、 __LINE__、 __STDC__；
字符串化运算符#将宏参数转换为字符串文本；标记粘贴运算符##把两个参数粘贴在一起，其含义就是粘贴之后所形成标识符的定义。








