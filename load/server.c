#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <stdlib.h>
#include <dlfcn.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc >=2) {
        printf("=====argc>=2\n");
    }
    printf("helloworld begin\n");

    if (argc <2){
        printf("=====argc<2\n");
    }

    unsigned int i = 0;
    while(1){

        printf("this is the server body %u\n", i);
        sleep(3);
    }
    return 0;
}
