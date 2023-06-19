#include <stdio.h>

int main(void)
{
	char *alpha = "abcdefjhijklmnopqrstuvwxyz";
	int i;

	for (i = 0; alpha[i]; i++)
		;
	printf("la taille de alpha egale %d \n", i);

	for (i = 1; i < 27; i++)
	{
		if (i == 1)
			printf("%c is %dst alphabet\n", alpha[0], i);
		else if (i == 2)
			printf("%c is %dnd alphabet\n", alpha[1], i);
		else if (i == 3)
			printf("%c is %drd alphabet\n", alpha[2], i);
		else 
			printf("%c is %dth alphabet\n", alpha[i - 1], i);
	}
	return 0;
}
