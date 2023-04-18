
#1 增加 dirto 将所有的.o .d 以及执行文件 等生成的文件 写入临时目录
#2 将gtest文件 放到 gtestsrc 里面

# 下面3个是make的控制函数
# $(error TEXT...)               错误控制 下面的命令不再执行
# $(warning TEXT...)             警告控制
# $(info TEXT...)                显示信息
# make 调试
# "-n" "--just-print" "--dry-run" "--recon" 不执行参数，这些参数只是打印命令，不管目标是否更新，
#   把规则和连带规则下的命令打印出来，但不执行，这些参数对于我们调试makefile很有用处。
# "-t" "--touch" 这个参数的意思就是把目标文件的时间更新，但不更改目标文件。也就是说，make假装编译目标，
#   但不是真正的编译目标，只是把目标变成已编译过的状态。
# "-q" "--question" 这个参数的行为是找目标的意思，也就是说，如果目标存在，那么其什么也不会输出，
#   当然也不会执行编译，如果目标不存在，其会打印出一条出错信息。
# 查看dependency关系
#   "-W <file>;" "--what-if=<file>;" "--assume-new=<file>;" "--new-file=<file>;"
#   这个参数需要指定一个文件。一般是是源文件（或依赖文件），Make会根据规则推导来运行依赖于这个文件的命令，
#   一般来说，可以和"-n"参数一同使用，来查看这个依赖文件所发生的规则命令。
# -d  Print lots of debugging information.
# [=FLAGS]  Print various types of debugging information
# 三个最适合用来调试的命令行选项：
#   --just-print (-n)
#   --print-database (-p)
#   --warn-undefined-variables

# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表
# := 即时赋值
# ?= 延时赋值
# += 附加
# CC 与 CXX 这是 C 与 C++ 编译器命令。默认值一般是 "gcc" 与 "g++"。
# CPPFLAGS will be given to the C preprocessor  这是用于预处理阶段的选项。
# CFLAGS 与 CXXFLAGS
#   CFLAGS 表示用于 C 编译器的选项，CXXFLAGS 表示用于 C++ 编译器的选项。这两个变量实际上涵盖了编译和汇编两个步骤。

dirto=dirto/
dirsrc=gtestsrc/
allcfile:=$(wildcard *.c)
allcppfile:=$(wildcard *.cpp  $(dirsrc)*.cpp)
notusedfile:=testall.cpp testalldemo.cpp $(wildcard *gmock*)
usedcppfile:=$(filter-out $(notusedfile),$(allcppfile))
objc=$(patsubst %.c,%.o,$(allcfile))
objc:=$(addprefix $(dirto),$(objc))
objcpp=$(notdir $(usedcppfile))
objcpp:=$(patsubst %.cpp,%.o,$(objcpp))
objcpp:=$(addprefix $(dirto),$(objcpp))
target=$(dirto)main

# 命令中输入的参数会替换掉makefile中的变量 override指示符会保留 makefile中的变量
# 如下使用make DDD=abc EEE=cba 则 DDD还是123 EEE变为cba
# override DDD+=123 则DDD为 abc 123
override DDD=123
EEE=321

# VPATH
# VPATH变量的值用于指示make如何查找文件 不同文件夹可作为 VPATH 的值同时出现 文件夹的名字之间需要使用分隔符进行区分
#   例如:VPATH := inc src
#   例如:VPATH := inc;src
#   例如:VPATH := inc:src
# make 对于 VAPTH 值的处理方式
#   当前文件夹找不到需要的文件时 VPATH会被使用
#   make会在VPATH指定的文件夹中依次搜索文件 当多个文件夹存在同名文件时选择第一次搜索到的文件
#   VPATH只能决定make的搜索路径 无法决定命令的搜索路径 对于特定的编译命令(gcc) 需要独立指定编译搜索路径
#   gcc -I include-path    <--- 如gcc中 指定头文件的路径
# VPATH存在的问题
#   当inc文件夹中意外出现源文件时,那么可能产生编译错误
#   替换方案:vpath关键字(小写)
#     为不同类型的文件制定不同的搜索路径
#     语法:在directory中搜索符合pattern的规则文集那
#     vpath pattern directory
#     vpath %.h inc
#     vpath %.c src
#     取消搜索规则
#     vpth %.h (取消搜索.h文件)
#     vpath(取消全部)
# 问题一:当VPATH和vpath同时出现,make会如何处理?
# 优先选择vpath,在vpath搜索不到时再选择VPATH
# 问题二:当有两个vpath同时指定两个文件夹时,make如何处理?
# 自上而下优先选择
# 问题三:通过VPATH指定搜索路径后,make如何决定目标文件的最终位置?
# make对路径搜索其实很弱,经常出现一些错误
# 当app.out完全不存在,make默认在当前文件夹创建
# 当app.out存在与src,且依赖文件被更新,但app.out不更新
# 使用GPATH特殊变量指定目标文件夹
# GPATH:=src
# 当app.out完全不存在,make默认在当前文件夹创建
# 当app.out存在与src,且依赖文件被更新,重新执行命令,生成app.out存在src


# 增加了对源文件的 路径搜索 要不生成.d 文件的时候 找不到
vpath %.h ./
vpath %.cpp ./ $(dirsrc)

#CPPFLAGS := -I./

# 自动推到代替main2

all:$(target)
	mkdir -p $(dirto)
#	./$(target)

$(target):$(objcpp) $(objc)
#	g++ -o $@ *.o  -lgtest -pthread
#	g++ -o $@ $(objc) $(objcpp)  -lgtest -pthread
	g++ -o $@ $^ -lgtest -pthread



####这部分生成.d文件的操作 本程序暂时没用 大工程可能有用
# 说明
# 在不使用自动生成依赖时：
# 如果是一个大型项目，必须清楚知道每个源文件包含哪些头文件，并且在加入/删除头文件时修改Makefile。
# 编译器的-M/-MM选项
# 作用：自动寻找源文件中包含的头文件，并生成一个依赖关系。
# 在GNU的C/C++编译器中要使用-MM选项，不然会包含一些标准库的头文件。
# 如何将编译器的功能与Makefile联系到一起
# 让Makefile依赖于源文件的方案并不现实。
# GNU建议把编译器为每一个源文件的自动生成的依赖关系放到一个文件中，例如每个.c文件都对应一个.d文件。
# 细节
# 所有 .d 文件都依赖于 .c 文件。
# 第一行 set -e 表示出错则退出 先删除所有目标，即.d文件。
# 第二行 为每个依赖文件 $<（即.c文件）生成依赖文件，$@表示模式%.d文件，$$$$表示随机编号 $$表示$ $$$$表示$$ 进程id。
# 第三行是一个替换命令，具体查看sed文件本身。正则替换 xx.o : 替换为 xx.o xx.d :
#   \(\)是保留的模式空间 $* 表示makefile中匹配的“茎”， \1表示正则的第一个匹配项
#   sed替换命令的格式是‘s///g’如果没有g，则sed的替换操作只对文本中的第一次出现的匹配模式进行替换。
#   可以通过在’s’之后指定一个不同的字符来更改分隔符。本例中使用 ,
# 第四行是删除临时文件。
# 目标：在编译器生成的依赖关系中加入.d文件的依赖，即把依赖关系 main.o : main.c defs.h 转换为 main.o main.d: main.c defs.h。
# 这样.d文件会自动更新。
# 之后吧这些生成的规则放到Makefile中，通过include命令。要注意顺序，不然可能就会作为make的默认target了。
$(dirto)%.d: %.c
	@set -e; rm -f $@; \
	gcc -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# g++的查找和make的查找不同 vpath不能用于g++ 增加 -I./ 否则 部分.h 文件找不到 或者 CPPFLAGS 中添加
CPPFLAGS+=-I./
$(dirto)%.d: %.cpp
	$(info $$@:$@  $$<:$<  $$^:$^ )
	@set -e; rm -f $@; \
	g++ -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


# 下面是通过include引入.d文件
alldfile = $(patsubst %.c,$(dirto)%.d,$(allcfile)) $(patsubst %.cpp,$(dirto)%.d,$(notdir $(usedcppfile)))
include $(alldfile)
####

#下面这2个也可以不写 利用自动推导
#若写入临时目录 这需要放开
$(objc):$(dirto)%.o:%.c
	gcc -o $@ -c $<
$(objcpp):$(dirto)%.o:%.cpp
#	g++ -o $@ -I./ -c $<
	g++ -o $@ -I./ -c $<



gmock1_tar:=gmock1_
.PHONEY:
gmock1:$(gmock1_tar)
	./$(gmock1_tar)
$(gmock1_tar):gmock1.cpp
	g++ gmock1.cpp -o $(gmock1_tar) -lgtest -lgmock -pthread

gmock1clean:
	rm $(gmock1_tar)

.PHONY: main2
main2:
	gcc -o cfunc.o -c cfunc.c
	g++ -o src.o -c src.cpp
	g++ -o testsrc.o -c testsrc.cpp
	g++ -o testsrc2.o -c testsrc2.cpp
	g++ -o testcfunc.o -c testcfunc.cpp
	g++ -o testFixtures.o -c testFixtures.cpp
	g++ -o testmain.o -c testmain.cpp
	g++ -o main *.o  -lgtest -pthread

clean:
	-rm $(objcpp) $(objc) $(target) $(alldfile)


allsrc=$(wildcard *.cpp)
allo=$(subst .cpp,.o,$(allsrc))
allo2=$(patsubst %.cpp,%.o,$(allsrc))

.PHONY: test
test:
# 打印变量的值
	$(warning $(CC))
	$(info $(CC))
	echo $(CC)
	$(info $(DDD))
#	echo $(CFLAGS)
#	echo $(CPPFLAGS)
#	echo $(CXXFLAGS)
#	$(info $(allsrc))
#	$(info $(allo))
#	$(info $(allo2))
#	@echo allcppfile
#	@echo $(allcppfile)
#	@echo objcpp
#	@echo $(objcpp)
