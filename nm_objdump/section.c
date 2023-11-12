#include "hreadelf.h"
/**
 * read_section_headers - reads the section headers into data
 * @h: the internal header
 * @fd: file descriptor to read
 */
void read_section_headers(header *h, int fd)
{
	size_t i = GETE(e_shnum), r;
	char *headers;
	size_t read_size = GETE(e_shentsize) * GETE(e_shnum);

	if (!i)
		return;
	headers = calloc(i, read_size * i);
	if (!headers)
		exit(1);
	lseek(fd, GETE(e_shoff), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
		exit(1);
	if (h->e64.e_ident[EI_CLASS] == ELFCLASS32)
		h->s32 = (void *)headers;
	else
		h->s64 = (void *)headers;
}

/**
 * read_string_table - reads the string table
 * @h: the internal header
 * @fd: file descriptor to read
 * Return: pointer to beginning of table
 */
char *read_string_table(header *h, int fd)
{
	char *str;

	str = calloc(1, GETS(GETE(e_shstrndx), sh_size));
	if (!str)
		exit(1);

	lseek(fd, GETS(GETE(e_shstrndx), sh_offset), SEEK_SET);
	read(fd, str, GETS(GETE(e_shstrndx), sh_size));
	return (str);
}
