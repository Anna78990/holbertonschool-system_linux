#include <stdio.h>
#include <sys/sysinfo.h>
 


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
	printf("get_nprocs_conf() = %d, get_nprocs() = %d\n",
		get_nprocs_conf(), get_nprocs());
}
