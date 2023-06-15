#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd, sz;
	char *buf, *b, *tmp;

	buf = (char *)malloc(sizeof(char) * 20);
	b = (char *)malloc(sizeof(char) * 20);

	fd = open("foo.txt", O_RDONLY);
	if (fd < 0) {
		perror("r1");
		exit(1);
	}

	sz = read(fd, buf, 6);
	printf("called read(%d, buf, 6). returned that"
		" %d bytes were read.\n",
		fd, sz);
	buf[sz] = '\n';
	printf("%d\n", sz);
	printf("1st read fd = %d\n", fd);
	printf("Those bytes are as follows: %s\n", buf);
	printf("1ST CHAR IS '%c'\n", buf[0]);
	sz = read(fd, b, 6);
        printf("2nd read fd = %d\n", fd);
	b[sz] = '\0';
	printf("%d\n", sz);
	printf("Those bytes are as follows 1: %s\n", buf);
	printf("Those bytes are as follows 2: %s\n", b);
	printf("1ST CHAR IS '%c'\n", b[0]);
	tmp = (char *)malloc(sizeof(char) * 2);
	strncpy(tmp, buf, 2);
	free(buf);
	printf("%s", tmp);
	return 0;
}

