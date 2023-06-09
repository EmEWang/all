# 在Makefile中自动生成依赖
# gcc 其实有一些生成用于 Makefile 规则的选项，-M 等，说明如下：
# -MM，忽略依赖中的系统头文件
# -MF，指定生成的规则文件的路径   将结果导入到这个文件 没有的话则输出到屏幕
# -MT，指定规则的目标            指定目标
# -MP，对每一个依赖创建一个 force target，典型输出：
# test.o: test.c test.h
# test.h:
# 没有这个选项的话是不会有 test.h: 的

# 比较难说明每个规则的作用，所以还是用实例好了。
# 一开始，*.o *.d 都不存在，只有一个 main.c
# 执行 make，make 没法读取 sinclude 那行表示的文件 main.d，但由于是 sinclude，忽略这个错误
# 尝试重建 main，发现需要的 main.o 不存在
# 因此尝试先重建 main.c。执行规则 %.o: %.c，生成 main.o 的同时也 生成了 main.d。假设 main.c 包含一个头文件 a.h，
#   那么 main.d 的内容将会是： main.o: main.c foo/a.h foo/a.h:
# 之后如果修改 main.c 或者 foo/a.h，因为 main.d 中的规则都会重建 main.o。
# 再看添加新依赖 bar/b.h 的情况，没错，这时我们的 main.d 是过期的，不能反映 main.c 的真实依赖情况。
#   但注意到 main.d 的过期必然蕴含：main.c 被修改了。根据规则 %.o: %.c，再次重建 main.d 和 main.o。
# 假设我们删除 main.c 中的 #include "foo/a.h"，同样的，main.d 过期了，不能反映 main.c 的真实依赖情况。
#   但注意到 main.d 的过期必然蕴含：main.c 被修改了。根据规则 %.o: %.c，再次重建 main.d 和 main.o。
# 如果我们不改动 main.c 而是直接删除 foo/a.h，那么根据 main.o: main.c foo/a.h，无法重建 main.o，make 报错。
#   注意：foor/a.h 是 force target，它不存在的话不会报错，只是让依赖它的目标强制重建。
#     这也是我们之所以使用 -MP 的原因，否则如果不存在目标为 foo/a.h 的规则，make 会报错：无法重建 foo/a.h。
# 还有种生成依赖的方式是让 main.o 依赖 main.d，main.d 依赖 main.c，但是这种方法可能会导致 make 的重启，
#   当 make 很复杂的时候性能不如前文的方法。

# LINK.c  cc   COMPILE.c  cc -c
PROG := main
SRCS := $(PROG).c

$(PROG): $(SRCS:.c=.o)
	$(LINK.c) $^ -o $@

sinclude $(SRCS:.c=.d)

# $(:=) performs a string replacement.
# $@ is the name of the file being generated (the target).
# So $(@:%.o=%.d) is the name of the file, with the .o extension changed to .d.
# 其实 $@  就是 $(@)  也就是说 @ 才是变量 $@ 就是使用变量
%.o: %.c
	gcc -MM -MP -MT $@ -MF $(@:.o=.d) $<
	$(COMPILE.c) $< -o $@

test:
	$(info LINK.c:$(LINK.c))
	$(info COMPILE.c:$(COMPILE.c))
clean:
	-rm *.o *.d $(PROG)