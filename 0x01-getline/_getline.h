#ifndef _GETLINE_H
#define _GETLINE_H

#define READ_SIZE 80

/**
 * struct read_s - structure which keep the information of readed line
 * @fd: file desciptor
 * @buf: buffer of read
 * @bytes: number of bytes read
 *
 * Description: Longer description
 */
typedef struct read_s
{
	int fd;
	char *buf;
	int size;
	struct read_s *next;
} read_t;

char *_getline(const int fd);
char *find_line(read_t *rd);

#endif
