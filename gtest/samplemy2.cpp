
#include "samplemy2.h"
#include <string.h>

// bool Odd(int a) {
//     if (a % 2 == 1)
//     {
//         return true;
//     }

//     return false;
// }

int Add(int a, int b)
{
    int i = a+b;
    return i;
}


char temp[100];
char* strJoin(const char* str1, const char* str2)
{
    sprintf(temp, "%s %s", str1, str2);
    return temp;
}

float Addfloat(float a, float b)
{
    return a + b;
}

int Calc::add(int a, int b) {
    return a + b;
};
