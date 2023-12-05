
https://zhuanlan.zhihu.com/p/655099766     # 深入讲解内存分配函数 malloc 原理及实现
https://zhuanlan.zhihu.com/p/657696118     # C语言 内存管理
https://mp.weixin.qq.com/s/tim50z93e-E-Jbl08rDY2A  # Linux内核中常用的C语言技巧



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




