#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *d;

	d = (char *)malloc(sizeof(char) * 0);
	printf("%s\n", d);
}
