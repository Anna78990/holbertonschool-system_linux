#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "_getline.h"


char *find_line(read_t reader)
{
	int i, j, byte_read = 0;
	char *line, *tmp, *buf;

	for (i = 0; i < READ_SIZE; i++)
	{
		if (reader->buf[i] == '\n')
		{
			line = (char *)malloc(sizeof(char) * (i + 1));
			strncpy(line, reader->buf, i);
			i += 1;
			line[i] = '\0';
			buf = (char *)malloc(sizeof(char) * (reader->size - i + 1));
			for (j = 0; j + i < reader->size; j++)
			{
				buf[j] = reader->buf[i + j];
			}
			buf[j + i] = '\0';
			free(reader->buf);
			reader->buf = buf;
			reader->size -= i;
			return (tmp);
		}
	}
	tmp = reader->buf;
	free(reader->buf);
	reader->buf = 

}


char *_getline(const int fd)
{
	static read_t *reader;
	static char buffer;
	static ssize_t bytes_read = 0;
	static ssize_t current_pos = 0;
	static ssize_t line_length = 0;
	char *line = NULL;
	ssize_t i = 0;

	if (fd < 0)
		return (NULL);

	if (reader != NULL || reader->fd != fd)
	{
		reader->fd = fd;
		reader = (read_t *)malloc(sizeof(read_t));
		if (reader == NULL)
			return (NULL);
		buffer = (char *)malloc(sizeof(char) * READ_SIZE);
		if (buffer == NULL)
			return (NULL);
		reader->size = read(fd, buffer, READ_SIZE);
		reader->buf = buffer;
	}
	

