#include "hreadelf.h"

/**
 * read_data - reads a block of data from descriptor
 * @h: the internal header
 * @fd: the descriptor to read
 * @offset: offset to start at
 * @size: number of bytes to read
 * Return: pointer to the data
 */
void *read_data(header *h, int fd, unsigned long offset, long size)
{
	void *str = NULL;

	str = calloc(1, size);
	if (!str)
		exit(1);
	/* printf("Reading [%lu] bytes at offset [%lu]\n", size, offset); */
	lseek(fd, offset, SEEK_SET);
	if (read(fd, str, size) != size)
	{
		fprintf(stderr, "Read error.\n");
		exit(1);
	}
	return (str);
	(void)h;
}
