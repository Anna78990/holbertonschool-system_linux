#ifndef _GETLINE_H
#define _GETLINE_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ_SIZE 1024

/**
 * struct read_s - structure which keep the information of readed line
 * @fd: file desciptor
 * @buf: buffer of read
 * @idx: index to start
 * @size: size of bytes
 * @l_char: last alphabet of the buf
 * @next: pointer to next
 * Description: Longer description
 */
typedef struct read_s
{
	int fd;
	char *buf;
	int idx;
	int size;
	char l_char;
	struct read_s *next;
} read_t;

char *_getline(const int fd);

#endif
