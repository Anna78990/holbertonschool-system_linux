#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *hello, *d;

	d = (char *)malloc(sizeof(char) * 12);
	strcpy(d, "hello world");
	hello = (char *)malloc(sizeof(char) * 12);
	strcpy(hello, d);
	free(d);
	printf("%s\n", hello);
}
