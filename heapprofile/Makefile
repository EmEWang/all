# google heap profiler

# 功能
# 1 计算任意时间点的内存使用情况
# 2 定位内存泄露
# 3 位何处大量分配内存

# 使用
# 1 链接tcmalloc库 编译链接-ltcmalloc或LD_PRELOAD  必须使用tcmalloc来分配内存 否则无法使用heap profiler
# 2.1 分析整个程序
#   HEAPPROFILE=/tmp/mybin.hprof env1=xxx env2=yyy ./exe
# 2.2 分析特定代码
#   引用头文件 google/heap-profiler.h
#   用 HeapProfilerStart("转储文件") 和 HeapProfilerStop()把要分析的代码块包起来
#   调用HeapProfilerStop() 随便调用HeapProfilerDump() or GetHeapProfile()来检查分析情况
#   IsHeapProfilerRunning() 会告诉你是否已经调用过HeapProfilerStart
# 3 分析结果
#   pprof 脚本分析  --text 文本格式  --pdf pdf 文件 --gv 图形

# 环境变量
# HEAPPROFILE  开启内存统计设置命名转储的分析文件. 如 HEAPPROFILE=server ./server
#   生成的文件 server.0001.heap  server.0002.heap 等
# 默认统计规则是, 程序每分配 1 GB, 或每占用 100 MB, 统计一次. 可通过环境变量控制
# HEAP_PROFILE_ALLOCATION_INTERVAL  每分配多少字节的内存统计一次. 默认为 1073741824 (1 GB).
# HEAP_PROFILE_INUSE_INTERVAL  每占用多少字节的内存统计一次. 默认为 104857600 (100 MB).
# HEAP_PROFILE_TIME_INTERVAL   每隔多少秒统计一次. 默认为 0.
# HEAPPROFILESIGNAL            每当收到指定信号统计一次.

# 结果格式
# 第一列为以MB为单位的内存分配情况
# 第二列和第五列是第一列和第四列的百分比表示
# 第三列是第二列累加之和，如：第二行的第三列就是第一行的第二列+第二行的第二列
# 第四列代表所有的进程和它调用函数的内存之和
# ./pprof --text testheaparm --base=server.0001.heap server.0004.heap
# Using local file testheaparm.
# Using local file server.0004.heap.
# Total: 197.1 MB
#     65.7  33.3%  33.3%    197.1 100.0% main
#     65.7  33.3%  66.7%     65.7  33.3% test3
#     65.6  33.3% 100.0%     65.6  33.3% test4
#      0.0   0.0% 100.0%    197.1 100.0% __libc_start_main
#      0.0   0.0% 100.0%    197.1 100.0% _start



# Ubuntu 系统中安装 graphviz 和 dot
# sudo apt-get update               # 更新软件包列表
# sudo apt-get install graphviz     # 安装 graphviz   有说只需要这一步
# sudo apt-get install graphviz-dev # 安装 graphviz-dev
# sudo apt-get install dot          # 安装 dot
# which dot                         # 显示路径表示安装成功

# 删除
# sudo apt-get remove graphviz，安装 graphviz。
# sudo apt-get remove graphviz-dev，安装 graphviz-dev。
# sudo apt-get remove dot，安装 dot。



file=testheap.cpp# 源程序
obj=                  # 中间文件
out=testheap# 结果程序
outarm=testheaparm# 结果程序
googlepath=/home/lixiang/code/gperftools/build/# google连接目录 注意前面不能由空格 否则会引起shell分割错误
jemallocpath=/home/lixiang/code/jemalloc2/lib/# jemalloc
pprof=/home/lixiang/code/gperftools/src/pprof     # pprof程序
jeprof=/home/lixiang/code/jemalloc2/bin/jeprof     # jeprof程序
ff=server.0001.heap  # pprof指定日志文件 基准
ff2=server.0002.heap # pprof指定日志文件 对比
log=server# 日志1
log2=server2# 日志2
gccarm=aarch64-linux-gnu-g++


# 程序编译若不连接google库 则需要LD_PRELOAD加载

all:
	g++ -o ${out} ${file}

all2:
	g++ -o ${out} ${file}  -L${googlepath} -lprofiler -ltcmalloc

# 生成arm版本
arm:
	${gccarm} -o ${outarm} ${file}

test:
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
# 设置log名
test2:
	HEAPPROFILE=server LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
# LD_PRELOAD方式
test21:
	LD_PRELOAD=${googlepath}libtcmalloc.so:${googlepath}libprofiler.so HEAPPROFILE=${log} LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
# 设置分配大小记录
test3:
	HEAPPROFILE=${log} HEAP_PROFILE_ALLOCATION_INTERVAL=1024 LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
# 信号只能使用数字 使用kill -x pid
test4:
	HEAPPROFILE=${log} HEAPPROFILESIGNAL=12 LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
test5:
	LD_PRELOAD=${googlepath}libtcmalloc.so:${googlepath}libprofiler.so HEAPPROFILE=server HEAPPROFILESIGNAL=12 ./${out}

# 使用jemaloc
testj1:
	MALLOC_CONF=prof:true,lg_prof_interval:20 LD_PRELOAD=${jemallocpath}libjemalloc.so.2 ./${out}
testj2:
	MALLOC_CONF=prof_leak:true,lg_prof_sample:0,prof_final:true LD_PRELOAD=${jemallocpath}libjemalloc.so.2 ./${out}
#	MALLOC_CONF=prof_leak:true,lg_prof_sample:0,prof_final:true LD_PRELOAD=${jemallocpath}libjemalloc.so.2 ./a.out

pprof:
#	echo ${ff}
	${pprof} --text ${out} ${ff}
# 基于ff 分析 ff2 与 ff 比较
pprof2:
	${pprof} --text ${out} --base=${ff} ${ff2}

pprofpdf:
	${pprof} --pdf ${out} ${ff} > heap.pdf
#	${pprof} --pdf ${out} --base=${ff} ${ff2} > record1.pdf

# 图形化结果
pprofgv:
	${pprof} --gv ${out} ${ff}
pprofsvg:
	${pprof} --svg ${out} ${ff} > ${ff}.svg
pprofgif:
	${pprof} --gif ${out} ${ff} > ${ff}.gif

# 使用jemaloc
jprof:
	${jeprof} --text ${out} ${ff}
#	${jeprof} --pdf ${out} ${ff} > ${out}.pdf

clean:
	rm -f ${obj} ${out} ./*.00*.heap*  *.pdf *.png *.gif jeprof.*.*.heap

# -T表示输出类型，jpg、gif、svg等等，-o指定输出文件名，不指定则输出到标准输出上。
#dot 数据格式
# "box"[shape=box]                    方块
# "polygon"[shape=polygon,sides=7]    多边形
# "ellipse"[shape=ellipse]            椭圆
# "circle"[shape=circle]              圆
# "point"[shape=point]                点
# "triangle"[shape=triangle]          三角
# "invtriangle"[shape=invtriangle]    倒三角
# "plaintext"[shape=plaintext]        文字
# "diamond"[shape=diamond]            钻石
# label和bgcolor分别定义图片属性 标题和背景颜色
# graph 用来描述无向图，关系使用 --来描述，digraph用来描述有向图，关系使用 -> 来描述
# node用来定义节点的默认属性，edge用来定义边的默认属性。作用域从本次定义到下一次定义截住。特定节点/边设置的属性会覆盖默认值。
# excute的关系通过大括号的方式来对应两个节点
# []内属性，属性可以针对图、节点、边来设置。
# rank定义设置节点处在同一行，辅助渲染出来的图的效果
# www.graphviz.org   graphviz 官网地址
dot:
	dot -Tpng 11.dot -o 11.png
	dot 12.dot -T png -o 12.png

