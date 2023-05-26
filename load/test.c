#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
// #include "testlib1.h"

int main()
{
    // printf(" __0__ \n");
    // printzzz("xxx");
    // printf(" __1__ \n");
    // // malloc(0);
    // printf(" __2__ \n");


    int i;

	srand(time(NULL));
	for(i=0;i<2;i++){
		printf("%d\n",rand()%100);
	}

    i = strcmp("333", "234");
    printf("i=%d\n",i);
    if(i == 0)
    {
        printf("equal\n");
    }
    else
    {
        printf("not equal\n");
    }

    return 0;
}
