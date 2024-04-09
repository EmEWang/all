
# 原来的
d_demangle:
#	dmd -c demangle.d
#	dmd -oflibd_demangle.so demangle.o -shared -defaultlib=libphobos2.so

# 后边是自己写的 hotspot的一部分
#https://github.com/lievenhey/d_demangler/tree/master  # 编译时提示的库
#https://dlang.org/download.html                       # Dlang官网 下载编译器  没给arm版的编译器
#https://www.dushibaiyu.com/2023/09/dlang_arm.html     # Dlang（D语言）下ARM嵌入式板子开发
#https://wiki.dlang.org/Cross-compiling_with_LDC       # Cross-compiling with LDC
#https://dlang.org/dmd-linux.html                      # dmd
#https://blog.csdn.net/fqbqrr/article/details/127890422 # d的dub构建配置
#https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/pool/main/libi/libiberty/ # 有说 libd_demangle.lib 是 libiberty的一部分 https://packages.ubuntu.com/jammy/s390x/libiberty-dev/download
#https://github.com/gcc-mirror/gcc/blob/master/libiberty/d-demangle.c # 有说 libd_demangle.lib 是gcc的一部分
#https://github.com/dlang/tools                        # https://code.dlang.org/packages/dtools%3Addemangle
#apt-get install dub              # 安装gub apt-get remove dub
#dpkg -i dmd_2.108.0-0_amd64.deb  # 安装官网下载的编译器 与上一个有冲突  dpkg -r dmd_2.108.0-0_amd64.deb
#
#export CC=aarch64-linux-gnu-gcc
#export CXX=aarch64-linux-gnu-g++

d_demanglearm:
# 结果是arm版本的 arm上使用待验证
#	aarch64-linux-gnu-cpp demangle.o -shared -o libd_demangle.so -m64 -Xlinker --export-dynamic -L/usr/aarch64-linux-gnu/lib -lphobos2 -lpthread -lm -lrt -ldl
#	-v 选项 输出详细信息
#	ldc2 -mtriple=aarch64-linux-gnu -relocation-model=pic -shared -c demangle.d
	ldc2 -mtriple=aarch64 -relocation-model=pic -shared -c demangle.d -v
	aarch64-linux-gnu-g++ demangle.o -shared -o libd_demangle.so -lpthread -lm -lrt -ldl
d_demangle2:
	ldc2 -mtriple=aarch64-linux-gnu -relocation-model=pic -shared -of=libd_demangle.so demangle.d

hello:
	ldc2 hello.d
helloarm:
# 交叉编译的时候有问题
	ldc2 -mtriple=aarch64 -c hello.d
#	aarch64-linux-gnu-g++ hello.o -o hello

.PHONEY clean:
clean:
	rm -f libd_demangle.so demangle.o hello hello.o