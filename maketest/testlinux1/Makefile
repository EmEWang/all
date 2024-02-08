

obj=$(basename $(wildcard *.c))
CFLAGS+=-lrt -pthread -g
tmp=add.tmp mman.file
draw:CFLAGS+=-lm#-lm draw.c使用
sched:CFLAGS+=-D_GNU_SOURCE#gcc需要特殊宏 gcc不需要
.PHONEY:
all:${obj}

%:%.c
	gcc -o $@  $< ${CFLAGS}

clean:
	-rm -f  ${obj} ${tmp}
