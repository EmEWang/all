// coverage2.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("312\n");
    // int loop = atoi(argv[1]);

    // for(int idx = 0; idx < loop; idx++)
    // {
    //     printf("%s line %d, %d\n", __func__, __LINE__, idx);
    // }

    for (size_t i = 0; i < 3; i++)
    {
        printf("%lu\n", i);
    }


    printf("123\n");

    return 0;
}