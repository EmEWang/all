
https://www.zhaixue.cc/makefile/makefile-intro.html  # Makefile 简明教程
https://awesome-programming-books.github.io/linux/%E8%B7%9F%E6%88%91%E4%B8%80%E8%B5%B7%E5%86%99makefile.pdf
https://www.gnu.org/software/make/manual/html_node/index.html


Makefile 的规则是在当前目录下依次找三个文件“GNUmakefile”、“makefile”和“Makefile”

GNU 的 make 工作时的执行步骤
  1 读入所有的 Makefile。
  2 读入被 include 的其它 Makefile。
  3 初始化文件中的变量。
  4 推导隐晦规则，并分析所有规则。
  5 为所有的目标文件创建依赖关系链。
  6 根据依赖关系，决定哪些目标要重新生成。
  7 执行生成命令。
1-5 步为第一个阶段，6-7 为第二个阶段。第一个阶段中，如果定义的变量被使用了，那么，make 会把其展开在使用的位置。
但 make 并不会完全马上展开，make 使用的是拖延战术，如果变量出现在依赖关系的规则中，那么仅当这条依赖被决定要使用了，
变量才会在其内部展开。


make 命令执行后有三个退出码：
  0 # 表示成功执行。
  1 # 如果 make 运行时出现任何错误，其返回 1。
  2 # 如果你使用了 make 的“-q”选项，并且 make 使得一些目标不需要更新，那么返回 2。


通配符
在Makefile中表示一个文件名时，可以使用通配符，通配符有：* 、? 、 […]。通配符的使用方法和含义和在shell中一样。
除此之外，Makefile还有经常使用的几个自动变量也可以看做特殊通配符：
$@：所有目标文件  $^：目标依赖的所有文件 $<：第一个依赖文件  $?：所有更新过的依赖文件
在Makefile中，通配符主要用在两个场合：
1 用在规则的目标和依赖中：make在读取Makefile时会自动对其进行匹配处理（通配符展开）。如：
test: *.o
    gcc -o $@ $^
*.o: *.c
    gcc -c $^
2 用在规则的命令中：通配符的通配处理在shell执行命令时完成。如：
clean:
    rm -f *.o
除了以上两种情况，在其他地方都不能直接使用通配符。需要一些函数（如wildcard）来实现。
如果想列举当前目录下的所有C文件，可以直接使用wildcard函数：$(wildcard *.c)



静态模式
targets: target-pattern:prereq-patterns
  commands
objects = foo.o bar.o
all: $(objects)
$(objects): %.o: %.c
  $(CC) -c $(CFLAGS) $< -o $@


模式规则
“%”的展开发生在变量和函数的展开之后，变量和函数的展开发生在make 载入 Makefile 时，而模式规则中的“%”则发生在运行时。
模式规则中，至少在规则的目标定义中要包含“%”，否则，就是一般的规则。目标中的“%”定义表示对文件名的匹配，“%”表示长度任意的非空字符串。
例如：“%.c”表示以“.c”结尾的文件名（文件名的长度至少为 3），而“s.%.c”则表示以“s.”开头，“.c”结尾的文件名（文件名的长度至少为 5）。
如果“%”定义在目标中，那么，目标中的“%”的值决定了依赖目标中的“%”的值，也就是说，目标中的模式的“%”决定了依赖目标中“%”的样子。
例如有一个模式规则如下：%.o : %.c ; <command ......>
其含义是，指出了怎么从所有的[.c]文件生成相应的[.o]文件的规则。如果要生成的目标是“a.o b.o”，那么“%c”就是“a.c b.c”。
一旦依赖目标中的“%”模式被确定，那么，make 会被要求去匹配当前目录下所有的文件名，一旦找到，make 就会规则下的命令，
所以，在模式规则中，目标可能会是多个的，如果有模式匹配出多个目标，make 就会产生所有的模式目标，
此时，make 关心的是依赖的文件名和生成目标的命令这两件事。
示例   把所有的[.c]文件都编译成[.o]文件
%.o : %.c
  $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

你可以重载内建的隐含规则（或是定义一个全新的），例如你可以重新构造和内建隐含规则不同的命令，如：
%.o : %.c
  $(CC) –c $(CPPFLAGS) $(CFLAGS) -D$(date)
你可以取消内建的隐含规则，只要不在后面写命令就行。如：
%.o : %.s
同样，你也可以重新定义一个全新的隐含规则，其在隐含规则中的位置取决于你在哪里写下这个规则。朝前的位置就靠前。


老式风格的“后缀规则”
后缀规则是一个比较老式的定义隐含规则的方法。后缀规则会被模式规则逐步地取代。因为模式规则更强更清晰。
后缀规则有两种方式：“双后缀”和“单后缀”。
双后缀规则定义了一对后缀：目标文件的后缀和依赖目标（源文件）的后缀。如“.c.o”相当于“%o : %c”。
单后缀规则只定义一个后缀，也就是源文件的后缀。如“.c”相当于“% :%.c”。
后缀规则中所定义的后缀应该是 make 所认识的，如果一个后缀是 make 所认识的，那么这个规则就是单后缀规则，
而如果两个连在一起的后缀都被 make 所认识，那就是双后缀规则。
例如：“.c”和“.o”都是 make 所知道。因而，如果你定义了一个规则是“.c.o”那么其就是双后缀规则，
意义就是“.c”是源文件的后缀，“.o”是目标文件的后缀。如下示例：
.c.o:
  $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
后缀规则不允许任何的依赖文件，如果有依赖文件的话，那就不是后缀规则，那些后缀统统被认为是文件名，如：
.c.o: foo.h
  $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
这个例子，就是说，文件“.c.o”依赖于文件“foo.h”，而不是我们想要的这样：
%.o: %.c foo.h
  $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
后缀规则中，如果没有命令，那是毫无意义的。因为他也不会移去内建的隐含规则。
而要让 make 知道一些特定的后缀，我们可以使用伪目标“.SUFFIXES”来定义或是删除，
如：
 .SUFFIXES: .hack .win
把后缀.hack 和.win 加入后缀列表中的末尾。
 .SUFFIXES: # 删除默认的后缀
 .SUFFIXES: .c .o .h # 定义自己的后缀
先清楚默认后缀，后定义自己的后缀列表。
make 的参数“-r”或“—no-builtin-rules”也会使用得默认的后缀列表为空。
而变量“SUFFIXE”被用来定义默认的后缀列表，你可以用“.SUFFIXES”来改变后缀列表，但  请不要改变变量“SUFFIXE”的值。






@gcc -o a.out a.c  # 命令前添加@，make在编译时就不会打印每条正在执行的命令 默认 会把当前的命令打印出来
-include xxx       # 命令前添加- 出错继续执行
如果你要让上一条命令的结果应用在下一条命令时，你应该使用分号分隔这两条命令。
exec:
  cd /home/hchen
  pwd                  # 上一条命令的执行结果不影响本条
exec:
  cd /home/hchen; pwd  # 起作用


下面3个是make的控制函数
$(error TEXT...)             # 错误控制 下面的命令不再执行
$(warning TEXT...)           # 警告控制
$(info TEXT...)              # 显示信息

make -C subdir1 subdir2 ...  # 等价于 cd subdir1 && $(MAKE) cd subdir2 && $(MAKE) ...
  export AAA=123             # 在主Makefile中导出环境变量 子Makefile中就可以直接使用
make –f hchen.mk             # 指定 Makefile 或 --file
make -s/--slient             # 全面禁止命令的显示
make all                     # 指定目标 默认目标是第一个
make test AAA=111 BBB=222    # 通过命令行定义变量


make 参数
三个最适合用来调试的命令行选项：
  --just-print (-n)
  --print-database (-p)
  --warn-undefined-variables
另外一个很有意思的用法是结合“-p”和“-v”来输出 makefile 被执行时的信息
"-n" "--just-print" "--dry-run" "--recon"    # 仅输出执行过程中的命令序列，但并不执行。
  不执行参数，这些参数只是打印命令，不管目标是否更新，
  把规则和连带规则下的命令打印出来，但不执行，这些参数对于我们调试makefile很有用处。
"-t" "--touch" 这个参数的意思就是把目标文件的时间更新，但不更改目标文件。
  也就是说，make假装编译目标，但不是真正的编译目标，只是把目标变成已编译过的状态。
  相当于 UNIX 的 touch 命令，只是把目标的修改日期变成最新的，也就是阻止生成目标的命令运行。
"-q" "--question" 这个参数的行为是找目标的意思，也就是说，如果目标存在，那么其什么也不会输出，
  当然也不会执行编译，如果目标不存在，其会打印出一条出错信息。
  不运行命令，也不输出。仅仅是检查所指定的目标是否需要更新。如果是 0 则说明要更新，如果是 2 则说明有错误发生。
“-w” “--print-directory” 输出运行 makefile 之前和之后的信息。这个参数对于跟踪嵌套式调用 make 时很有用。
“--no-print-directory” 禁止“-w”选项。
"-W <file>;" "--what-if=<file>;" "--assume-new=<file>;" "--new-file=<file>;" 查看dependency关系
  这个参数需要指定一个文件。一般是是源文件（或依赖文件），Make会根据规则推导来运行依赖于这个文件的命令，
  一般来说，可以和"-n"参数一同使用，来查看这个依赖文件所发生的规则命令。
  假定目标<file>需要更新，如果和“-n”选项使用，那么这个参数会输出该目标更新时的运行动作。
  如果没有“-n”那么就像运行 UNIX 的“touch”命令一样，使得<file>的修改时间为当前时间。
“--warn-undefined-variables” 只要 make 发现有未定义的变量，那么就输出警告信息。
“-B” “--always-make” 认为所有的目标都需要更新（重编译）。
“-C <dir>” “--directory=<dir>”  指定读取 makefile 的目录。如果有多个“-C”参数，make 的解释是后面的路径以前面的
  作为相对路径，并以最后的目录作为被指定目录。如：“make –C ~hchen/test –C prog”等价于“make –C ~hchen/test/prog”。
“—debug[=<options>]” 输出 make 的调试信息。它有几种不同的级别可供选择，如果没有参数，那就是输出最简单
  的调试信息。下面是<options>的取值：
  a # all，输出所有的调试信息。（会非常的多）
  b # basic，只输出简单的调试信息。即输出不需要重编译的目标。
  v # verbose，在 b 选项的级别之上。输出的信息包括哪个 makefile 被解析，不需要被重编译的依赖文件（或是依赖目标）等。
  i # implicit，输出所以的隐含规则。
  j # jobs，输出执行规则中命令的详细信息，如命令的 PID、返回码等。
  m # makefile，输出 make 读取 makefile，更新 makefile，执行makefile 的信息。
“-d” 相当于“--debug=a”。
“-e” “--environment-overrides” 指明环境变量的值覆盖 makefile 中定义的变量的值。
“-f=<file>” “--file=<file>” “--makefile=<file>” 指定需要执行的 makefile。
“-i” “--ignore-errors” 在执行时忽略所有的错误。
“-I <dir>” “--include-dir=<dir>” 指定一个被包含 makefile 的搜索目标。可以使用多个“-I”参数来指定多个目录。
“-j [<jobsnum>]” “--jobs[=<jobsnum>]”  指同时运行命令的个数。如果没有这个参数，make 运行命令时能运行多少就运行多少。
  如果有一个以上的“-j”参数，那么仅最后一个“-j”才是有效的。（注意这个参数在 MS-DOS中是无用的）
“-k” “--keep-going” 出错也不停止运行。如果生成一个目标失败了，那么依赖于其上的目标就不会被执行了。
“-l <load>” “--load-average[=<load]” “—max-load[=<load>]” 指定 make 运行命令的负载。
“-o <file>” “--old-file=<file>” “--assume-old=<file>” 不重新生成的指定的<file>，即使这个目标的依赖文件新于它。
“-p” “--print-data-base” 输出makefile中的所有数据，包括所有的规则和变量。这个参数会让一个简单的makefile都会输出一堆信息。
  如果你只是想输出信息而不想执行 makefile，你可以使用“make -qp”命令。
  如果你想查看执行 makefile 前的预设变量和规则，你可以使用“make –p –f/dev/null”。
  这个参数输出的信息会包含着你的 makefile 文件的文件名和行号，所以，用这个参数来调试你的 makefile 会是很有用的，
  特别是当你的环境变量很复杂的时候。
“-r” “--no-builtin-rules” 禁止 make 使用任何隐含规则。
“-R” “--no-builtin-variabes” 禁止 make 使用任何作用于变量上的隐含规则。
“-s” “--silent” “--quiet” 在命令运行时不输出命令的输出。
“-S” “--no-keep-going” “--stop” 取消“-k”选项的作用。因为有些时候，make 的选项是从环境变量“MAKEFLAGS”中继承下来的。
  所以你可以在命令行中使用这个参数来让环境变量中的“-k”选项失效。



变量
一个变量可以定义在Makefile中，也可以在执行make时通过命令行定义
var2=$(var1)         # 使用 var1 给 var2 赋值  或 ${val1}
$@  目标
$^  所有目标依赖
$<  目标依赖列表中的第一个依赖
$?  所有目标依赖中被修改过的文件 比目标还要新的依赖文件列表
$%  当规则的目标是一个静态库文件时，$%代表静态库的一个成员名
$+  类似$^，但是保留了依赖文件中重复出现的文件
$*  在模式匹配和静态模式规则中，代表目标模式中%的部分。比如hello.c，当匹配模式为%.c时，$*表示hello
$(@D) 表示目标文件的目录部分
$(@F) 表示目标文件的文件名部分
$(*D) 在模式匹配中，表示目标模式中%的目录部分
$(*F) 在模式匹配中，表示目标模式中%的文件名部分
-:  告诉make在编译时忽略所有的错误
@:  告诉make在执行命令前不要显示命令
$:

+=  附加 追加赋值
  OBJS=hello.o
  OBJS+=module.o
  echo $(OBJS)    # hello.o module.o
?=  条件赋值指一个变量如果没有被定义过，就直接给它赋值；如果之前被定义过，那么这条赋值语句就什么都不做。
  CC=gcc
  CC?=arm-linux-gnueabi-gcc
  echo $(CC)      # gcc
:=  即时赋值  解析阶段就立即展开变量
=   延时赋值  解析阶段不会立即展开，而是等到实际使用这个变量时才展开，获得其真正的值
  a = 1
  b = 2
  val_a := $(a)
  val_b  = $(b)
  a = 10
  b = 20
  test:
    echo $(val_a)           # 1
    echo $(val_b)           # 20

override指示符会保留 makefile中的变量  否则 命令中输入的变量会替换掉makefile中的变量
  如使用 make DDD=abc EEE=cba
  override DDD=123     # 则 DDD 还是 123
  override DDD+=123    # 则 DDD 为 abc 123
  EEE=321              # 则 EEE 变为 cba
  EEE+=123             # 则 EEE 变为 cba
  Makefile中的变量分为多种：追加变量、立即变量、展开变量、使用define定义的变量，它们都可以使用override修饰：
  override VARIABLE = VALUE
  override VARIABLE := VALUE
  override VARIABLE += MORE TEXT
  override define foo
  当一个追加变量在定义时使用了override，后续对它的值进行追加时，必须带有override指示符的追加方式。否则对此变量值的追加不会有效。
  .PHONY: all
  override fruits = apple
  fruits += banana
  all:
      @echo "fruits = $(fruits)"     # fruits = apple

使用指定字符串替换掉变量中的字符串
.PHONY: all
SRC := main.c sub.c
OBJ := $(SRC:.c=.o)
all:
    @echo "SRC = $(SRC)"       # SRC = main.c sub.c
    @echo "OBJ = $(OBJ)"       # OBJ = main.o sub.o

模式匹配替换
使用匹配符%匹配变量，使用 % 保留变量值中的指定字符串，然后其他部分使用指定字符串代替。
PHONY: all
SRC := main.c sub.c
OBJ := $(SRC:%.c=%.o)
all:
    @echo "SRC = $(SRC)"       # SRC = main.c sub.c
    @echo "OBJ = $(OBJ)"       # OBJ = main.o sub.o

$(:=) performs a string replacement.
$@ is the name of the file being generated (the target).
So $(@:%.o=%.d) is the name of the file, with the .o extension changed to .d.
其实 $@  就是 $(@)  也就是说 @ 才是变量 $@ 就是使用变量

x = y
y = z
a := $($(x))     # z  把变量的值再当成变量

目标变量
前面所讲的都是“全局变量”，在整个文件都可以访问。
当然，“自动化变量”除外，如“$<”等这种类量的自动化变量就属于“规则型变量”，这种变量的值依赖于规则的目标和依赖目标的定义。
可以为某个目标设置局部变量，这种变量被称为“Target-specificVariable”，它可以和“全局变量”同名，
因为它的作用范围只在这条规则以及连带规则中，所以其值也只在作用范围内有效。而不会影响规则链以外的全局变量的值。
其语法是：
 <target ...> : <variable-assignment>
 <target ...> : overide <variable-assignment>
<variable-assignment>可以是前面讲过的各种赋值表达式，如“=”、“:=”、“+=”或是“？=”。
override是针对于 make 命令行带入的变量，或是系统环境变量。
举例
prog : CFLAGS = -g
prog : prog.o foo.o bar.o
  $(CC) $(CFLAGS) prog.o foo.o bar.o

模式变量  Pattern-specific Variable
给定一种“模式”，可以把变量定义在符合这种模式的所有目标上。
<pattern ...> : <variable-assignment>
<pattern ...> : override <variable-assignment>
make 的“模式”一般是至少含有一个“%”的，所以，我们可以以如下方式给所有以[.o]结尾的目标定义目标变量：
%.o : CFLAGS = -O





编译选项
https://www.cnblogs.com/lidabo/p/6068448.html
CC         # 一般指 gcc   C   编译器命令
CXX        # 一般指 g++   C++ 编译器命令
CPPFLAGS   # 预处理阶段的选项   will be given to the C preprocessor
CFLAGS     # C 编译器的选项  指定头文件.h的路径 如：CFLAGS=-I/usr/include -I/path/include
CXXFLAGS   # C++ 编译器的选项 这两个变量实际上涵盖了编译和汇编两个步骤
LDFLAGS    # 传递给连接器的选项  告诉链接器从哪里寻找库文件  如 LDFLAGS=-L/usr/lib -L/path/to/your/lib
  若LDFLAGS指定-L虽然链接器能找到库，但运行时链接器却找不到，若要让软件运行时库文件的路径也得到扩展，需要增加这两个库给"-Wl,R"
  LDFLAGS = -L/var/xxx/lib -L/opt/mysql/lib -Wl,R/var/xxx/lib -Wl,R/opt/mysql/lib
LIBS       # 链接器要链接哪些库文件，如LIBS = -lpthread -liconv
LINK.c     # 表示 cc
COMPILE.c  # 表示 cc -c



条件判断 ifeq、ifneq、ifdef、ifndef
1 ifeq 关键字 用来判断两个参数是够相等，相等时条件成立为true，不相等为false。一般和变量结合使用
由三个关键字组成：ifeq、else、endif；ifeq和小括号之间要用空格隔开，小括号里的两个参数用逗号隔开
mode = debug
hello: hello.c
ifeq ($(mode),debug)
    @echo "debug mode"
    gcc -g -o hello hello.c
else
    @echo "release mode"
    gcc -o hello hello.c
endif

# make
debug mode
gcc -g -o hello hello.c

2 ifneq 关键字 和ifeq关键字恰恰相反
mode = debug
hello: hello.c
ifneq ($(mode),)
    @echo "debug mode"
    gcc -g -o hello hello.c
else
    @echo "release mode"
    gcc -o hello hello.c
endif

# make
debug mode
gcc -g -o hello hello.c

3 ifdef 关键字 用来判断一个变量是否已经定义。如果变量的值非空（在Makefile中，没有定义的变量的值为空），表达式为真。
如果在Makefile定义一个变量没有赋值，或者没有定义变量，那么这个变量的值都为空
mode =
hello: hello.c
ifdef mode
    @echo "debug mode"
    gcc -g -o hello hello.c
else
    @echo "release mode"
    gcc -o hello hello.c
endif

# make
release mode
gcc -o hello hello.c

4 ifndef 关键字 和ifdef相反，如果一个变量没有定义，表达式为真。
mode =
hello: hello.c
ifndef mode
    @echo "debug mode"
    gcc -g -o hello hello.c
else
    @echo "release mode"
    gcc -o hello hello.c
endif

# make
debug mode
gcc -o hello hello.c




while 循环用于执行一系列命令，直到满足指定条件为止。语法如下：

while(条件)
    # 命令
endwhile

示例：
count := 0
while($(count) < 5)
    @echo $(count)
    count := $(shell expr $(count) + 1)
endwhile
在上述示例中，我们定义了一个变量count，然后使用while循环输出0到4的数字。




for 循环。语法如下：

for VAR in LIST; do \
  CMD 1; \
  CMD 2; \
done

示例：
subdirs="dir1 dir2"
@for dir in ${subdirs}; do \
	echo $${dir}; \
	make -C $${dir} clean ; \
done
注意：要加空格\，这样会视为一条命令；makefile中$有特殊意义，需要用$$来表示$



函数
$(function arguments)   # 函数的使用和变量引用的展开方式相同 同 ${function arguments}
分两类：make内嵌函数和用户自定义函数。内嵌的函数，直接引用就可以了；用户自定义的函数，要通过make的call函数来间接调用。
函数和参数列表之间要用空格隔开，多个参数之间使用逗号隔开。
如果在参数中引用了变量，变量的引用建议和函数引用使用统一格式：要么是一对小括号，要么是一对大括号。

1 用户自定义函数
以define开头，endef结束，给函数传递的参数在函数中使用$(0)、$(1)引用，分别表示第1个参数、第2个参数
对于用户自定义函数，在Makefile中要使用call函数间接调用，各个参数之间使用空格隔开
PHONY: all
define func
    @echo "pram1 = $(0)"
    @echo "pram2 = $(1)"
endef
all:
    $(call func, hello zhaixue.cc)
# make
pram1 = func
pram2 =  hello zhaixue.cc

2 内嵌的函数
SRC  = $(wildcard *.c)
HEAD = $(wildcard *.h)
all:
    @echo "SRC = $(SRC)"
    @echo "HEAD = $(HEAD)"
# ls
add.c  add.h  hello.c  main.c  makefile  sub.c  sub.h
# make
SRC = hello.c main.c add.c sub.c
HEAD = add.h sub.h

2.1 文本处理函数
$(subst old,new,text)     # 实现字符串的替换，将字符串text中的old替换为new  如 OBJ=$(subst .c,.o,$(SRC))
$(patsubst PATTERN, REPLACEMENT, TEXT) # 模式替换：使用通配符 % 代表一个单词中的若干字符，
  在PATTERN和REPLACEMENT如果都包含这个通配符，表示两者表示的是相同的若干个字符，并执行替换操作。
  如 OBJ=$(patsubst %.c, %.o, $(SRC))
$(strip TEXT)             # 去空格函数：一个字符串通常有多个单词，单词之间使用一个或多个空格进行分割，
  将多个连续的空字符合并成一个，并去掉字符串开头、末尾的空字符。空字符包括：空格、多个空格、tab等不可显示的字符。
  如 STR =     hello a    b   c    STRIP_STR = $(strip $(STR))   # hello a b c
$(findstring FIND, IN)    # 查找一个字符串 在字符串IN中查找FIND字符串，如果找到，则返回字符串FIND，否则，返回空。
  如 STR =     hello a    b   c   FIND = $(findstring hello, $(STR))  # hello
$(filter PATTERN…,TEXT)   # 过滤掉字符串TEXT中所有不符合PATTERN模式的单词，只留下符合PATTERN格式的单词
  如 FILE = a.c b.h c.s d.cpp    SRC = $(filter %.c, $(FILE)) # a.c
$(filter-out PATTERN…,TEXT)  # 反过滤函数，过滤掉所有符合PATTERN模式的单词，保留所有不符合此模式的单词，与filter相反
$(sort LIST)              # 单词排序 对字符串LIST中的单词以首字母为准进行排序，并删除重复的单词。
$(word N,TEXT)            # 取单词 从一个字符串TEXT中，按照指定的数目N取单词，返回值是字符串TEXT中的第N个单词。
  如果N的值大于字符串中单词的个数，返回空；如果N为0，则出错。
  如 LIST = one two three  word1 = $(word 1, $(LIST)) # one   word3 = $(word 3, $(LIST)) # three
$(wordlist N, M, TEXT)    # 从一个字符串TEXT中取出从N到M之间的一个单词串
  N 和 M都是从1开始的一个数字，函数的返回值是字符串TEXT中从N到M的一个单词串。当N比字符串TEXT中的单词个数大时，函数返回空。
  如 LIST = one two three  sub_list = $(wordlist 1, 2, $(LIST)) # one two
$(words TEXT)             # 统计单词数目 用来统计一个字符串TEXT中单词的个数，返回值为字符串TEXT中单词的个数
  如 LIST = one two three   len = $(words $(LIST)) # 3
$(firstword NAMES…)       # 取一个字符串中的首个单词 相当于 $(word 1,TEXT)

2.2 文件名处理函数
$(dir NAMES…)             # 从一个路径名中截取目录的部分
  如 LIST = /home/wit/banana.c /usr/include/stdio.h   dir = $(dir $(LIST)) # /home/wit/ /usr/include/
$(notdir NAMES…)          # 和dir函数实现完全相反的功能：从一个文件路径名中取文件名，而不是目录
  如 LIST = /home/wit/banana.c /usr/include/stdio.h   notdir = $(notdir $(LIST)) # banana.c stdio.h
$(suffix NAMES…)          # 从一系列文件名序列中，取出各个文件名的后缀。
  后缀是文件名中以点号 . 开始（包括点号）的部分。若文件名没有后缀， suffix函数则返回空。
  如 LIST = /home/wit/banana.c /usr/include/stdio.h   suffix = $(suffix $(LIST)) # .c .h
$(basename NAMES…)        # 从一系列文件名序列中，取出各个文件名的前缀部分
  如果一个文件名中包括多个点号，basename函数返回最后一个点号之前的文件名部分；如果一个文件名没有前缀，函数返回空字符串。
  如 LIST = /home/wit/banana.c /usr/include/stdio.h   b = $(basename $(LIST)) # /home/wit/banana /usr/include/stdio
$(addsuffix SUFFIX, NAMES…) # 给文件列表中的每个文件名添加后缀SUFFIX
  如 LIST = apple banana peach addsuffix = $(addsuffix .c, $(LIST)) # apple.c banana.c peach.c
$(addprefix SUFFIX, NAMES…) # 给文件列表中的每个文件名添加一个前缀PREFIX
  如 LIST = apple banana peach addprefix =  $(addprefix /, $(LIST)) # /apple.c /banana.c /peach.c
$(join LIST1,LIST2)       # 单词连接 将字符串LIST1和字符串LIST2的各个单词依次连接，合并为新的单词构成的字符串
  如 LIST1 = apple banana peach  LIST2 = .c .h .s  LIST  = $(join $(LIST1), $(LIST2)) # apple.c banana.h peach.s
  如果两个字符串中的单词个数不相等，则只合并前面的单词，剩下的单词不合并
  如 LIST1 = apple banana peach  LIST2 = .c .h  LIST  = $(join $(LIST1), $(LIST2)) # apple.c banana.h peach
$(wildcard PATTERN…)       # 列出当前目录下所有符合PATTREN模式的文件名  其中PATTREN可以使用shell能识别的通配符：？、*等。
  如 LIST  = $(wildcard *.c)  # add.c  hello.c  main.c

2.3 其他函数
$(foreach VAR,LIST,TEXT)  # 把LIST中使用空格分割的单词依次取出并赋值给变量VAR，然后执行TEXT表达式。
  重复这个过程，直到遍历完LIST中的最后一个单词。函数的返回值是TEXT多次计算的结果。
.PHONY: all
dirs = lcd usb media keyboard
srcs = $(foreach dir, $(dirs), $(wildcard $(dir)/*.c))
objs = $(foreach src, $(srcs), $(subst .c,.o,$(src)))
all:
    @echo "srcs = $(srcs)"
    @echo "objs = $(objs)"
# make
srcs =  lcd/lcd.c  usb/usb.c  media/decode.c  keyboard/key.c
objs =  lcd/lcd.o  usb/usb.o  media/decode.o  keyboard/key.o

$(if CONDITION,THEN-PART)
$(if CONDITION,THEN-PART[,ELSE-PART]) #  if 函数提供了在一个函数上下文中实现条件判断的功能，类似于ifeq关键字
  CONDITION表示条件判断，展开后如果非空，则条件为真，执行 THEN-PART部分；否则，如果有ELSE-PART部分，则执行ELSE-PART部分。
  if函数的返回值即执行分支（THEN-PART或ELSE-PART）的表达式值。如果没有ELSE-PART，则返回一个空字符串。
.PHONY: all
install_path = $(if $(install__path), $(install__path), /usr/local)
all:
    @echo "install_path = $(install_path)"
# make
install_path =  /usr/local
# make install_path=/opt
install_path = /opt

$(function arguments) 或
${function arguments}     # 调用用户自定义的函数，则只能使用call函数
PHONY: all
define func
    @echo "pram1 = $(0)"
    @echo "pram2 = $(1)"
endef
all:
    $(call func, hello zhaixue.cc)
给函数传递的参数，在函数内部可以使用$(0)、$(1)…直接使用。call函数是唯一一个可以用来创建新的参数化的函数。
call函数不仅可以用来调用一个用户自定义函数并传参，还可以向一个表达式传参：
$(call <expression>,<parm1>,<parm2>,<parm3>...)
当 make 执行这个函数时，expression表达式中的参数变量，如$(1)，$(2)，$(3)等，会被参数parm1，parm2，parm3依次取代。
而expression的返回值就是 call 函数的返回值。
.PHONY: all
param = $(1) $(2)
reverse_param = $(2) $(1)
str1 = $(call param, hello, zhaixue.cc)
str2 = $(call reverse_param, hello, zhaixue.cc)
all:
    @echo "str1 = $(str1)"
    @echo "str2 = $(str2)"
# make
str1 =  hello  zhaixue.cc
str2 =  zhaixue.cc  hello

$(origin <variable>)      # 作用就是告诉你，你所关注的一个变量是从哪里来的。
如果变量没有定义，origin函数的返回值为：undefined，不同的返回值代表变量的类型不同。常见的返回值如下
default     ：变量是一个默认的定义，比如 CC 这个变量
file        ：这个变量被定义在Makefile中
command line：这个变量是被命令行定义的
override    ：这个变量是被override指示符重新定义过的
automatic   ：一个命令运行中的自动化变量
.PHONY: all
WEB = www.zhaixue.cc
web_type = $(origin WEB)
all:
    @echo "web_type = $(web_type)"
    @echo "cc_type  = $(origin CC)"
    @echo "cmd_type = $(origin CMD)"
# make
web_type = file
cc_type = default
cmd_type = undefined
# make CMD=pwd
web_type = file
cc_type = default
cmd_type = command line

$(shell cmd)              # 运行shell命令 参数是shell命令 和反引号``具有相同的功能 返回值为shell命令的运行结果
.PHONY: all
current_path = $(shell pwd)
all:
    @echo "current_path = $(current_path)"
root@ubuntu:/home/makefile/demo# make
current_path = /home/makefile/demo

$(error TEXT…)            # 当遇到error函数时，就会给用户一个错误提示信息，并终止make的继续执行
需要注意的是：error函数是在函数被调用时才会提示信息并终止make的继续执行。
如果函数出现在命令中，或者出现在一个递归变量的定义里，在读取Makefile时不会出现错误。
而只有包含error函数引用的命令执行时，或者包含这个函数的定义变量被展开时，才会提示错误信息TEXT，并终止make的运行。
.PHONY: all
all:
    @echo "make command start..."
    $(error find a error)
    @echo "make command end..."
# make
makefile:5: *** find a error.  Stop.

$(warning TEXT…)          # 跟error函数类似，也会给用户提示信息，唯一的区别是：不会终止make的运行，make会继续运行下去。
.PHONY: all
all:
    @echo "make command start..."
    $(warning find a error)
    @echo "make command end..."
# make
makefile:5: find a error
make command start...
make command end...





VPATH vpath
VPATH变量的值用于指示make如何查找文件 不同文件夹可作为 VPATH 的值同时出现 文件夹的名字之间需要使用分隔符进行区分
  例如:VPATH := inc src
  例如:VPATH := inc;src
  例如:VPATH := inc:src
make 对于 VAPTH 值的处理方式
  当前文件夹找不到需要的文件时 VPATH会被使用 (当前目录永远是最高优先搜索的地方)
  make会在VPATH指定的文件夹中依次搜索文件 当多个文件夹存在同名文件时选择第一次搜索到的文件
  VPATH只能决定make的搜索路径 无法决定命令的搜索路径 对于特定的编译命令(gcc) 需要独立指定编译搜索路径
  gcc -I include-path    <--- 如gcc中 指定头文件的路径
VPATH存在的问题
  当inc文件夹中意外出现源文件时,那么可能产生编译错误
  替换方案:vpath关键字(小写)
    为不同类型的文件制定不同的搜索路径
    vpath pattern directory   在directory中搜索符合pattern规则的文件
    vpath %.h inc
    vpath %.c src
    取消搜索规则
    vpth %.h (取消搜索.h文件)
    vpath(取消全部)
问题一:当VPATH和vpath同时出现,make会如何处理?
  优先选择vpath,在vpath搜索不到时再选择VPATH
问题二:当有两个vpath同时指定两个文件夹时,make如何处理?
  自上而下优先选择
问题三:通过VPATH指定搜索路径后,make如何决定目标文件的最终位置?
make对路径搜索其实很弱,经常出现一些错误
当app.out完全不存在,make默认在当前文件夹创建
当app.out存在与src,且依赖文件被更新,但app.out不更新
使用GPATH特殊变量指定目标文件夹
GPATH:=src
当app.out完全不存在,make默认在当前文件夹创建
当app.out存在与src,且依赖文件被更新,重新执行命令,生成app.out存在src





将make的输出重定向到文件
数字    含义                   标准叫法
0      标准输入        stdin = standard input
1      标准输出        stdout = standard output
2      标准错误输出   stderr = standard error

1 make xxx > build_output.txt  # make输出的全部信息，输出到某个文件中
此时默认情况是没有改变2=stderr的输出方式，还是屏幕，所以，如果有错误信息，还是可以在屏幕上看到的。
2 make xxx 2> build_output.txt # 只需要把make输出中的错误(及警告)信息输出到文件中ing
相应地，由于1=stdout没有变，还是屏幕，所以，那些命令执行时候输出的正常信息，还是会输出到屏幕上，你还是可以在屏幕上看到的。
3 make xxx 1> build_output.txt # 只需要把make输出中的正常(非错误，非警告)的信息输出到文件中
相应地，由于2=stderr没有变，还是屏幕，所以，那些命令执行时候输出的错误信息，还是会输出到屏幕上，你还是可以在屏幕上看到的。
4 make xxx 1> build_output_normal.txt 2>build_output_error.txt # 想要把正常输出信息和错误信息输出到分别的文件中
即联合使用了1和2，正常信息和错误信息，都输出到对应文件中了。
5 make xxx > build_output_all.txt 2>&1 # 所有的信息都输出到同一个文件中
其中的2>&1表示错误信息输出到&1中，而&1，指的是前面的那个文件：build_output_all.txt 。
注意：上面所有的1,2等数字，后面紧跟着大于号'>' ，中间不能有空格
(在命令行中 直接使用 xxx &> build_output_all.txt 表示所有的信息都输出到同一个文件中)





关于生成 .d 文件
https://www.cnblogs.com/openix/archive/2012/04/17/2453833.html
https://blog.csdn.net/chezhai/article/details/80047990
这部分生成.d文件的操作 大工程可能有用 在不使用自动生成依赖时：
如果是一个大型项目，必须清楚知道每个源文件包含哪些头文件，并且在加入/删除头文件时修改Makefile。
编译器的-M/-MM选项作用：自动寻找源文件中包含的头文件，并生成一个依赖关系。
在GNU的C/C++编译器中要使用-MM选项，不然会包含一些标准库的头文件。
如何将编译器的功能与Makefile联系到一起 让Makefile依赖于源文件的方案并不现实。
GNU建议把编译器为每一个源文件的自动生成的依赖关系放到一个文件中，例如每个.c文件都对应一个.d文件。
所有 .d 文件都依赖于 .c 文件。

%.d: %.c
  $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
  sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
  rm -f $@.$$$$

本人用的是下面这个  作用是头文件变动则重新编译相关的文件 因为添加了 .o 依赖 .h
seq.d : seq.c
  @set -e; rm -f $@; \
  gcc -MM $< > $@.$$$$; \
  sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
  rm -f $@.$$$$

-include seq.d

第一个命令
@set -e    # @关键字告诉make不输出该行命令；-e的作用是，当后面的命令的返回值非0时(出错)，立即退出。
rm -f $@   # 先删除所有目标，即.d文件。
那么为什么要把几个命令写在”同一行“(是对于make来说，因为\的作用就是连接行)，并用分号隔开每个命令？
因为在Makefile这样做才能使上一个命令作用于下一个命令。这里是想要set -e作用于后面的命令。

第二个命令
gcc -MM $< > $@.$$$$
为每个依赖文件 $<（即.c文件）生成依赖文件，$@表示模式%.d文件，$$$$表示随机编号 $$表示$ $$$$表示$$ 进程id。
作用是根据源文件生成依赖关系，并保存到临时文件中。内建变量 $< 的值为第一个依赖文件(那seq.c)，
$$$$ 为字符串 "$$" 由于makefile中所有的$字符都是特殊字符(即使在单引号之中)，要得到普通字符$，需要用 $$ 来转义;
而 $$ 是shell的特殊变量，它的值为当前进程号；使用进程号为后缀的名称创建临时文件，是shell编程常用做法，这样可保证文件唯一性。

第三个命令
是一个替换命令，将目标文件加入依赖关系的目录列表中，并保存到目标文件。将.d文件中作正则替换 xx.o : 替换为 xx.o xx.d :
sed替换命令格式是‘s///g’，若没有g，只对第一次匹配替换。分隔符‘/’可以替换,通过在’s’之后指定一个不同的字符来更改分隔符。
如果需要在规则表达式中使用分隔符，可以在它前面加入反斜杠。
如 d –e ‘s:/usr/local:/usr:g’ mylist.txt  # 把所有出现的/usr/local替换成/usr  使用冒号作为分隔符
\(\)是保留的模式空间，\($*\)表示匹配$*,后面使用\1表示它；
\1表示正则的第一个匹配项，\(\)第一次出现用\1匹配，如果出现多次，分别用\2、\3...匹配
$* 是makefile中匹配的“茎”，表示去掉文件的后缀，只留下基础名字，值为第一个依赖文件去掉后缀的名称(这里即是seq)。
\.表示点"."

第四个命令
删除临时文件。

目标：在编译器生成的依赖关系中加入.d文件的依赖，即把依赖关系 main.o : main.c defs.h 转换为 main.o main.d: main.c defs.h。
这样.d文件会自动更新。
之后吧这些生成的规则放到Makefile中，通过include命令。要注意顺序，不然可能就会作为make的默认target了。




在Makefile中自动生成依赖  例子 maketest/test2
gcc 其实有一些生成用于 Makefile 规则的选项，-M 等，说明如下：
-MM，忽略依赖中的系统头文件
-MF，指定生成的规则文件的路径       将结果导入到这个文件 没有的话则输出到屏幕
-MT，指定规则的目标                指定目标
-MP，对每一个依赖创建一个 force target，典型输出：
test.o: test.c test.h
test.h:
没有这个选项的话是不会有 test.h: 的

Makefile 如下

PROG := main
SRCS := $(PROG).c

# LINK.c  cc   COMPILE.c  cc -c
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

比较难说明每个规则的作用，所以还是用实例好了。

一开始，*.o *.d 都不存在，只有一个 main.c
执行 make，make 没法读取 sinclude 那行表示的文件 main.d，但由于是 sinclude，忽略这个错误
尝试重建 main，发现需要的 main.o 不存在 因此尝试先重建 main.o。
执行规则 %.o: %.c，生成 main.o 的同时也 生成了 main.d。
假设 main.c 包含一个头文件 a.h，那么 main.d 的内容将会是：
main.o: main.c foo/a.h
foo/a.h:
之后如果修改 main.c 或者 foo/a.h，因为 main.d 中的规则都会重建 main.o。

再看添加新依赖 bar/b.h 的情况，没错，这时我们的 main.d 是过期的，不能反映 main.c 的真实依赖情况。
但注意到 main.d 的过期必然蕴含：main.c 被修改了。根据规则 %.o: %.c，再次重建 main.d 和 main.o。

假设我们删除 main.c 中的 #include "foo/a.h"，同样的，main.d 过期了，不能反映 main.c 的真实依赖情况。
但注意到 main.d 的过期必然蕴含：main.c 被修改了。根据规则 %.o: %.c，再次重建 main.d 和 main.o。

如果我们不改动 main.c 而是直接删除 foo/a.h，那么根据 main.o: main.c foo/a.h，无法重建 main.o，make 报错。
注意：foor/a.h 是 force target，它不存在的话不会报错，只是让依赖它的目标强制重建。
这也是我们之所以使用 -MP 的原因，否则如果不存在目标为 foo/a.h 的规则，make 会报错：无法重建 foo/a.h。

还有种生成依赖的方式是让 main.o 依赖 main.d，main.d 依赖 main.c，但是这种方法可能会导致 make 的重启，
当 make 很复杂的时候性能不如前文的方法。






Makefile中指示符“include”、“-include”和“sinclude”的区别

1 include 指定的文件不是以斜线开始(绝对路径，如/usr/src/Makefile...)，而且当前目录下也不存在此文件；
make将根据文件名试图在以下几个目录下查找：首先，查找使用命令行选项“-I”或者“--include-dir”指定的目录，如果找到指定的文件，
则使用这个文件；否则继续依此搜索以下几个目录(如果其存在)：“/usr/gnu/include”、“/usr/local/include”和“/usr/include”。

当在这些目录下都没有找到“include”指定的文件时，make将会提示一个包含文件未找到的告警提示，但是不会立刻退出。
而是继续处理Makefile的后续内容。当完成读取整个Makefile后，make将试图使用规则来创建通过指示符“include”指定的但未找到的文件，
当不能创建它时(没有创建这个文件的规则)，make将提示致命错误并退出。会输出类似如下错误提示：
Makefile:错误的行数：未找到文件名：提示信息(No such file or directory)
Make： *** No rule to make target ‘<filename>’. Stop

2 通常在Makefile中可使用“-include”来代替“include”，来忽略由于包含文件不存在或者无法创建时的错误提示
(“-”的意思是告诉make，忽略此操作的错误。make继续执行)。像下边那样：
-include FILENAMES...

使用这种方式时，当所要包含的文件不存在时不会有错误提示、make也不会退出；除此之外，和第一种方式效果相同。以下是这两种方式的比较：

使用“include FILENAMES...”，make程序处理时，
如果“FILENAMES”列表中的任何一个文件不能正常读取而且不存在一个创建此文件的规则时make程序将会提示错误并退出。

使用“-include FILENAMES...”的情况是，当所包含的文件不存在或者不存在一个规则去创建它，make程序会继续执行，
只有不能正确完成终极目标的重建时(某些必需的目标无法在当前已读取的makefile文件中找到正确的重建规则)，才会提示致命错误并退出。

3 也可以使用“sinclude”来代替“-include”(GNU所支持的方式)。为了和其它的make程序进行兼容。

