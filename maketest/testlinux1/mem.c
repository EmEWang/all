#include <stdlib.h>
#include <string.h>
void main()
{
    char *p1, *p2;
    p1 = (char *)malloc(sizeof(char) * 18); // 0x602010
    p2 = (char *)malloc(sizeof(char) * 1);  // 0x602030
    memcpy(p1, "111111111111111111", 18);
}