#include <stdio.h>

int main(void)
{
	int i = 0;
	
	for (i = 0; i < 3; i++)
	{
		printf("===\n");
		printf("%d\n", i);
                printf("---\n");
	}

	printf("%d\n", i);
	for (i = 0; i < 3; i++)
	{
		printf("===\n");
		printf("%d\n", i);
                printf("---\n");
	}
	printf("%d\n", i);
}
