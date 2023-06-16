#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "_getline.h"

#include <stdio.h>

char *find_line(read_t *reader)
{
	int i, j;
	char *line, *tmp, *buf;

	for (i = 0; i < reader->size; i++)
	{
		if (reader->buf[i] == '\n')
		{
			line = (char *)malloc(sizeof(char) * i);
			strncpy(line, reader->buf, i);
			line[i] = '\0';
			buf = (char *)malloc(sizeof(char) * (reader->size - i));
			i += 1;
			for (j = 0; j + i < reader->size; j++)
				buf[j] = reader->buf[i + j];
			free(reader->buf);
			reader->buf = (char *)malloc(sizeof(char) * (reader->size - i));
			strcpy(reader->buf, buf);
			reader->buf[j] = '\0';
			reader->size = j;
			return (line);
		}
	}
	tmp = (char *)malloc(sizeof(char) * reader->size);
	strcpy(tmp, reader->buf);
	tmp[reader->size] = '\0';
	free(reader->buf);
	buf = (char *)malloc(sizeof(char) * READ_SIZE + 1);
	reader->size = read(reader->fd, buf, READ_SIZE);
	if (reader->size < 1)
	{
		free(buf);
		free(reader);
	}
	else
	{
		buf[READ_SIZE] = '\0';
		reader->buf = buf;
	}
	return (tmp);
}


char *_getline(const int fd)
{
	static read_t *reader;
	char *buffer;

	if (fd < 0)
		return (NULL);

	if (reader == NULL)
	{
		reader = (read_t *)malloc(sizeof(read_t));
		if (reader == NULL)
			return (NULL);
		reader->fd = fd;
		reader->buf = (char *)malloc(sizeof(char) * (READ_SIZE + 1));
		if (reader->buf == NULL)
			return (NULL);
		reader->size = read(fd, reader->buf, READ_SIZE);
		reader->buf[READ_SIZE] = '\0';
	}
	else if (reader->fd != fd)
	{
		reader = (read_t *)malloc(sizeof(read_t));
		reader->fd = fd;
		if (reader == NULL)
			return (NULL);
		buffer = (char *)malloc(sizeof(char) * (READ_SIZE + 1));
		if (buffer == NULL)
			return (NULL);
		reader->size = read(fd, buffer, READ_SIZE);
		buffer[READ_SIZE] = '\0';
		reader->buf = buffer;
	}
	if (reader->size == 0)
		return (NULL);
	return (find_line(reader));
}
