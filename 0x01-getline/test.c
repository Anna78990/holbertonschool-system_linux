#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *hello, *h1, *h2, k[5], *d;
	int i = 11, j, a, fd;

	hello = (char *)malloc(sizeof(char) * 11);
	strcpy(hello, "hello world");
	printf("hello = %s\n", hello);
	printf("hello = %c\n", hello[10]);
	if (!hello[11])
		printf("hello[11] is null pointer\n");
	h1 = (char *)malloc(sizeof(char) * 7);
	for (j = 0; j < 11; j++)
	{
		if (hello[j] == ' ')
		{
			strncpy(h1, hello, j + 1);
			break;
		}
	}
	printf("%d\n", j); //
	printf("h1[5] == %c\n", h1[5]);
	h1[j + 1] = '\0';
	if (!h1[6])
		printf("h1[6] is null pointer\n");
	printf("h1 is %s\n", h1);
	h2 = (char *)malloc(sizeof(char) * (11 - 6 + 1));
	j += 1;
	for (i = 0; i + j < 11; i++)
		h2[i] = hello[i + j];
	printf("i = %d, j = %d sum = %d", i, j, i + j);
	h2[i] = '\0';
	printf("%s\n", h2);

	fd = open("a1", 0);
	a = read(fd, k, 5);
	printf("%s\n", k);
	printf("%d\n", a);
	d = (char *)malloc(sizeof(char) * 6);
	a = read(fd, d, 5);
	printf("%s\n", d);
	printf("%d\n", a);
	return (0);
}
