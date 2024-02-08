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
obj=# 中间文件
out=testheap# 结果程序 x64
outarm=testheaparm# 结果程序 arm
googlepath=/home/lixiang/code/gperftools/build/# google连接目录 注意前面不能由空格 否则会引起shell分割错误
jemallocpath=/home/lixiang/code/jemalloc2/lib/# jemalloc
pprof=/home/lixiang/code/gperftools/src/pprof     # tcmalloc pprof程序
jeprof=/home/lixiang/code/jemalloc2/bin/jeprof     # jemalloc jeprof程序
ff=# pprof指定日志文件 基准
ff2=# pprof指定日志文件 对比
log=tcmalloc# 日志1
log2=jemalloc# 日志2
gccarm=aarch64-linux-gnu-g++

${out}:${file}
	g++ -o ${out} ${file}

# 默认编译     需要LD_PRELOAD加载库
all:
	g++ -o ${out} ${file}
# 连接tcmalloc库的方式编译
all2:
	g++ -o ${out} ${file}  -L${googlepath} -lprofiler -ltcmalloc
# 生成arm版本
arm:
	${gccarm} -o ${outarm} ${file}


# tcmalloc 测试  libtcmalloc_and_profiler.so 可替代 libtcmalloc.so 和 libprofiler.so
# 编译连接方式
test11:
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
# 设置log名
test12:
	HEAPPROFILE=${log} LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
# 设置分配多大空间 产生dump文件
test13:
	HEAPPROFILE=${log} HEAP_PROFILE_ALLOCATION_INTERVAL=1024 LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}
# 信号只能使用数字 使用kill -x pid
test14:
	HEAPPROFILE=${log} HEAPPROFILESIGNAL=12 LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${googlepath} ./${out}


# LD_PRELOAD方式
test21:
	LD_PRELOAD=${googlepath}libtcmalloc.so:${googlepath}libprofiler.so HEAPPROFILE=${log} ./${out}
# 设置使用多大空间 产生dump文件
test22:
	LD_PRELOAD=${googlepath}libtcmalloc_and_profiler.so HEAPPROFILE=${log} HEAP_PROFILE_INUSE_INTERVAL=1048576 ./${out}
# 使用信号 产生dump文件
test23:
	LD_PRELOAD=${googlepath}libtcmalloc_and_profiler.so HEAPPROFILE=server HEAPPROFILESIGNAL=12 ./${out}




# 使用jemaloc
# MALLOC_CONF 选项
# https://jemalloc.net/jemalloc.3.html#mallctl_namespace   TUNING -> MALLCTL NAMESPACE
# prof_leak(bool)    Leak reporting enabled/disabled 如生效 配合 prof_final 显示结果
# prof_final(bool)   如生效 程序退出时 显示结果
# lg_prof_sample(size_t)  分配多大内存产生样本  默认 19 即512KB(2^19 B) 17 128K  27 128M
# lg_prof_interval(ssize_t)  默认关闭 实际分配多少产生样本


testj1:
	MALLOC_CONF=prof:true,lg_prof_interval:17,prof_prefix:${log2} LD_PRELOAD=${jemallocpath}libjemalloc.so ./${out}
#	MALLOC_CONF=prof:true,lg_prof_interval:17,prof_prefix:jeprof.app LD_PRELOAD=${jemallocpath}libjemalloc.so ./${out}
#	MALLOC_CONF=prof:true,lg_prof_sample:17,prof_prefix:jeprof.app LD_PRELOAD=${jemallocpath}libjemalloc.so ./${out}
#	MALLOC_CONF=prof:true,lg_prof_sample:17,prof_accum:true,lg_prof_interval:20 LD_PRELOAD=${jemallocpath}libjemalloc.so ./${out}
testj2:
	MALLOC_CONF=prof_leak:true,lg_prof_sample:0,prof_final:true LD_PRELOAD=${jemallocpath}libjemalloc.so ./${out}
#	MALLOC_CONF=prof_leak:true,lg_prof_sample:0,prof_final:true LD_PRELOAD=${jemallocpath}libjemalloc.so ./a.out
#	MALLOC_CONF="oversize_threshold:1,background_thread:true,metadata_thp:auto,dirty_decay_ms:9000000000,muzzy_decay_ms:9000000000";



# tcmalloc 分析结果
pprof:
#	echo ${ff}
	${pprof} --text ${out} ${ff}
# 基于ff 分析 ff2 与 ff 比较
pprof2:
	${pprof} --text ${out} --base=${ff} ${ff2}

# 图形化结果
pprofpdf:
	${pprof} --pdf ${out} ${ff} > heap.pdf
#	${pprof} --pdf ${out} --base=${ff} ${ff2} > record1.pdf
pprofgv:
	${pprof} --gv ${out} ${ff}
pprofsvg:
	${pprof} --svg ${out} ${ff} > ${ff}.tc.svg
pprofgif:
	${pprof} --gif ${out} ${ff} > ${ff}.tc.gif



# jemaloc 分析结果
jprof:
	${jeprof} --text ${out} ${ff}
#	${jeprof} --svg ${out} ${ff} > ${ff}.svg
#	${jeprof} --pdf ${out} ${ff} > ${out}.pdf
jprofgif:
	${jeprof} --gif ${out} ${ff} > ${ff}.je.gif
jprofsvg:
	${jeprof} --svg ${out} ${ff} > ${ff}.je.svg
jprofpdf:
	${jeprof} --pdf ${out} ${ff} > ${ff}.je.pdf
jprof2:
	${jeprof} --text ${out} --base=${ff} ${ff2}

clean:
	rm -f ${obj} ${out}  *.pdf *.png *.gif *.svg *.heap

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
	dot -Tsvg 11.dot -o 11.svg
	dot 12.dot -T png -o 12.png



# generate.sh 使用方法
# ./generate.sh ./jeprof /app/ad3/bin/datarec_container     /data/outpp0/jeprof.datarec.out    ./out0
# ./generate.sh ./jeprof /app/ad3/bin/lidar_container       /data/outpp0/jeprof.lidar.out      ./out0
# ./generate.sh ./jeprof /app/ad3/bin/prediction_container  /data/outpp0/jeprof.prediction.out ./out0


# ./generate.sh ./jeprof /app/ad3/bin/datarec_container     /data/outpp1/jeprof.datarec.out    ./out1
# ./generate.sh ./jeprof /app/ad3/bin/lidar_container       /data/outpp1/jeprof.lidar.out      ./out1
# ./generate.sh ./jeprof /app/ad3/bin/prediction_container  /data/outpp1/jeprof.prediction.out ./out1


# ./generate.sh ./jeprof /app/ad3/bin/datarec_container     /data/outpp2/jeprof.datarec.out    ./out2
# ./generate.sh ./jeprof /app/ad3/bin/lidar_container       /data/outpp2/jeprof.lidar.out      ./out2
# ./generate.sh ./jeprof /app/ad3/bin/prediction_container  /data/outpp2/jeprof.prediction.out ./out2

# ./generate.sh ./jeprof /app/ad3/bin/datarec_container     /data/outpp3/jeprof.datarec.out    ./out3
# ./generate.sh ./jeprof /app/ad3/bin/lidar_container       /data/outpp3/jeprof.lidar.out      ./out3
# ./generate.sh ./jeprof /app/ad3/bin/prediction_container  /data/outpp3/jeprof.prediction.out ./out3
