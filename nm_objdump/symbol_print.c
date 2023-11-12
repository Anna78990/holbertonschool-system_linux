#include "hreadelf.h"

#define GETSYM(i, x) \
	((h->e64.e_ident[EI_CLASS] == ELFCLASS32) ? h->sym32[i].x : h->sym64[i].x)


/**
 * print_symbol_table32 - prints 32 bit program headers
 * @h: pointer to elf header struct
 * @string_table: the string table program
 * @sym_string_table: the symbol string table
 * @section: the symbol section to print
 * Return: number of symbols printed
 */
size_t print_symbol_table32(header *h, char *string_table,
	char *sym_string_table, int section)
{
	size_t i = 0, num_printed = 0;
	size_t size = GETS(section, sh_size) / GETS(section, sh_entsize);

	for (i = 0; i < size; i++)
	{
		if ((GETSYM(i, st_info) & 0xf) == STT_SECTION ||
			(GETSYM(i, st_info) & 0xf) == STT_FILE || !i)
			continue;
		if (get_nm_type32(h->sym32[i], h->s32) != 'U' &&
			get_nm_type32(h->sym32[i], h->s32) != 'w')
			printf("%8.8lx ", GETSYM(i, st_value));
		else
			printf("%8s ", "");
		printf("%c %s\n",
			get_nm_type32(h->sym32[i], h->s32),
			sym_string_table + GETSYM(i, st_name));
		num_printed++;
	}
	return (num_printed);
	(void)string_table;
}

/**
 * print_program_headers64 - prints 64 bit program headers
 * @h: pointer to elf header struct
 * @string_table: the string table program
 * @sym_string_table: the symbol string table
 * @section: the symbol section to print
 * Return: number of symbols printed
 */
size_t print_symbol_table64(header *h, char *string_table,
	char *sym_string_table, int section)
{
	size_t i = 0, num_printed = 0;
	size_t size = GETS(section, sh_size) / GETS(section, sh_entsize);

	for (i = 0; i < size; i++)
	{
		if ((GETSYM(i, st_info) & 0xf) == STT_SECTION ||
			(GETSYM(i, st_info) & 0xf) == STT_FILE || !i)
			continue;
		if (get_nm_type64(h->sym64[i], h->s64) != 'U' &&
			get_nm_type64(h->sym64[i], h->s64) != 'w')
			printf("%16.16lx ", GETSYM(i, st_value));
		else
			printf("%16s ", "");
		printf("%c %s\n",
			get_nm_type64(h->sym64[i], h->s64),
			sym_string_table + GETSYM(i, st_name));
		num_printed++;
	}
	return (num_printed);
	(void)string_table;
}


/**
 * print_all_symbol_tables - prints all the symbol table stuff
 * @h: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * @num_printed: pointer to var storing number of symbols printed
 * Return: 0 on success else exit_status
 */
int print_all_symbol_tables(header *h, int fd, size_t *num_printed)
{
	char *string_table = NULL;
	size_t i;

	if (!GETE(e_shnum))
	{
		printf("\nThere are no section headers in this file.\n");
		return (0);
	}
	read_section_headers(h, fd);
	for (i = 0; i < GETE(e_shnum); i++)
		switch_end_sec(h, i);
	string_table = read_string_table(h, fd);
	for (i = 0; i < GETE(e_shnum); i++)
	{
		if (GETS(i, sh_type) == SHT_SYMTAB)
		{
			*num_printed += print_symbol_table(h, fd, i, string_table);
		}
	}
	free(string_table);
	return (0);
}

/**
 * print_all_table - prints just one symbol table
 * @h: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * @i: section index of current symbol table
 * @string_table: the section header string_table
 * Return: number of symbols printed
 */
size_t print_symbol_table(header *h, int fd, size_t i,
	char *string_table)
{
	char *sym_string_table = NULL;
	size_t size, j, num_printed;

	size = GETS(i, sh_size) / GETS(i, sh_entsize);
	read_symbol_table(h, fd, i);
	for (j = 0; j < size; j++)
		switch_endians_symbol(h, j);
	sym_string_table = read_symbol_string_table(h, fd, i + 1);

	if ((h->e64).e_ident[EI_CLASS] == ELFCLASS64)
	{
		num_printed = print_symbol_table64(h, string_table,
			sym_string_table, i);
		h->sym64 = (free(h->sym64), NULL);
	}
	else
	{
		num_printed = print_symbol_table32(h, string_table,
			sym_string_table, i);
		h->sym32 = (free(h->sym32), NULL);
	}
	sym_string_table = (free(sym_string_table), NULL);
	return (num_printed);
}
