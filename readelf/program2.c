#include "hreadelf.h"

/**
 * read_strings - reads the string table
 * @h: pointer to header struct
 * @fd: file descriptor
 * Return: pointer to beginning of table
 */
char *read_strings(header *h, int fd)
{
	char *str;

	str = calloc(1, GETS(GETE(e_shstrndx), sh_size));
	if (!str)
		exit(1);

	lseek(fd, GETS(GETE(e_shstrndx), sh_offset), SEEK_SET);
	read(fd, str, GETS(GETE(e_shstrndx), sh_size));
	return (str);
}

/**
 * print_sec_to_seg - self-documenting
 * @h: pointer to header struct
 * @str: the string
 * Return: 0 on success else error
 */
int print_sec_to_seg(header *h, char *str)
{
	size_t i, j;

	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	for (i = 0; i < GETE(e_phnum); i++)
	{
		printf("   %2.2lu     ", i);
		for (j = 0; j < GETE(e_shnum); j++)
		{
			if (h->e64.e_ident[EI_CLASS] == ELFCLASS32)
			{
				if (IS_IN_SEG_MEM((&h->s32[j]),
					(&h->p32[i])))
					printf("%s ", str + GETS(j, sh_name));
			}
			else
			{
				if (IS_IN_SEG_MEM((&h->s64[j]),
					(&h->p64[i])))
					printf("%s ", str + GETS(j, sh_name));
			}
		}
		printf("\n");
	}
	return (0);
}
