#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "_getline.h"

#include <stdio.h>


/**
 * free_readers - free reader structs
 * @reader: reader structs to free
 */
void free_readers(read_t *reader)
{
	read_t *tmp;

	while (reader)
	{
		tmp = reader;
		reader = reader->next;
		if (tmp->buf)
			free(tmp->buf);
		free(tmp);
	}
}

/**
 * find_line - find line
 * @reader: reader to use
 * Return: gotten line
 */
char *find_line(read_t *reader)
{
	int i, j, size;
	char *line, *tmp, *buf, *next_line;

	if (reader->size <= 0)
	{
		free_readers(reader);
		return (NULL);
	}
	for (i = 0; i < reader->size; i++)
		if (reader->buf[i] == '\n')
		{
			if (i == 0)
				line = (char *)malloc(sizeof(char) * 1);
			else
			{
				line = (char *)malloc(sizeof(char) * (i + 1));
				memset(line, '\0', i + 1), memcpy(line, reader->buf, i);
			}
			line[i] = '\0', i += 1;
			buf = (char *)malloc(sizeof(char) * (reader->size - i + 1));
			memset(buf, '\0', reader->size - i + 1);
			for (j = 0; j + i < reader->size; j++)
				buf[j] = reader->buf[i + j];
			buf[j] = '\0', reader->buf = buf, reader->size = j;
			return (line);
		}
	size = reader->size, line = (char *)malloc(sizeof(char) * (READ_SIZE));
	reader->size = read(reader->fd, line, READ_SIZE);
	tmp = (char *)malloc(sizeof(char) * (reader->size + size));
	memset(tmp, '\0', reader->size + size);
	memcpy(tmp, reader->buf, size), free(reader->buf);
	memcpy(tmp + size, line, reader->size);
	reader->buf = tmp, reader->size = size + reader->size;
	next_line = find_line(reader);
	if (next_line != NULL)
	{
		free(line);
		return (next_line);
	}
	return (NULL);
}

/**
 * _getline - getline of given fd
 * @fd: fd to search line
 * Return: gotten line
 */
char *_getline(const int fd)
{
	static read_t *reads, *reader;
	char *buf;
	size_t bytes;

	if (reader)
		printf("** now, reader->size = %d**\n", reader->size);
	else
		printf("** reader does not exist**\n");
	if (fd == -1)
	{
		free_readers(reader);
		reads = NULL;
		reader = NULL;
		return (NULL);
	}
	reads = reader;
	while (reads)
	{
		if (reads->fd == fd)
		{
			if (reads->size <= 0)
				reads->size = read(fd, reads->buf, READ_SIZE);
			return (find_line(reads));
		}
		reader = reads;
		reads = reads->next;
		free(reader->buf);
		free(reader);
	}
	buf = malloc(sizeof(char) * READ_SIZE);
	bytes = read(fd, buf, READ_SIZE);
	if (bytes <= 0)
	{
		free(buf);
		return (NULL);
	}
	reads = malloc(sizeof(read_t));
	if (reads == NULL)
		return (NULL);
	reads->fd = fd;
	reads->buf = buf;
	reads->size = bytes;
	reads->next = reader;
	reader = reads;
	return (find_line(reads));
}
