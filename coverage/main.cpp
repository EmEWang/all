#include <stdio.h>
#include <stdlib.h>
#include "module1/inc/module1_1.h"
#include "module1/inc/module1_2.h"
#include "module2/inc/module2_1.h"

#define BAR(x) ((x) || (x))
template <typename T> void foo(T x) {
  for (unsigned I = 0; I < 10; ++I) { BAR(I); }
}

int main(int argc, char **argv)
{
    int loop = atoi(argv[1]);
    int i1 = 0;

    for(int idx =2; idx < loop; idx++)
    {
        printf("%s line %d, %d\n", __func__, __LINE__, idx);
    }

    i1 +=1 ;

    for (size_t i = 0; i < 5; i++)
    {
        i1 += 1;
        i1 += add1_1(1,1);
    }

    int i2 = add1_2(1,2);
    int i3 = add2_1(11,1);

    int i4 = 0;
    for (size_t i = 0; i < 3; i++)
    {
        i4 += mut1_1(1,1);
    }

    if (0)
    {
        i1 += 1;
    }


//     printf("1:%d 2:%d 3:%d\n", i1, i2, i3);

    foo<int>(0);
    foo<float>(0);

    ttt();

    return 0;
}