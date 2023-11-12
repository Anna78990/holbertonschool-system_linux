#include "hreadelf.h"

/**
 * has_section - checks if objfile has given section name
 * @h: the header
 * @string_table: the header string table
 * @section_name: the name
 * Return: 1 if has it else 0
 */
int has_section(header *h, char *string_table, char *section_name)
{
	size_t i = 0;

	section_name = strdup(section_name);
	for (i = 1; i < GETE(e_shnum); i++)
		if (!strcmp(string_table + GETS(i, sh_name), section_name))
			return (1);
	return (0);
}

/**
 * flag_print - prints the string flag list
 * @flags: the flags for this file
 */
void flag_print(unsigned long flags)
{
	int first = 1;

	if (flags & 0x01)
		first = (printf("%s%s", first ? "" : ", ", "HAS_RELOC"), 0);
	if (flags & 0x02)
		first = (printf("%s%s", first ? "" : ", ", "EXEC_P"), 0);
	if (flags & 0x04)
		first = (printf("%s%s", first ? "" : ", ", "HAS_LINENO"), 0);
	if (flags & 0x08)
		first = (printf("%s%s", first ? "" : ", ", "HAS_DEBUG"), 0);
	if (flags & 0x10)
		first = (printf("%s%s", first ? "" : ", ", "HAS_SYMS"), 0);
	if (flags & 0x20)
		first = (printf("%s%s", first ? "" : ", ", "HAS_LOCALS"), 0);
	if (flags & 0x40)
		first = (printf("%s%s", first ? "" : ", ", "DYNAMIC"), 0);
	if (flags & 0x80)
		first = (printf("%s%s", first ? "" : ", ", "WP_TEXT"), 0);
	if (flags & 0x100)
		first = (printf("%s%s", first ? "" : ", ", "D_PAGED"), 0);
	if (!first)
		printf("\n");
}

/**
 * get_file_format - gets the string format type
 * @h: the internal header
 * Return: string type
 */
char *get_file_format(header *h)
{
	static char buf[32];

	*buf = 0;
	sprintf(buf, "elf%d-%s",
		(h->e64).e_ident[EI_CLASS] == ELFCLASS64 ? 64 : 32,
		((h->e64).e_ident[EI_DATA] == ELFDATA2MSB) ? "big" :
		((h->e64).e_ident[EI_CLASS] == ELFCLASS64) ? "x86-64" :
		"i386");
	return (buf);
}

/**
 * header_print - prints the -f style header
 * @h: the header
 * @string_table: the header string table
 */
void header_print(header *h, char *string_table)
{
	unsigned long flags = 0;

	printf("architecture: ");
	if ((h->e64).e_ident[EI_DATA] == ELFDATA2MSB)
		printf("UNKNOWN!");
	else if ((h->e64).e_ident[EI_CLASS] == ELFCLASS64)
		printf("i386:x86-64");
	else
		printf("i386");

	if (GETE(e_type) == ET_REL)
		flags |= 0x01;
	else if (GETE(e_type) == ET_EXEC)
		flags |= 0x02;
	else if (GETE(e_type) == ET_DYN)
		flags |= 0x40;

	if (GETE(e_phnum) > 0)
		flags |= 0x100;
	if (has_section(h, string_table, ".symtab"))
		flags |= 0x10;
	if (has_section(h, string_table, ".dynsym"))
		flags |= 0x10;
	if (has_section(h, string_table, ".locals"))
		flags |= 0x20;
	if (has_section(h, string_table, ".lineno"))
		flags |= 0x04;
	if (has_section(h, string_table, ".debug"))
		flags |= 0x08;

	printf(", flags 0x%08lx:\n", flags);
	flag_print(flags);
	printf("start address 0x%0*lx\n\n",
		(h->e64).e_ident[EI_CLASS] == ELFCLASS64 ? 16 : 8,
		GETE(e_entry));
}
