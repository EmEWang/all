


obj-m+=hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean

# 1模块加载到内核   2模块卸载   3以 fasion 为 name 参数值重新挂载   4卸载模块   5查看内核日志
# 跟内核模块相关还有 insmod 、 rmmod 、 lsmod 、 modinfo 、 modprobe 等命令
test:
	sudo insmod hello.ko
	sudo rmmod hello
	sudo insmod hello.ko name=fasion
	sudo rmmod hello
	dmesg

# 查看模块信息
msg:
	modinfo hello.ko