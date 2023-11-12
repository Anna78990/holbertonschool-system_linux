#include "hreadelf.h"

/**
 * read_symbol_table - reads the symbol headers into data
 * @h: the internal header
 * @fd: file descriptor to read
 * @i: the current symbol section to print
 */
void read_symbol_table(header *h, int fd, int i)
{
	size_t r;
	char *headers;
	size_t read_size = GETS(i, sh_size);

	headers = calloc(1, read_size);
	if (!headers)
		exit(1);
	lseek(fd, GETS(i, sh_offset), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
	{
		fprintf(stderr, "Symbol read failed.\n");
		exit(1);
	}
	if (h->e64.e_ident[EI_CLASS] == ELFCLASS32)
		h->sym32 = (void *)headers;
	else
		h->sym64 = (void *)headers;
}

/**
 * read_symbol_string_table - reads the string table
 * @h: the internal header
 * @fd: file descriptor to read
 * @i: the current symbol section to print
 * Return: pointer to beginning of table
 */
char *read_symbol_string_table(header *h, int fd, int i)
{
	char *str;

	str = calloc(1, GETS(i, sh_size));
	if (!str)
		exit(1);

	lseek(fd, GETS(i, sh_offset), SEEK_SET);
	read(fd, str, GETS(i, sh_size));
	return (str);
}


/**
 * symbol_type4 - gets type of symbol in one char
 * @sym: the symbol struct
 * @shdr: the array of section header structs
 * Return: the char type
 */
char symbol_type4(Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char c;

	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
		ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
		c = sym.st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
		c = sym.st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym.st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		c = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}

/**
 * symbol_type2 - gets type of symbol in one char
 * @sym: the symbol struct
 * @shdr: the array of section header structs
 * Return: the char type
 */
char symbol_type2(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char  c;

	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK &&
		ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
		c = sym.st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK)
		c = sym.st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym.st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		c = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}

