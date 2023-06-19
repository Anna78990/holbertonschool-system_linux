#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "_getline.h"

#include <stdio.h>

static int test = 0;

void free_readers(read_t *reader)
{
	read_t *tmp;

	while (reader)
	{
		tmp = reader;
		reader = reader->next;
		free(tmp->buf);
		free(tmp);
	}
}

char *find_line(read_t *reader)
{
	int i, j, size;
	char *line, *tmp, *buf;
	read_t *reads = malloc(sizeof(read_t));

	for (i = 0; i < reader->size; i++)
	{
		if (reader->buf[i] == '\n')
		{
			line = (char *)malloc(sizeof(char) * i);
			strncpy(line, reader->buf, i);
			line[i] = '\0';
			reads->buf = (char *)malloc(sizeof(char) * (reader->size - i));
			i += 1;
			for (j = 0; j + i < reader->size; j++)
				reads->buf[j] = reader->buf[i + j];
			reads->buf[j] = '\0';
			reader->buf = line;
			reads->size = j;
			reads->next = reader, reader = reads;
			printf("reader->buf is %s\n", reader->buf);
			printf("reads->buf is %s\n", reads->buf);
			return (line);
		}
	}
	tmp = (char *)malloc(sizeof(char) * reader->size);
	strcpy(tmp, reader->buf);
	tmp[reader->size] = '\0';
	size = reader->size;
	buf = (char *)malloc(sizeof(char) * READ_SIZE);
	reads->size = read(reader->fd, buf, READ_SIZE);
	
	buf[reader->size] = '\0';
	tmp = (char *) realloc(tmp, sizeof(char) * (reader->size + size));
	strcat(tmp, buf);
	free(buf);
	reads->buf = tmp;
	reads->next = reader, reader = reads;
	if (reads->buf == NULL)
		return (NULL);
	return (find_line(reader));
}


char *_getline(const int fd)
{
	static read_t *reader, *r;
	char *tmp;

	
	if (fd < 0)
		return (NULL);

	printf("%d\n", test);
	test += 1;
	if (reader)
	{
		printf("reader->buf: %s, size->%d, next->%p\n", reader->buf, reader->size, reader->next);
		if (reader->next)
		{	
			r = reader->next;
			printf("reader->buf: %s, size->%d, next->%p\n", r->buf, r->size, r->next);
		}
	}
	if (reader == NULL)
	{
		reader = (read_t *)malloc(sizeof(read_t));
		if (reader == NULL)
			return (NULL);
		reader->fd = fd;
		reader->buf = (char *)malloc(sizeof(char) * (READ_SIZE));
		if (reader->buf == NULL)
			return (NULL);
		reader->size = read(fd, reader->buf, READ_SIZE);
		reader->buf[READ_SIZE] = '\0';
		reader->next = reader;
	}
	else if (reader->fd != fd)
	{
		reader = (read_t *)malloc(sizeof(read_t));
		if (reader == NULL)
			return (NULL);
		reader->fd = fd;
		reader->buf = (char *)malloc(sizeof(char) * (READ_SIZE));
		if (reader->buf == NULL)
			return (NULL);
		reader->size = read(fd, reader->buf, READ_SIZE);
		reader->buf[READ_SIZE] = '\0';
		reader->next = reader;
	}
	tmp = find_line(reader);
	if (tmp)
		return (tmp);
	else
		free_readers(reader);
	return (NULL);
}
