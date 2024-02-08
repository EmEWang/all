#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>

// $ time ./vdos  vsyscall

// real    0m0.359s
// user    0m0.105s
// sys     0m0.254s
// $ time ./vdos  vdso

// real    0m0.007s
// user    0m0.006s
// sys     0m0.001s
// $ time ./vdos vsyscall-native

// real    0m0.124s
// user    0m0.040s
// sys     0m0.084s


int main(int argc, char **argv)
{
        unsigned long i = 0;
        time_t (*f)(time_t *) = (time_t (*)(time_t *))0xffffffffff600400UL;

        if (!strcmp(argv[1], "vsyscall")) {
                for (i = 0; i < 1000000; ++i)
                        f(NULL);
        } else if (!strcmp(argv[1], "vdso")) {
                for (i = 0; i < 1000000;++i)
                        time(NULL);
        } else {
                for (i = 0; i < 1000000; ++i)
                        syscall(SYS_time, NULL);
        }

        return 0;
}