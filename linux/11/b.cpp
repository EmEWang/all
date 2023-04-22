#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main()
{
	printf("start\n");

	int n = 0;

	while(1)
	{
		sleep(1);
		printf("num:%d\n", ++n);
	}
	
	return 0;	
}

