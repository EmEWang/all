
srcfile=hello_world.cc

target_normal=out_normal
target_normal_aarch=out_normal_aarch
target_tcmalloc=out_tcmalloc
target_tcmalloc_aarch=out_tcmalloc_aarch
target_mimalloc=out_mimalloc

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

page=8
cache=16777216
#dir_tcmalloc=./
#dir_tcmalloc_page=./tcmalloc/tcmalloc_page${page}
dir_tcmalloc_page=/home/lixiang/code/gperftools/out_x64_O2_page${page}
#dir_mimalloc=./
#dir_jemalloc=./

#tcso=libtcmalloc.so
tcso_mini=libtcmalloc_minimal.so.4.5.10
# tcso_mini=libtcmalloc.so.4.5.10
#jeso=libjemalloc.so
#miso=libmimalloc.so

tcso=libtcmalloc.so
jeso=libjemalloc.so
miso=libmimalloc.so
GGG=aarch64-linux-gnu-g++

${target_normal}:${srcfile}
	g++ -o2 -g -pthread ${srcfile} -o ${target_normal}

.PHONEY:
all:
	g++ -o2 -g -pthread ${srcfile} -o ${target_normal} &&/usr/bin/time -v ./${target_normal}
all_tc:
	g++ ${srcfile} -DTCMALLOC123 -g -pthread -L${dir_tcmalloc} -ltcmalloc -o ${target_tcmalloc} && LD_PRELOAD=${dir_tcmalloc}/${tcso} time ./${target_tcmalloc}

aarch:
	${GGG} ${srcfile} -o2 -g -pthread -o ${target_normal_aarch}
aarch_tc:
	${GGG} ${srcfile} -DTCMALLOC123 -o2 -g -pthread -L${dir_tcmalloc_aarch} -ltcmalloc -o ${target_tcmalloc_aarch}

all_pmr:
	g++ -O2 -pthread -std=c++17 hello.cpp -o pmrtest
	LD_PRELOAD=/home/lixiang/code/gperftools/out_x64_O2_page8/libtcmalloc.so time ./pmrtest sys; sleep 1
	time ./pmrtest sys; sleep 1
	time ./pmrtest pmr; sleep 1
#	time ./pmrtest sys

pmrtest:
	time LD_PRELOAD=/home/lixiang/code/gperftools/out_x64_O2_page8/libtcmalloc.so ./pmrtest sys; sleep 1
	time ./pmrtest sys; sleep 1
	time ./pmrtest pmr; sleep 1

all_leak:
	g++ -std=c++0x -g -o mem_leak hello_leak.cpp -L/home/lixiang/code/gperftools/out_x64_O2 -ltcmalloc

leak_test:
#	LD_PRELOAD=${dir_tcmalloc_o2}/${tcso} HEAPPROFILE=./pf123 HEAPCHECK=normal ./mem_leak
	LD_PRELOAD=${dir_tcmalloc_o2}/${tcso} ./mem_leak

leak:all_leak leak_test


all_tc1:
	g++ ${srcfile} -DTCMALLOC123 -g -pthread -L${dir_tcmalloc} -ltcmalloc -o ${target_tcmalloc} && /usr/bin/time -v ./${target_tcmalloc}
all_tc2:
	g++ ${srcfile} -DTCMALLOC123 -o2 -g -pthread -L${dir_tcmalloc2} -ltcmalloc -o ${target_tcmalloc} && LD_PRELOAD=${dir_tcmalloc2}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 222 count 10000 count2 1000
all_tc3:
	g++ ${srcfile} -DTCMALLOC123 -o2 -g -pthread -L${dir_tcmalloc3} -ltcmalloc -o ${target_tcmalloc} && LD_PRELOAD=${dir_tcmalloc3}/${tcso} /usr/bin/time -v ./${target_tcmalloc} map newsize 222 count 10000 count2 1000
all_mi:
	g++ ${srcfile} -DMIMALLOC123 -g -pthread -L${dir_mimalloc} -lmimalloc -o ${target_mimalloc} && LD_PRELOAD=${dir_mimalloc}/libmimalloc.so time ./${target_mimalloc}

all2:
	g++ ${srcfile} -g -pthread -ldl -L/home/lixiang/code/gperftools/build -ltcmalloc
	LD_PRELOAD=/home/lixiang/code/gperftools/build/${tcso} ./a.out

test_:
#	/usr/bin/time -v ./${target_normal} malloc mallocsize 25 newsize 25 vector map count 10000 count2 1000 thread 16
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector list map count 10000 count2 1000 thread 16


test_tc_page_cache:
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3"

test_tc_page:
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} ./${target_normal} thread 5 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} ./${target_normal} thread 5 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} ./${target_normal} thread 5 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} ./${target_normal} thread 5 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} ./${target_normal} thread 5 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} ./${target_normal} thread 5 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} ./${target_normal} thread 5 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3"

test_tc_page_cache2:
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3"
	/bin/bash -c "time LD_PRELOAD=${dir_tcmalloc_page}/${tcso_mini} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=${cache} ./${target_normal} thread 5 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3"



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

test_tc:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10 newsize 10 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102 newsize 102 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024 newsize 1024 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 102400 newsize 102400 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 1024000 newsize 1024000 vector map count 10000 count2 100 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} thread 16 malloc mallocsize 10240000 newsize 10240000 vector map count 10000 count2 100 ; sleep 3


test_o2_4:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_4}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_o2_8:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_o2_16:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_16}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_o2_32:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_32}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_o2_64:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_64}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_o2_128:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_128}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3
test_o2_256:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 32 newsize 32 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 322 newsize 322 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_256}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100 ; sleep 3

test_o2_8_TMTTCB2:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=8388608   /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=16777216  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=33554432  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=83886080  /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3
	LD_PRELOAD=${dir_tcmalloc_o2_8}/${tcso} TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=167772160 /usr/bin/time -v ./${target_normal} malloc mallocsize 10240 newsize 10240 vector map count 10000 count2 1000 thread 16; sleep 3


test_o2_8_TMTTCB:${target_normal}
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



test_o3:${target_normal}
	LD_PRELOAD=${dir_tcmalloc_o3}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1023 newsize 1023 vector map count 10000 count2 1000
	LD_PRELOAD=${dir_tcmalloc_o3}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 102401 newsize 102401 vector map count 10000 count2 1000
	LD_PRELOAD=${dir_tcmalloc_o3}/${tcso} /usr/bin/time -v ./${target_normal} malloc mallocsize 1048577 newsize 1048577 vector map count 10000 count2 100



testsys:
	/usr/bin/time -v ./${target_normal} malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
testsys_t1:
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 1 mallocsize 222222 count 10000 count2 1000 ; sleep 3
testsys_t16:
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} malloc thread 16 mallocsize 222222 count 10000 count2 1000 ; sleep 3
testsys2:
	/usr/bin/time -v ./${target_normal} vector newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector newsize 222222 count 10000 count2 1000 ; sleep 3
testsys2_t1:
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testsys2_t16:
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} vector thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3
testsys3:
	/usr/bin/time -v ./${target_normal} list newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list newsize 222222 count 10000 count2 1000 ; sleep 3
testsys3_t1:
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testsys3_t16:
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} list thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3
testsys4:
	/usr/bin/time -v ./${target_normal} map newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map newsize 222222 count 10000 count2 1000 ; sleep 3
testsys4_t1:
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testsys4_t16:
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} map thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3
testsys2_s:
	/usr/bin/time -v ./${target_normal} simple thread 1 vector count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple vector count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple thread 16 vector count 10000 count2 1000 ; sleep 3
testsys3_s:
	/usr/bin/time -v ./${target_normal} simple thread 1 list count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple list count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple thread 16 list count 10000 count2 1000 ; sleep 3
testsys4_s:
	/usr/bin/time -v ./${target_normal} simple thread 1 map count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple map count 10000 count2 1000 ; sleep 3
	/usr/bin/time -v ./${target_normal} simple thread 16 map count 10000 count2 1000 ; sleep 3

testsys_s:testsys2_s testsys3_s testsys4_s

testsysall: testsys testsys2 testsys3 testsys4

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

mi:
	LD_PRELOAD=/home/lixiang/code/mimalloc/build/libmimalloc.so time ./a.out
clean:
	rm ${target_normal} ${target_tcmalloc} ${target_mimalloc} ./a.out

.PHONEY:
perf1:
	sudo perf script -i perf.data &> perf.unfold
#	~/code/FlameGraph/stackcollapse-perf.pl perf.unfold &> perf.folded
#	~/code/FlameGraph/flamegraph.pl perf.folded > perf.svg

.PHONEY:
perf2:
#	$$ 表示$
	sudo perf record -F 10000 -p ` ps -ef | grep out_ | awk 'NR==3 {print $$2}' `   -g -- sleep 10
	sudo perf script -i perf.data > perf.unfold 2>&1
	~/code/FlameGraph/stackcollapse-perf.pl perf.unfold > perf.folded  2>&1
	~/code/FlameGraph/flamegraph.pl perf.folded > perf.svg
test:
	echo 1234 &> 123.txt
#	` echo 1234 &> 123.txt `
#	$(shell echo 1234 &> 123.txt)
perfclean:
	rm -rf ./perf*
