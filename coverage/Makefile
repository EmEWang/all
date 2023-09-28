# 代码覆盖率 测试
source1=coverage.c
target1=tar1
output1=out1
# 1 clang + llvm-cov
all:
	clang -o $(target1) -fprofile-instr-generate -fcoverage-mapping $(source1)
	./$(target1) 5
data:
	llvm-profdata merge -o $(target1).profdata default.profraw
#	llvm-cov show ./$(target1) -instr-profile=$(target1).profdata
	llvm-cov show ./$(target1) -instr-profile=$(target1).profdata $(source1) -format=html -output-dir=$(output1)
clean:
	rm -rf $(output1) *.profdata default.profraw $(target1)

source2=coverage.c
target2=tar2
output2=out2
# 2 clang + lcov
all2:
	clang -o $(target2) -fprofile-instr-generate -fcoverage-mapping $(source2)
	./$(target2) 5
data2:
	llvm-profdata merge -sparse default.profraw -o $(target2).profdata
	lcov --capture --directory . --output-file app.info
	genhtml app.info --output-directory $(output2)
clean2:
	-rm -rf $(output2) default.profraw $(target2).profdata *.info $(target2)

source3=coverage.c
target3=tar3
output3=out3
# 3 clang + llvm-cov gcov
all3:
	clang -o $(target3) --coverage $(source3)  -Xclang -coverage-version='A94*'
	./$(target3) 5

data3:
	llvm-cov gcov coverage.
	lcov -c -o $(target3).info -d . -b . --rc lcov_branch_coverage=1
	genhtml $(target3).info --branch-coverage -o $(output3)
#	llvm-cov show ./$(target3) -instr-profile=coverage.c.gcov $(source3) -format=html -output-dir=$(output3)
#	genhtml app.info --output-directory $(output3)

clean3:
	-rm -rf $(target3) *.gcno *.gcda *.gcov $(output3)

# 11 g++ + lcov
source11=coverage.c
target11=tar11
output11=out11
all11:
	g++ -fprofile-arcs -ftest-coverage $(source11) -o $(target11)
	./$(target11) 5

data11:
# 生成 coverage.c.gcov 下一句可以不要
	gcov $(source11)
	lcov -c -o $(target11).info -d .
	genhtml $(target11).info -o $(output11)

clean11:
	-rm -rf $(output11) *.info *.gcov *.gcda *.gcno $(target11)


# 12 g++ + llvm-cov gcov
source12=coverage.c
target12=tar12
output12=out12
all12:
	g++ -fprofile-arcs -ftest-coverage $(source12) -o $(target12)
	./$(target12) 5

data12:
	llvm-cov gcov $(source12)
# 	llvm-profdata merge -o loop-cov.profdata default.profraw
# #	llvm-cov show ./loop-cov -instr-profile=loop-cov.profdata loop-cov.profdata
	llvm-cov show ./$(target12) -instr-profile=loop-cov.profdata coverage.c -format=html -output-dir=$(output12)

clean12:
	-rm -rf $(output12) *.info *.gcov *.gcda *.gcno $(target12)



# 101 clang + llvm-cov  多目录
#选项-fprofile-instr-generate -fcoverage-mapping是为了对源码进行插桩编译，
#   这样执行程序后，才会产生Code Coverage文件
# ./(target101) 3;执行完毕后会生成default.profraw
# llvm-profdata merge -o (target101).profdata default.profraw     Index the raw profile file
# llvm-cov show 生成报告  若没有-format=html -output-dir=$(output101) 则只打印输出不生成html
# llvm-cov show ./(target101) -instr-profile=(target101).profdata coverage.c -format=html -output-dir=$(output101)

#source101=main.cpp module1/src/module1_1.cpp module1/src/module1_2.cpp module2/src/module2_1.cpp
source101=$(wildcard *.cpp module1/src/*.cpp module2/src/*.cpp)
target101=tar101
output101=out101
all101:
#  -mllvm -runtime-counter-relocation
#	clang -o $(target101) -fprofile-instr-generate -fcoverage-mapping $(source101)
	clang++ -o $(target101) -fprofile-instr-generate -fcoverage-mapping $(source101)
#	LLVM_PROFILE_FILE="XX%p-%h-.profdata" ./$(target101) 3
	./$(target101) 3
data101:
# 运行默认产生 default.profraw 文件 当前目录
# LLVM_PROFILE_FILE 环境变量 改变 生成的 .profraw 文件 若带路径 同时也会生成路径 如果不存在的话
# %p 扩展为进程ID
# %h 扩展为hostname
# %t 扩展为 TMPDIR 环境变量
# 可由  llvm-profdata merge 工具 更改格式成 profile
# --sparse  Generate a sparse profile (only meaningful for -instr)
# 能显著的缩小文件 但是若打算重复使用线索化的文件 则不能打开此选项
# llvm-profdata merge 能合并多个原始数据或已经线索化的数据或两种同时存在
# llvm-profdata merge -sparse foo1.profraw foo2.profdata -o foo3.profdata
	llvm-profdata merge -o $(target101).profdata  default.profraw
#	llvm-cov show ./loop-cov -instr-profile=loop-cov.profdata loop-cov.profdata
# llvm-cov show 需要 clang -fprofile-instr-generate -fcoverage-mapping 选项 生成的 profile
# llvm-cov show [options] -instr-profile PROFILE [BIN] [-object BIN]… [-sources] [SOURCE]…
#	llvm-cov show ./$(target101) -show-line-counts-or-regions --show-branches=count --show-expansions -instr-profile=$(target101).profdata -format=html -output-dir=$(output101)
# --show-branches=<value>                            - Show coverage for branch conditions
#     =count                                           -   Show True/False counts
#     =percent                                         -   Show True/False percent
#   --show-expansions                                  - Show expanded source regions
#   --show-instantiations                              - Show function instantiations
#   --show-line-counts                                 - Show the execution counts for each line
#   --show-line-counts-or-regions                      - Show the execution counts for each line, or the execution counts for each region on lines that have multiple regions
#   --show-regions                                     - Show the execution counts for each region

# --region-coverage-lt=2 区域 功能 过滤
# --region-coverage-gt=2
# --line-coverage-lt=100   函数 功能 过滤
# --line-coverage-gt=x
# --coverage-watermark=90,50 水印 格式 high,low  >=high 绿 <low 红  其他黄
# --format html text lcov
# --dump 打印 内部信息
# -format=XXX  html 格式 text 格式 lcov(llvm-cov export 命定导出)
# --show-instantiation-summary 实例化统计
# --show-region-summary 区域统计
# --show-branch-summary 分支统计
	llvm-cov show ./$(target101) \
		--coverage-watermark=60,50 \
		--show-line-counts-or-regions  \
		--show-branches=count  \
		-instr-profile=$(target101).profdata -format=html -output-dir=$(output101)

# report 命令 generate a file-level summary of coverage statistics instead of a line-oriented report
# html(不支持) text(支持) lcov 使用(llvm-cov export)
#	 llvm-cov report ./$(target101) -instr-profile=$(target101).profdata --format=text
# html(不支持) text(支持 json 格式) lcov(支持)
#	llvm-cov export ./$(target101) -instr-profile=$(target101).profdata --format=lcov

# 第二种方式生成html
data101_2:
	llvm-profdata merge -o loop-cov.profdata default.profraw
	lcov --capture --directory . --output-file app.info
	genhtml app.info --output-directory out

clean101:
	$(info source101: $(source101))
	rm -rf $(output101) *.profdata default.profraw $(target101)



# 102 clang + lcov  多目录
#source102=main.cpp module1/src/module1_1.cpp module1/src/module1_2.cpp module2/src/module2_1.cpp
source102=$(wildcard *.cpp module1/src/*.cpp module2/src/*.cpp)
target102=tar102
output102=out102
all102:
# 编译选项为 -fprofile-arcs -ftest-coverage (== --coverage)
# 编译 产生 .gcno 对应每个目标文件 包含一半覆盖率信息
# 运行 产生 .gcda 对应每个目标文件 包含另一半覆盖率信息 运行 则数据做相应的叠加
# 默认 .gcda 跟目标文件同一目录
# 环境变量 GCOV_PREFIX GCOV_PREFIX_STRIP 控制生成的.gcda的位置
# GCOV_PREFIX_STRIP去掉原代码路径中的前几级，比如源代码路径为/a/b/c/d.cpp，
#   如果GCOV_PREFIX_STRIP=2 则实际使用的路径是c/d.cpp
# 如果GCOV_PREFIX=/run/gcov，则.gcda实际存放的路径是/run/gcov/c/d.gcda
# export GCOV_PREFIX=/home/dce/work/test/
# export GCOV_PREFIX_STRIP=5
# 运行 llvm-cov gcov for each main source file where you want to examine the coverage results
# 同在运行编译的目录下 结果 产生 .gcov 文件 主文件包含的文件都产生各自的 .gcov 文件
# .gcov 文件格式为 源文件拷贝+行号+执行次数 没有可执行代码的行用 - 表示 代码没有执行的行 用 #### 表示
# gcov-dump coverage.gcda    od -t x4 -w16 coverage.gcda
# gcov-dump coverage.gcno    od -t x4 -w16 coverage.gcno
# .gcno/.gcda均由一串uint32组成，文件格式参见gcc/gcov-io.h

# clang --coverage -c a.c b.c 生成a.gcno和b.gcno，instrument(记录边执行次数)
# clang --coverage a.o b.o 链接libclang_rt.profile-$arch.a (实现在compiler-rt)
# ./a.out 程序退出时输出a.gcda和b.gcda
# 让Clang和libclang_rt.profile-支持GCC 4.7~9所有instrument改动。可以用-Xclang -coverage-version='409*'
#  生成GCC 4.9兼容的.gcno/.gcda；A93*则是GCC 9.3，A94*则是GCC 9.4 B01*则是GCC 10.1
	clang -o $(target102) --coverage $(source102) -Xclang -coverage-version='A94*'
	./$(target102) 3
data102:
#	llvm-cov gcov  *.gcno
#	llvm-cov gcov  *.gcda  或者 源文件
#	lcov -c --gcov-tool $PWD/llvm-gcov -d . -o output.lcov
# -b 源文件目录 否则 源文件用 / 开始找
	lcov -c -o $(target102).info -d . -b . --rc lcov_branch_coverage=1
	genhtml $(target102).info --branch-coverage -o $(output102)
#	genhtml output.lcov -o out
#	llvm-cov show ./loop-cov -instr-profile=loop-cov.profdata loop-cov.profdata
#	llvm-cov show ./$(target102) -instr-profile=$(target102).profdata -format=html -output-dir=$(output102)

clean102:
	$(info source102: $(source102))
	-rm -rf $(output102) *.info *.gcda *.gcno *.gcov *.s $(target102) output.lcov



# 103 g++ + gcov  多目录
#source103=main.cpp module1/src/module1_1.cpp module1/src/module1_2.cpp module2/src/module2_1.cpp
source103=$(wildcard *.cpp module1/src/*.cpp module2/src/*.cpp)
# source103+=$(wildcard *.h module1/inc/*.h module2/inc/*.h)
target103=tar103
output103=out103
all103:
# 在运行gcc的目录 生成 *.gcno 文件 instrument(记录边执行次数)并链接libgcov.a
# -ftest-profile: 输出notes file (.gcno)，描述GCC版本、函数基本信息(名称、起始行列号、结束行列号(GCC 8添加)、
#   校验码(源文件更新后可以判断.gcno/.gcda是否过期))、基本块 (flags (是否树边、是否异常控制流添加的)、包含的行)
# -fprofile-arcs: instrument程序，程序执行后更新data files (.gcda)，描述程序执行次数和边执行次数
# .gcno/.gcda均由一串uint32组成，文件格式参见gcc/gcov-io.h
# 简单说来，-ftest-profile描述控制流图 而-fprofile-arcsinstrument程序。
# -fprofile-arcs亦可用作链接选项，链接libgcov.{a,so}。
# 通常-ftest-profile -fprofile-arcs同时指定，可以简写为--coverage。
	g++ --coverage -o $(target103) $(source103)
# 产生汇编文件 .s 文件 和 .gcno 文件  \./
#	g++ --coverage -S $(source103)
# 运行 生成 *.gcda 文件
	./$(target103) 3
data103:
# gcov常用的命令行选项：
# -i: GCC 4.9~8生成一个近似lcov的intermediate format。GCC 9之后生成.json.gz(有点讨厌的上游改动～)。
#   如果只是想单纯看行执行次数，从JSON提取信息比提取intermediate format麻烦多了
# -r: 只输出编译时(源文件使用相对路径名)的.gcno/.gcda的信息。可跳过系统头文件
# -s prefix: 若源文件路径名前缀为prefix，去除后变为相对路径，可使-r生效
# -t: 输出到stdout，而非.gcov文件
# -b 分支覆盖 -f 函数覆盖
# 举例 \./            其中.gcov文件可以文本显示 每运行一次程序 其标头和行运行次数都将叠加 #####表示未运行的行
#	gcov main.       #输出 main.cpp.gcov 文件 需要相应的 .gcno 文件 若有 .gcda 文件 则将数据叠加上
#	gcov -t *        #看所有的文件
#	gcov -t main.    #只看某一个文件

# gcov有个经典前端lcov，原先为Linux kernel设计。lcov设计的一套中间格式应用非常广泛
# Lcov(1.10及往后)默认关闭分支覆盖率的。打开需要在参数中加入 --rc lcov_branch_coverage=1
#   或者 设置/etc/lcovrc文件中的lcov_branch_coverage = 1
# lcov -b <测试代码路径> -d <gcda目录位置> -c -o result.info --rc lcov_branch_coverage=1
# -b为指定原代码路径，即生成gcno数据时编译的代码路径
# -c: lcov 的一个操作，表示要去捕获覆盖率数据
# -o: 输出文件
# -d: .gcno .gcda 所在的文件夹，注意这里有个“.”，是从当前文件夹中获取数据的
# lcov 可以在指定目录去找代码覆盖的信息, 输出为 *.info, 这个 *.info 是一个中间结果
	lcov -c -o $(target103).info -d . --rc lcov_branch_coverage=1
# 不同次代码覆盖率统计合并 -a参数合并.info文件 使用all.info执行genhtml生成最终的代码覆盖率
#	lcov -a a.info -a b.info -o all.info
# 移除指定目录 屏蔽 '/src/include/*' '/user/bin/*' 两个目录的覆盖率信息
#	lcov --remove all.info '/src/include/*' '/user/bin/*' -o result.info
# 只要固定目录 命令表示生成的覆盖率信息只要src和lib目录下文件的覆盖率信息
#	lcov  --extract all.info '*/src/*' '*/lib/*' -o result.info



# 倒成 html 文件 -o dir
#  默认关闭分支覆盖率的 打开需要在参数中加入 --branch-coverage
	genhtml $(target103).info --branch-coverage -o $(output103)
# 合并两个用例产生的info文件，输出同一个模块不同用例的总的统计数据
#	genhtml -o 333 helloworld1.info helloworld2.info

# 第二种方式生成html
data103_2:
	llvm-profdata merge -o loop-cov.profdata default.profraw
	lcov --capture --directory . --output-file app.info
	genhtml app.info --output-directory out

clean103:
	$(info source103: $(source103))
	rm -rf $(output103) *.info *.gcda *.gcno *.gcov *.s $(target103)


# FAQ
# 问题1
# ERROR: could not read source file /home/user/project/sub-dir1/subdir2/subdir1/subdir2/file.c
# 解决方法
# 在home目录下创建一个~/.lcovrc文件,并加入一行geninfo_auto_base = 1
# 出现此问题的原因是: 当编译工具链和源码不在同一个目录下时,会出现ERROR: could not read source file错误,
#   这个geninfo_auto_base = 1选项指定geninfo需要自动确定基础目录来收集代码覆盖率数据.
# 问题2
# 使用lcov [srcfile]的命令生成.info文件的时候，提示如下错误, 无法生成info文件：
# xxxxxxxxxxxx.gcno:version '402*', prefer '408*'
# Segmentation fault
# 解决方法
# 在lcov工具中使用–gcov-tool选项选择需要的gcov版本,如lcov --gcov-tool /usr/bin/gcov-4.2






# 代码覆盖率 测试
source_z1=coverage.c
source_z2=coverage2.c
target_z1=tar1
target_z2=tar2
target_out1=1
target_out2=2
output_z1=out1
output_z2=out2
output_z=out
out_z=out

# 1 clang + llvm-cov
# 多目标生成覆盖率
zzz:
	-mkdir $(target_out1)
	-mkdir $(target_out2)
	-mkdir $(output_z)
	clang -o $(target_out1)/$(target_z1) -fprofile-instr-generate -fcoverage-mapping $(source_z1)
	clang -o $(target_out2)/$(target_z2) -fprofile-instr-generate -fcoverage-mapping $(source_z2)
	cd $(target_out1) ; ./$(target_z1) 2
	cd $(target_out2) ; ./$(target_z2) 13
#data_z:
	llvm-profdata merge -o $(out_z).profdata $(target_out1)/default.profraw $(target_out2)/default.profraw default.profraw
#	llvm-cov show ./$(target1) -instr-profile=$(target1).profdata
#	llvm-cov show  -object ./$(target_out2)/$(target_z2) -object ./$(target_out1)/$(target_z1) -instr-profile=$(out_z).profdata -sources $(source_z1) -sources $(source_z2) -format=html -output-dir=$(output_z)
#	-sources 可省略
#	llvm-cov show  -instr-profile=$(out_z).profdata \
#	-object ./$(target_out1)/$(target_z1) -sources $(source_z1) \
#	-object ./$(target_out2)/$(target_z2) -sources $(source_z2) \
#	-object ./$(target101) -sources $(source101) \
#	-format=html -output-dir=$(output_z)

#	llvm-profdata merge -o $(out_z).profdata $(target_out1)/default.profraw $(target_out2)/default.profraw
#	llvm-cov show  -instr-profile=$(out_z).profdata \
#	-object ./$(target_out1)/$(target_z1) \
#	-object ./$(target_out2)/$(target_z2)  \
#	-object ./$(target101) \
#	-format=html -output-dir=$(output_z)

# -sources files 表示显示指定文件的覆盖率 若没有则显示默认的 注意 此选项 全局有效 不只是针对某一个目标
# 若一个-object中 制定了文件1 -sources file1 另-object中没有指定-sources选项 则 只显示 file1的覆盖率
	llvm-cov show  -instr-profile=$(out_z).profdata \
	-object ./$(target_out1)/$(target_z1) -sources coverage.c \
	-object ./$(target_out2)/$(target_z2)  \
	-object ./$(target101) -sources module1/inc/module1_1.h module2/inc/module2_1.h module2/src/module2_1.cpp \
	-format=html -output-dir=$(output_z)

cleanzzz:
	rm -rf $(output_z) *.profdata default.profraw $(target_out1) $(target_out2)


