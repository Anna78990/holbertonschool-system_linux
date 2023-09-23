#include "hreadelf.h"


/**
 * read_section_headers - reads the section headers into data
 * @h: pointer to header struct
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
 * print_section_headers - prints all the ELF section headers
 * @h: pointer to header struct
 * @fd: the file descriptor of our ELF file
 * Return: 0 on success else exit_status
 */
int print_section_headers(header *h, int fd)
{
	char *str;
	size_t i;

	if (!((h->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		h->e32.e_shnum : h->e64.e_shnum))
		return (1);
	printf("There are %d section headers, starting at offset 0x%lx:\n",
		GETE(e_shnum), GETE(e_shoff));
	read_section_headers(h, fd);
	for (i = 0; i < GETE(e_shnum); i++)
		switch_end_sec(h, i);
	str = calloc(1, GETS(GETE(e_shstrndx), sh_size));
	if (!str)
		exit(1);

	lseek(fd, GETS(GETE(e_shstrndx), sh_offset), SEEK_SET);
	read(fd, str, GETS(GETE(e_shstrndx), sh_size));
	printf("\nSection Headers:\n");
	if (h->e64.e_ident[EI_CLASS] == ELFCLASS32)
		print_section32(h, str);
	else
		print_section64(h, str);
	printf("%s", KEY_FLAG);
	if (h->e64.e_ident[EI_CLASS] == ELFCLASS64)
		printf(", l (large)");
	free(str);
	return (0);
}
