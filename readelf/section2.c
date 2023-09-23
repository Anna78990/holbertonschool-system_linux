#include "hreadelf.h"


#define FORMAT_32 \
	"  [%2u] %-17s %-15.15s %8.8lx %6.6lx %6.6lx %2.2lx %3s %2u %3u %2lu\n"

#define FORMAT_64 \
	"  [%2u] %-17s %-15.15s %16.16lx %6.6lx %6.6lx %2.2lx %3s %2u %3u %2lu\n"

/**
 * get_sec_type - return string type of section
 * @sh_type: the section type
 * Return: string name of type
 */
char *get_sec_type(unsigned int sh_type)
{
	static char buf[32];

	switch (sh_type)
	{
		case SHT_NULL:		return ("NULL");
		case SHT_PROGBITS:		return ("PROGBITS");
		case SHT_SYMTAB:		return ("SYMTAB");
		case SHT_STRTAB:		return ("STRTAB");
		case SHT_RELA:		return ("RELA");
		case SHT_HASH:		return ("HASH");
		case SHT_DYNAMIC:		return ("DYNAMIC");
		case SHT_NOTE:		return ("NOTE");
		case SHT_NOBITS:		return ("NOBITS");
		case SHT_REL:		return ("REL");
		case SHT_SHLIB:		return ("SHLIB");
		case SHT_DYNSYM:		return ("DYNSYM");
		case SHT_INIT_ARRAY:	return ("INIT_ARRAY");
		case SHT_FINI_ARRAY:	return ("FINI_ARRAY");
		case SHT_PREINIT_ARRAY:	return ("PREINIT_ARRAY");
		case SHT_GNU_HASH:		return ("GNU_HASH");
		case SHT_GROUP:		return ("GROUP");
		case SHT_SYMTAB_SHNDX:	return ("SYMTAB SECTION INDICIES");
		case SHT_GNU_verdef:	return ("VERDEF");
		case SHT_GNU_verneed:	return ("VERNEED");
		case SHT_GNU_versym:	return ("VERSYM");
		case 0x6ffffff0:		return ("VERSYM");
		case 0x6ffffffc:		return ("VERDEF");
		case 0x7ffffffd:		return ("AUXILIARY");
		case 0x7fffffff:		return ("FILTER");
		case 0x6ffffff1:		return ("LOOS+ffffff1");
		case 0x6ffffff3:		return ("LOOS+ffffff3");
		case SHT_GNU_LIBLIST:	return ("GNU_LIBLIST");
		default:
			sprintf(buf, "%08x: <unknown>", sh_type);
		return (buf);
	}
}


/**
 * get_sec_flags - translates section flags to string
 * @h: pointer to h struct
 * @i: the section index
 * Return: legend-based string rep of flag
 */
char *get_sec_flags(header *h, size_t i)
{
	static char buf[32];
	unsigned long flags = 0;
	char *p = buf;

	if (h->e64.e_ident[EI_DATA] == ELFDATA2MSB)
		flags = h->s32[i].sh_flags;
	else
		flags = h->s64[i].sh_flags;

	if (flags & SHF_WRITE)
		*p++ = 'W';
	if (flags & SHF_ALLOC)
		*p++ = 'A';
	if (flags & SHF_EXECINSTR)
		*p++ = 'X';
	if (flags & SHF_MERGE)
		*p++ = 'M';
	if (flags & SHF_STRINGS)
		*p++ = 'S';
	if (flags & SHF_INFO_LINK)
		*p++ = 'I';
	if (flags & SHF_LINK_ORDER)
		*p++ = 'L';
	if (flags & SHF_OS_NONCONFORMING)
		*p++ = 'O';
	if (flags & SHF_GROUP)
		*p++ = 'G';
	if (flags & SHF_TLS)
		*p++ = 'T';
	if (flags & SHF_EXCLUDE)
		*p++ = 'E';
	*p = 0;
	return (buf);
}


/**
 * print_section32 - prints 32 bit section hs
 * @h: pointer to h struct
 * @strings: the string section
 */
void print_section32(header *h, char *strings)
{
	size_t i = 0;

	printf("%s", TITLE_32);
	for (i = 0; i < GETE(e_shnum); i++)
	{
		printf(FORMAT_32,
			(unsigned int)i,
			strings + GETS(i, sh_name),
			get_sec_type(GETS(i, sh_type)),
			GETS(i, sh_addr),
			GETS(i, sh_offset),
			GETS(i, sh_size),
			GETS(i, sh_entsize),
			get_sec_flags(h, i),
		    GETS(i, sh_link),
		    GETS(i, sh_info),
		    GETS(i, sh_addralign));
	}
}

/**
 * print_section64 - prints 64 bit section hs
 * @h: pointer to h struct
 * @strings: the string section
 */
void print_section64(header *h, char *strings)
{
	size_t i = 0;

	printf("%s", TITLE_64);
	for (i = 0; i < GETE(e_shnum); i++)
	{
		printf(FORMAT_64,
			(unsigned int)i,
			strings + GETS(i, sh_name),
			get_sec_type(GETS(i, sh_type)),
			GETS(i, sh_addr),
			GETS(i, sh_offset),
			GETS(i, sh_size),
			GETS(i, sh_entsize),
			get_sec_flags(h, i),
		    GETS(i, sh_link),
		    GETS(i, sh_info),
		    GETS(i, sh_addralign));
	}
}
