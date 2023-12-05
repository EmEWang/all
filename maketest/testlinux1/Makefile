

obj=$(basename $(wildcard *.c))
CFLAGS+=-lrt -pthread -g #-lm draw.c使用
tmp=add.tmp mman.file
draw:CFLAGS+=-lm
.PHONEY:
all:${obj}

%:%.c
	gcc -o $@  $< ${CFLAGS}

clean:
	-rm -f  ${obj} ${tmp}
