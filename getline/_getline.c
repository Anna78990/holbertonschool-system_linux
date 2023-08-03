#include <stdio.h>
#include "_getline.h"
#include "string.h"

char *write_buf(read_t *reader);
read_t *get_buf(read_t *reader, int fd);
char *_strchr(char *s, char c, int len);

/**
 * _getline - getline of given fd
 * @fd: fd to search line
 * Return: gotten line
 */
char *_getline(const int fd)
{
	static read_t reads;
	static char buf[READ_SIZE + 1];
	read_t *reader = NULL, *tmp = NULL;
	static size_t len;
	char *line = NULL;

	if (fd == -1)
	{
		if (reads.buf)
		{
			free(reads.buf);
			reads.buf = NULL;
		}
		for (reader = reads.next; reader;)
		{
			if (reader->buf)
			{
				free(reader->buf);
				reader->buf = NULL;
			}
			tmp = reader;
			reader = reader->next;
			free(tmp);
		}
		memset(&reads, 0, sizeof(reads));
		memset(buf, 0, len);
		len = 0;
		return (NULL);
	}
	reader = get_buf(&reads, fd);
	if ((reader == &reads) && len)
	{
		reader->buf = malloc(len + 1);
		if (!reader->buf)
			return (NULL);
		reader->size = len;
		memcpy(reader->buf, buf, len);
		len = 0;
	}
	if (reader)
	{
		line = write_buf(reader);
	}
	if (line)
	{
		if (strlen(line) == 1 && line[0] == 10)
			line[0] = '\0';
	}
	if ((reader == &reads) && reader->buf)
	{
		len = reader->size - reader->idx;
		memcpy(buf, reader->buf + reader->idx, len);
		free(reader->buf);
		reader->buf = NULL;
		reader->size = reader->idx = 0;
	}
	return (line);
}

/**
 * write_buf - write the correct string on the buf of reader
 * @reader: reader to refer
 * Return: string to return
 */
char *write_buf(read_t *reader)
{
	char buf[READ_SIZE + 1], *p, *line;
	ssize_t r = 0;

	p = _strchr(reader->buf + reader->idx, '\n', reader->size);
	if (!reader->size || reader->idx + 1 == reader->size || !p)
	{
		while (1)
		{
			r = read(reader->fd, buf, READ_SIZE);
			if (r < 0 || (r == 0 && !reader->buf))
			{
				if (reader->buf)
					free(reader->buf);
				return (NULL);
			}
			if (r == 0)
			{
				p = reader->buf + reader->size;
				break;
			}
			reader->buf = realloc(reader->buf, reader->size + r + 1);
			if (!reader->buf)
				return (NULL);
			memcpy(reader->buf + reader->size, buf, r);
			reader->size += r;
			reader->l_char = reader->buf[reader->size - 2];
			p = _strchr(reader->buf + (reader->size - r), '\n', r);
			if (p)
			{
				reader->buf[reader->size] = 0;
				break;
			}
		}
	}
	*p = '\0';
	line = malloc(1 + (p - (reader->buf + reader->idx)));
	if (!line)
		return (NULL);
	memcpy(line, reader->buf + reader->idx,
			1 + (p - (reader->buf + reader->idx)));
	reader->idx = (p - reader->buf) + 1;
	if (reader->idx >= reader->size)
	{
		reader->idx = reader->size = 0;
		free(reader->buf);
		reader->buf = NULL;
	}
	return (line);
}

/**
 * get_buf - get buf to store read string
 * @reader: pointer to reader
 * @fd: file discriptor
 * Return: pointer to buf
 */
read_t *get_buf(read_t *reader, int fd)
{
	read_t *r;

	if (!reader->fd && !reader->next)
	{
		reader->buf = NULL;
		reader->fd = fd;
		return (reader);
	}
	else if (fd < reader->fd)
	{
		r = malloc(sizeof(*r));
		if (!r)
			return (NULL);
		memcpy(r, reader, sizeof(*reader));
		memset(reader, 0, sizeof(*reader));
		reader->buf = NULL;
		reader->fd = fd;
		reader->next = r;
		return (reader);
	}
	for (; reader->next && reader->next->fd <= fd; reader = reader->next)
		;
	if (reader->fd == fd)
	{
		return (reader);
	}
	r = malloc(sizeof(*r));
	if (!r)
		return (NULL);
	memset(r, 0, sizeof(*r));
	r->buf = NULL;
	r->fd = fd;
	r->next = reader->next;
	reader->next = r;
	return (r);
}
/**
 * *_strchr - locates a character in a string
 * @s: pointer to the string
 * @c: character to search
 * @length: length of string
 * Return: (&s[i]) or (NULL)
 */
char *_strchr(char *s, char c, int length)
{
	int i;

	if (!s)
		return (NULL);
	for (i = 0; i < length; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (NULL);
}
