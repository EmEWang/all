
# https://zhuanlan.zhihu.com/p/672082073
# https://github.com/dwangxxx/gperftools_flamegraph_profiler
# 通过 tcmalloc 的 cpu profile 导出火焰图

src=test.cpp
tar=test
path=/home/lixiang/code/gperftools/.libs#tcmalloc 路径
pathFlame=/home/lixiang/code#火焰图 路径


${tar}:${src}
	g++ test.cpp -g -o test

all:
#	g++ ${src} -o ${tar} -L${path} -lprofiler
	g++ ${src} -g -o ${tar}
	LD_PRELOAD=${path}/libprofiler.so CPUPROFILE=./profiler.prof ./${tar}
svg:
	python3 gperf2flamegraph.py test profiler.prof --svg ./profiler.svg --text ./profiler.txt --flame=${pathFlame}


.PHONEY:
perf1:
	sudo perf script -i perf.data &> perf.unfold
#	~/code/FlameGraph/stackcollapse-perf.pl perf.unfold &> perf.folded
#	~/code/FlameGraph/flamegraph.pl perf.folded > perf.svg


process=${tar}
.PHONEY:
perf2:
#	$$ 表示$
	sudo perf record -F 99 -p ` ps -ef | grep ${process} | awk 'NR==2 {print $$2}' ` --call-graph dwarf -- sleep 5
	sudo perf script -i perf.data > perf.unfold 2>&1
	${pathFlame}/FlameGraph/stackcollapse-perf.pl perf.unfold > perf.folded  2>&1
	${pathFlame}/FlameGraph/flamegraph.pl perf.folded > perf.svg
perf3:
	sudo perf record -F 99 -p ` ps -ef | grep ${process} | awk 'NR==2 {print $$2}' `   -g -- sleep 5
	sudo perf script | ${pathFlame}/FlameGraph/stackcollapse-perf.pl | ${pathFlame}/FlameGraph/flamegraph.pl > perf.sv
testp:
	echo 1234 &> 123.txt
#	` echo 1234 &> 123.txt `
#	$(shell echo 1234 &> 123.txt)

perfclean:
	rm -rf ./perf*

clean:
	@rm -rf ${tar} profiler.* __pycache__  ./perf*




# #!/bin/bash
# ./perf.sh PID Time name   （PID进程号，Time采样时间秒， name文件名例如interaction_container-2023-5-12-16-11-7min）
# exec() {
#   # echo "$1"
#    mkdir "$3"
#    cd "$3"
#    export LD_LIBRARY_PATH=../
#    sudo ../perf record -F 99 -p "$1" --call-graph dwarf sleep "$2" # 时间需要改
#    sudo ../perf script > out.unfold
#    sudo ../../FlameGraph/stackcollapse-perf.pl out.unfold > out.folded
#    sudo ../../FlameGraph/flamegraph.pl out.folded > "$3".svg
# }

# # parse_arg() {
# #     while [ $# -gt 0 ]; do
# #         case "$1" in
# #             -p|--pid)
# #                 shift 1
# #                 if [ -n "$1" ]; then
# #                     exec "$1"
# #                 fi
# #                 shift 1
# #                 ;;

# #             *)
# #                 shift 1
# #                 ;;

# #         esac
# #     done
# # }

# # parse_arg "$@" #perf.sh -p pid

# exec "$@" "$@" "$@" #perf.sh  pid time filename
