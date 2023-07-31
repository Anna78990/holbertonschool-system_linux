#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(void)
{
	FILE *fp;
	char *line = NULL;
	char buffer[2000];
	size_t len = 0, a, b;
	fp = fopen("foo.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	a = read(fileno(fp), buffer, 100);
	printf("a is %d\n", (int)a);
	printf("buffer[2] is %c, buffer[3] is %c\n", buffer[2], buffer[3]);
	if (line)
		free(line);

	return EXIT_SUCCESS;
}
