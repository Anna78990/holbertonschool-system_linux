#include "hreadelf.h"

#define PROGRAM_TITLE \
	"\nElf file type is %s\n" \
	"Entry point 0x%lx\nThere are %d program headers," \
	" starting at offset %lu\n"

#define FORMAT_PROGRAM_32 \
	"  %-14s 0x%6.6lx 0x%8.8lx 0x%8.8lx 0x%5.5lx 0x%5.5lx %c%c%c %#lx\n"


#define FORMAT_PROGRAM_64 \
	"  %-14s 0x%6.6lx 0x%16.16lx 0x%16.16lx 0x%6.6lx 0x%6.6lx %c%c%c %#lx\n"

#define FSCAN_F \
	"      [Requesting program interpreter: %s]\n"

/**
 * get_segment_type - get string represenation of segment type
 * @p_type: the p_type of this segment
 * Return: string representation of p_type
 */
char *get_segment_type(unsigned long p_type)
{
	switch (p_type)
	{
		case PT_NULL:	return ("NULL");
		case PT_LOAD:	return ("LOAD");
		case PT_DYNAMIC:	return ("DYNAMIC");
		case PT_INTERP:	return ("INTERP");
		case PT_NOTE:	return ("NOTE");
		case PT_SHLIB:	return ("SHLIB");
		case PT_PHDR:	return ("PHDR");
		case PT_TLS:	return ("TLS");
		case PT_GNU_EH_FRAME:	return ("GNU_EH_FRAME");
		case PT_GNU_STACK:	return ("GNU_STACK");
		case PT_GNU_RELRO:  return ("GNU_RELRO");
		case 0x6464E550:	return ("LOOS+464e550");
		default:	return ("UNKNOWN");
	}
}

/**
 * print_program32 - prints 32 bit program headers
 * @h: pointer to header struct
 * @strings: the string table program
 * @fd: file descriptor of ELF file
 */
void print_program32(header *h, char *strings, int fd)
{
	size_t i = 0;
	FILE *file;
	char format[32], prog[PATH_MAX];

	printf(TITLE_P32);
	for (i = 0; i < GETE(e_phnum); i++)
	{
		printf(FORMAT_PROGRAM_32,
			get_segment_type(GETP(i, p_type)),
			GETP(i, p_offset),
			GETP(i, p_vaddr),
			GETP(i, p_paddr),
			GETP(i, p_filesz),
			GETP(i, p_memsz),
			GETP(i, p_flags) & PF_R ? 'R' : ' ',
			GETP(i, p_flags) & PF_W ? 'W' : ' ',
			GETP(i, p_flags) & PF_X ? 'E' : ' ',
			GETP(i, p_align));
		switch (GETP(i, p_type))
		{
			case PT_INTERP:
			{
				file = fdopen(fd, "r");

				snprintf(format, sizeof(format), "%%%ds", PATH_MAX);
				lseek(fd, GETP(i, p_offset), SEEK_SET);
				if (fscanf(file, format, prog) > 0)
					printf(FSCAN_F, prog);
				fclose(file);
			}
		}
	}
	(void)strings;
}

/**
 * print_program64 - prints 64 bit program headers
 * @h: pointer to header struct
 * @strings: the string table program
 * @fd: file descriptor of ELF file
 */
void print_program64(header *h, char *strings, int fd)
{
	size_t i = 0;
	char format[32], prog[PATH_MAX];
	FILE *file;

	printf(TITLE_P64);
	for (i = 0; i < GETE(e_phnum); i++)
	{
		printf(FORMAT_PROGRAM_64,
			get_segment_type(GETP(i, p_type)),
			GETP(i, p_offset),
			GETP(i, p_vaddr),
			GETP(i, p_paddr),
			GETP(i, p_filesz),
			GETP(i, p_memsz),
			GETP(i, p_flags) & PF_R ? 'R' : ' ',
			GETP(i, p_flags) & PF_W ? 'W' : ' ',
			GETP(i, p_flags) & PF_X ? 'E' : ' ',
			GETP(i, p_align));
		switch (GETP(i, p_type))
		{
			case PT_INTERP:
			{
				file = fdopen(fd, "r");

				snprintf(format, sizeof(format), "%%%ds", PATH_MAX);
				lseek(fd, GETP(i, p_offset), SEEK_SET);
				if (fscanf(file, format, prog) > 0)
					printf(FSCAN_F, prog);
				fclose(file);
			}
		}
	}
	(void)strings;
}


/**
 * switch_end_pro - switches endians of the given header
 * @h: pointer to header struct
 * @i: index of this section
 */
void switch_end_pro(header *h, size_t i)
{
	if (h->e64.e_ident[EI_DATA] == ELFDATA2MSB &&
			h->e64.e_ident[EI_CLASS] == ELFCLASS64)
	{
		h->p64[i].p_type = switch_4bt_end(h->p64[i].p_type);
		h->p64[i].p_offset = switch_8bt_end(h->p64[i].p_offset);
		h->p64[i].p_vaddr = switch_8bt_end(h->p64[i].p_vaddr);
		h->p64[i].p_paddr = switch_8bt_end(h->p64[i].p_paddr);
		h->p64[i].p_filesz = switch_8bt_end(h->p64[i].p_filesz);
		h->p64[i].p_memsz = switch_8bt_end(h->p64[i].p_memsz);
		h->p64[i].p_align = switch_8bt_end(h->p64[i].p_align);
		h->p64[i].p_flags = switch_4bt_end(h->p64[i].p_flags);
	}
	if (h->e64.e_ident[EI_DATA] == ELFDATA2MSB &&
			h->e64.e_ident[EI_CLASS] == ELFCLASS32)
	{
		h->p32[i].p_type = switch_4bt_end(h->p32[i].p_type);
		h->p32[i].p_offset = switch_4bt_end(h->p32[i].p_offset);
		h->p32[i].p_vaddr = switch_4bt_end(h->p32[i].p_vaddr);
		h->p32[i].p_paddr = switch_4bt_end(h->p32[i].p_paddr);
		h->p32[i].p_filesz = switch_4bt_end(h->p32[i].p_filesz);
		h->p32[i].p_memsz = switch_4bt_end(h->p32[i].p_memsz);
		h->p32[i].p_align = switch_4bt_end(h->p32[i].p_align);
		h->p32[i].p_flags = switch_4bt_end(h->p32[i].p_flags);
	}
}

/**
 * print_program - prints all the ELF PROGRAM headers
 * @h: pointer to header struct
 * @fd: the file descriptor of ELF file
 * Return: 0 on success otherwise 1
 */
int print_program(header *h, int fd)
{
	char *strings, *headers;
	size_t i, j = GETE(e_phnum), r;
	size_t read_size = GETE(e_phentsize) * GETE(e_phnum);

	if (!GETE(e_phnum))
	{
		return (1);
	}
	printf(PROGRAM_TITLE, get_e_type(h), GETE(e_entry),
		GETE(e_phnum), GETE(e_phoff));

	read_section_headers(h, fd);
	if (!j)
		return (0);
	headers = calloc(j, read_size * j);
	if (!headers)
		exit(1);
	lseek(fd, GETE(e_phoff), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
		exit(1);
	if (h->e64.e_ident[EI_CLASS] == ELFCLASS32)
		h->p32 = (void *)headers;
	else
		h->p64 = (void *)headers;

	for (i = 0; i < GETE(e_shnum); i++)
		switch_end_sec(h, i);
	for (i = 0; i < GETE(e_phnum); i++)
		switch_end_pro(h, i);
	strings = read_strings(h, fd);
	printf("\nProgram Headers:\n");
	if (h->e64.e_ident[EI_CLASS] == ELFCLASS32)
		print_program32(h, strings, fd);
	else
		print_program64(h, strings, fd);
	print_sec_to_seg(h, strings);
	free(strings);
	return (0);
}
