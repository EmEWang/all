
target_normal=out_normal
target_tcmalloc=out_tcmalloc
target_mimalloc=out_mimalloc

dir_tcmalloc=/home/lixiang/code/gperftools/build
dir_tcmalloc2=/home/lixiang/code/gperftools/build2
dir_mimalloc=/home/lixiang/code/mimalloc/build

.PHONEY:
all:
	g++ -o2 -g -pthread hello_world.cc -o ${target_normal} &&/usr/bin/time -v ./${target_normal}

all2:
	g++ hello_world.cc -DTCMALLOC123 -g -pthread -L${dir_tcmalloc} -ltcmalloc -o ${target_tcmalloc} && LD_PRELOAD=${dir_tcmalloc}/libtcmalloc.so time ./${target_tcmalloc}

all21:
	g++ hello_world.cc -DTCMALLOC123 -g -pthread -L${dir_tcmalloc} -ltcmalloc -o ${target_tcmalloc} && /usr/bin/time -v ./${target_tcmalloc}
all22:
	g++ hello_world.cc -DTCMALLOC123 -o2 -g -pthread -L${dir_tcmalloc2} -ltcmalloc -o ${target_tcmalloc} && LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc}
all3:
	g++ hello_world.cc -DMIMALLOC123 -g -pthread -L${dir_mimalloc} -lmimalloc -o ${target_mimalloc} && LD_PRELOAD=${dir_mimalloc}/libmimalloc.so time ./${target_mimalloc}

all222:
	g++ hello_world.cc -g -pthread -ldl -L/home/lixiang/code/gperftools/build -ltcmalloc
	LD_PRELOAD=/home/lixiang/code/gperftools/build/libtcmalloc.so ./a.out

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
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
testtct1:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 1 malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
testtct16:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} thread 16 malloc mallocsize 222222 count 10000 count2 1000 ; sleep 3
testtc2:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector newsize 222222 count 10000 count2 1000 ; sleep 3
testtc2_t1:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testtc2_t16:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} vector thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3

testtc3:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list newsize 222222 count 10000 count2 1000 ; sleep 3
testtc3_t1:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testtc3_t16:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} list thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3

testtc4:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map newsize 222222 count 10000 count2 1000 ; sleep 3
testtc4_t1:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 1 newsize 222222 count 10000 count2 1000 ; sleep 3
testtc4_t16:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 22 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 2222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 22222 count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} map thread 16 newsize 222222 count 10000 count2 1000 ; sleep 3

testtc2_s:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple thread 1 vector count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple vector count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple thread 16 vector count 10000 count2 1000 ; sleep 3
testtc3_s:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple thread 1 list count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple list count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple thread 16 list count 10000 count2 1000 ; sleep 3
testtc4_s:
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple thread 1 map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple map count 10000 count2 1000 ; sleep 3
	LD_PRELOAD=${dir_tcmalloc2}/libtcmalloc.so /usr/bin/time -v ./${target_tcmalloc} simple map thread 16 count 10000 count2 1000 ; sleep 3

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
