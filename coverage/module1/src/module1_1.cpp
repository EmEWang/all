#include "../inc/module1_1.h"


int add1_1(int a, int b)
{
    if (a > 1)
    {
        printf("a > 1");
    }
    else
    {
        printf("a <= 1");
    }

    int c = a + b;
    return c;
}


int sub1_1(int a, int b)
{
    int c = a - b;
    return c;
}