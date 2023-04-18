// coverage.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int loop = atoi(argv[1]);

    for(int idx = 0; idx < loop; idx++)
    {
        printf("%s line %d, %d\n", __func__, __LINE__, idx);
    }

    return 0;
}