#include <stdio.h>

int main(void)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (i == 1)
			continue;
		printf("i is %d\n", i);
	}

}
