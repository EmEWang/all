
src=test.cc
src_pmr=pmr.cpp
src_leak=leak.cpp

target_normal=out_normal
target_normal_aarch=out_normal_aarch
target_tcmalloc=out_tcmalloc
target_tcmalloc_aarch=out_tcmalloc_aarch
target_mimalloc=out_mimalloc
tar_pmr=pmr
tar_leak=leak

dir_tcmalloc=/home/lixiang/code/gperftools/build
dir_tcmalloc2=/home/lixiang/code/gperftools/build2
dir_tcmalloc3=/home/lixiang/code/gperftools/build3
dir_tcmalloc_aarch=/home/lixiang/code/gperftools/.libs
dir_tcmalloc11=/home/lixiang/code/gperftools/.libs
dir_tcmalloc12=/home/lixiang/code/gperftools2/.libs
dir_tcmalloc13=/home/lixiang/code/gperftools3/.libs
dir_tcmalloc_o2=/home/lixiang/code/gperftools/out_x64_O2
dir_tcmalloc_o2_4=/home/lixiang/code/gperftools/out_x64_O2_page4
dir_tcmalloc_o2_8=/home/lixiang/code/gperftools/out_x64_O2_page8
dir_tcmalloc_o2_16=/home/lixiang/code/gperftools/out_x64_O2_page16
dir_tcmalloc_o2_32=/home/lixiang/code/gperftools/out_x64_O2_page32
dir_tcmalloc_o2_64=/home/lixiang/code/gperftools/out_x64_O2_page64
dir_tcmalloc_o2_128=/home/lixiang/code/gperftools/out_x64_O2_page128
dir_tcmalloc_o2_256=/home/lixiang/code/gperftools/out_x64_O2_page256
dir_tcmalloc_o3=/home/lixiang/code/gperftools/out_x64_O3
dir_mimalloc=/home/lixiang/code/mimalloc/build
dir_jemalloc=/home/lixiang/code/jemalloc/out_x64
dir_jemalloc_inc=/home/lixiang/code/jemalloc/include

page=8
cache=16777216
#dir_tcmalloc_page=./tcmalloc/tcmalloc_page${page}
dir_tcmalloc_page=/home/lixiang/code/gperftools/out_x64_O2_page${page}

#tcso=libtcmalloc_minimal.so.4.5.10
tcso=libtcmalloc.so
jeso=libjemalloc.so
miso=libmimalloc.so
garm=aarch64-linux-gnu-g++
flag=-o2 -g -pthread
flag2=-std=c++17

pprof=/home/lixiang/code/gperftools/src/pprof

${target_normal}:${src}
	g++ ${src} ${flag} -o ${target_normal}

.PHONEY:
all:
	g++ ${src} ${flag} -o ${target_normal}
	./${target_normal}
#	/usr/bin/time -v ./${target_normal}
#	/bin/bash -c "/usr/bin/time -v ./${target_normal}"
all_tc:
	g++ ${src} -DTC12 ${flag} -L${dir_tcmalloc} -ltcmalloc -o ${target_tcmalloc}
	LD_PRELOAD=${dir_tcmalloc}/${tcso} time ./${target_tcmalloc}

arm:
	${garm} ${src} ${flag} -o ${target_normal_aarch}
arm_tc:
	${garm} ${src} -DTC12 ${flag} -L${dir_tcmalloc_aarch} -ltcmalloc -o ${target_tcmalloc_aarch}

all_pmr:
	g++ ${flag} ${flag2} ${src_pmr} -o ${tar_pmr}
pmrtest:
	time LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} ./${tar_pmr} sys; sleep 1
	time ./${tar_pmr} sys; sleep 1
	time ./${tar_pmr} pmr; sleep 1
#	time ./pmrtest sys
pmr:all_pmr
	./${tar_pmr} 1



all_leak:
#	g++ ${src_leak} -std=c++0x ${flag} -L${dir_tcmalloc_o2_8} -ltcmalloc -o ${tar_leak}
	g++ ${src_leak} -std=c++0x ${flag} -o ${tar_leak}
leak_test:
#	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} HEAPPROFILE=./pf123 HEAPCHECK=normal ./${tar_leak}
leak:all_leak leak_test
	HEAPCHECK=normal LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} ./${tar_leak}
leak2:all_leak leak_test
	HEAPPROFILE=./${tar_leak} HEAPCHECK=normal LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} ./${tar_leak}
leakpprof:
# 1 编译时将-g换成-pg  /usr/bin/addr2line: DWARF error: could not find variable specification at offset 5fc4
# 2 安装graphviz      sh: dot: command not found
#	${pprof} ./${tar_leak} "./${tar_leak}.0001.heap" --inuse_objects --lines --heapcheck  --edgefraction=1e-10 --nodefraction=1e-10 --gv
	${pprof} ./${tar_leak} "./${tar_leak}.0001.heap" --inuse_objects --lines --heapcheck  --edgefraction=1e-10 --nodefraction=1e-10 --svg > ${tar_leak}.svg


# https://github.com/jemalloc/jemalloc/wiki/Use-Case:-Basic-Allocator-Statistics
ex=ex_stats_print
ex:
	gcc ${ex}.c -o ${ex} -I${dir_jemalloc_inc} -L${dir_jemalloc} -Wl,-rpath,${dir_jemalloc} -ljemalloc
	MALLOC_CONF="prof:true,lg_prof_sample:1,prof_accum:false,prof_prefix:jeprof.out" ./${ex}


all_tc1:
	g++ ${src} -DTC12 ${flag} -L${dir_tcmalloc} -ltcmalloc -o ${target_tcmalloc} && /usr/bin/time -v ./${target_tcmalloc}
all_tc2:
	g++ ${src} -DTC12 ${flag} -L${dir_tcmalloc2} -ltcmalloc -o ${target_tcmalloc} && LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 222 count 10000 count2 1000
all_tc3:
	g++ ${src} -DTC12 ${flag} -L${dir_tcmalloc3} -ltcmalloc -o ${target_tcmalloc} && LD_PRELOAD=${dir_tcmalloc3}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 222 count 10000 count2 1000
all_mi:
	g++ ${src} -DMI12 ${flag} -L${dir_mimalloc} -lmimalloc -o ${target_mimalloc} && LD_PRELOAD=${dir_mimalloc}/${miso} time ./${target_mimalloc}

all2:
	g++ ${src} ${flag} -ldl -L${dir_tcmalloc} -ltcmalloc
	LD_PRELOAD=${dir_tcmalloc}/${tcso} ./a.out

test_:
#	/usr/bin/time -v ./${target_normal} malloc mallocsize 25 newsize 25 vector map count 10000 count2 1000 thread 16
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector list map count 10000 count2 1000 thread 16

test_tc:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3

test_mi:${target_normal}
	LD_PRELOAD=${dir_mimalloc}/${miso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_mimalloc}/${miso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_mimalloc}/${miso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_mimalloc}/${miso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_mimalloc}/${miso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_mimalloc}/${miso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_mimalloc}/${miso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3

test_je:${target_normal}
	LD_PRELOAD=${dir_jemalloc}/${jeso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_jemalloc}/${jeso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_jemalloc}/${jeso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_jemalloc}/${jeso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_jemalloc}/${jeso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_jemalloc}/${jeso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_jemalloc}/${jeso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3

test_tc_page:
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} ./${target_normal} thread 5 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} ./${target_normal} thread 5 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} ./${target_normal} thread 5 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} ./${target_normal} thread 5 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} ./${target_normal} thread 5 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} ./${target_normal} thread 5 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} ./${target_normal} thread 5 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3"

test_tc_page_cache:
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3"

test_tc_o2_4:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_tc_o2_8:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_tc_o2_16:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_tc_o2_32:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_tc_o2_64:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_tc_o2_128:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_tc_o2_256:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3

test_tc_o2_8_TMTTCB:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3

	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3

	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3

	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3

	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3

	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3

test_tc_o2_8_TMTTCB_thread:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3

test_tc_o3:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o3}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000
	LD_PRELOAD=${dir_tcmalloc_o3}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000
	LD_PRELOAD=${dir_tcmalloc_o3}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100



test_sys:
	/usr/bin/time -v ./${target_normal} malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
test_sys_thread1:
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 222222 count 10000 count2 1000 ; sleep 3
test_sys_thread16:
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 222222 count 10000 count2 1000 ; sleep 3
test_sys2:
	/usr/bin/time -v ./${target_normal} vector newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys2_thread1:
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys2_thread16:
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys3:
	/usr/bin/time -v ./${target_normal} list newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys3_thread1:
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys3_thread16:
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys4:
	/usr/bin/time -v ./${target_normal} map newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys4_thread1:
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys4_thread16:
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3
test_sys2_s:
	/usr/bin/time -v ./${target_normal} simple thread 1 vector count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple vector count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple thread 16 vector count 10000 count2 1000 ; sleep 3
test_sys3_s:
	/usr/bin/time -v ./${target_normal} simple thread 1 list count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple list count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple thread 16 list count 10000 count2 1000 ; sleep 3
test_sys4_s:
	/usr/bin/time -v ./${target_normal} simple thread 1 map count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple map count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple thread 16 map count 10000 count2 1000 ; sleep 3

testsys_s:test_sys2_s test_sys3_s test_sys4_s

testsysall: test_sys test_sys2 test_sys3 test_sys4

testtc:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
testtct1:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
testtct16:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
testtc2:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector newsize 222222 count 10000 count2 1000 ; sleep 3
testtc2_t1:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testtc2_t16:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3

testtc3:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list newsize 222222 count 10000 count2 1000 ; sleep 3
testtc3_t1:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testtc3_t16:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3

testtc4:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 222222 count 10000 count2 1000 ; sleep 3
testtc4_t1:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testtc4_t16:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3

testtc2_s:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple thread 1 vector count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple vector count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple thread 16 vector count 10000 count2 1000 ; sleep 3
testtc3_s:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple thread 1 list count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple list count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple thread 16 list count 10000 count2 1000 ; sleep 3
testtc4_s:
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple thread 1 map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} simple map thread 16 count 10000 count2 1000 ; sleep 3

testtc_s:testtc2_s testtc3_s testtc4_s

testtcall:testtc testtc2 testtc3 testtc4


clean:
	rm -rf ${target_normal} ${target_tcmalloc} ${target_mimalloc} ${ex} ./a.out ${tar_leak} ${tar_leak}.svg ${tar_leak}.0001.heap ${tar_pmr} ./perf*