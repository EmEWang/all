# 预加载技术示例
# server.c 是一个服务 无限运行 强制结束后 没有调用 exit 故不能生成 .gcda
# preload.c 生成一个 so 在调用server之前 预先加载 preload.so 其中有截获方法
#   截获终端消息 并以合理的方式 exit 或者 __gcov_flush 以达到 生成 .gcda 的目的
# LD_PRELOAD，是个环境变量，用于动态库的加载，动态库加载的优先级最高，一般情况下，
#   其加载顺序为LD_PRELOAD>LD_LIBRARY_PATH>/etc/ld.so.cache>/lib>/usr/lib
# Linux操作系统的动态链接库在加载过程中，动态链接器会先读取LD_PRELOAD环境变量和默认配置文件/etc/ld.so.preload，
#   并将读取到的动态链接库文件进行预加载。即使程序不依赖这些动态链接库
ifeq ("$(NAME)","gcov")
CFLAGS+= -fprofile-arcs -ftest-coverage
endif
CFLAGS+= -fprofile-arcs -ftest-coverage
CC=gcc

.PHONE: all
all: hello
	cd ..;pwd;cd ..;pwd
	LD_PRELOAD=./preload.so ./server
#2 或者：
#	echo "/sbin/preload.so" >/etc/ld.so.preload ./server
#3 还可以通过export LD_PRELOAD=$PWD/preload.so写入环境变量，然后执行ldd命令来了解server可执行程序所依赖的动态链接库
# export -n LD_PRELOAD=$PWD/preload.so来删除环境变量  或者 unset LD_PRELOAD

hello: *.c
	@echo $(CFLAGS)
	@${CC} $(CFLAGS) -o server server.c


# 预加载的库
# preload.so server_gcov.c同目录下 然后在编译server.c,运行,执行CTRL+c正常结束server且产生了gcda文件
# -shared是生成共享库格式
# -fPIC选项作用于编译阶段，告诉编译器产生与位置无关代码（Position-Independent Code）；
#   这样一来，产生的代码中就没有绝对地址了，全部使用相对地址，所以代码可以被加载器加载到内存的任意位置，都可以正确的执行。
#   这正是共享库所要求的，共享库被加载时，在内存的位置不是固定的。
preload:
	gcc -shared -fpic preload.c -o preload.so

.PHONE: clean
clean:
	@-rm server *.gcno *.gcda
