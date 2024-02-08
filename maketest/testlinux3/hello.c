// #include <linux/init.h>
#include <linux/module.h>   // 引入相关内核头文件


// 内核模块信息，包括许可证、作者、描述和版本等
MODULE_LICENSE("GPL");   // 代码使用的协议发布，一般声明GPL，不声明，内核可能不会接受，运行时的打印可能打不出来
MODULE_AUTHOR("test@1www.cc");  // 声明代码作者，一般留邮箱或名字，感兴趣的人可以通过该联系方式找到你。
MODULE_DESCRIPTION("test moudlue www");
MODULE_VERSION("1.0");

// 内核模块参数，加载时指定或者动态指定，以此控制模块行为
static char *name = "world";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "Whom this module say hello to");

static int __init hello_init(void)
{
    printk("Hello %s\n", name);   // 内核的打印使用 printk() 函数，使用格式和应用层的 printf() 函数一样。
    return 0;
}
static void __exit hello_exit(void)
{
    printk("Goodbye %s\n", name);
}

// 登记初始化函数及清理函数
module_init(hello_init); // 内核模块的入口函数，不再是main()，在加载时调用，分配资源准备执行环境
module_exit(hello_exit); // 内核模块的清理函数，在卸载时调用，回收资源销毁执行环境
