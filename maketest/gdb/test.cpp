

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int add(int a, int b);

int main(int argc, char** argv)
{
    printf("start!\n");
    printf("argc %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("argv %d %s\n", i, argv[i]);
    }

    int c = add(3, 5);
    int max = 1000;
    int i = 0;
    for (i = 0; i < max; i++)
    {
        printf("index %d\n", i);
        sleep(1);
    }



    printf("end!\n");
    return 0;
}

int add(int a, int b)
{
    int c = a + b;
    return c;
}