#include <stdio.h>

int main(void)
{
	int i, j = 0;
	
	for (i = 0; i <= 3; i++)
	{
		printf("i = %d\n", i);

		for (j = 0; j <= 3; j++)
		{
			printf("	j = %d\n", j);
			if (j == 2)
			{
				printf("--\n");
				break;
			}
		}
	}
}
