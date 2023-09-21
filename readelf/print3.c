#include "hreadelf.h"

/**
 * print_version - prints the ELF version
 * @header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_version(header *header)
{
	printf("  Version:                           %d ",
		header->e64.e_ident[EI_VERSION]);
	if (header->e64.e_ident[EI_VERSION] == EV_CURRENT)
		printf("(current)");
	else if (header->e64.e_ident[EI_VERSION] != EV_NONE)
		printf("<unknown: %x", header->e64.e_ident[EI_VERSION]);
	printf("\n");
	return (0);
}

/**
 * get_e_type - gets the file type
 * @header: the internal header
 * Return: string file type
 */
char *get_e_type(header *header)
{
	static char buf[100];

	switch (header->e64.e_ident[EI_CLASS])
	{
		case ELFCLASS32:
			switch (header->e32.e_type)
			{
				case ET_NONE:
					return ("NONE (None)");
				case ET_REL:
					return ("REL (Relocatable file)");
				case ET_EXEC:
					return ("EXEC (Executable file)");
				case ET_DYN:
					return ("DYN (Shared object file)");
				case ET_CORE:
					return ("CORE (Core file)");
				default:
					sprintf(buf, "<unknown>: %x",
							header->e32.e_type);
			}
		case ELFCLASS64:
			switch (header->e64.e_type)
			{
				case ET_NONE:
					return ("NONE (None)");
				case ET_REL:
					return ("REL (Relocatable file)");
				case ET_EXEC:
					return ("EXEC (Executable file)");
				case ET_DYN:
					return ("DYN (Shared object file)");
				case ET_CORE:
					return ("CORE (Core file)");
				default:
					sprintf(buf, "<unknown>: %x",
							header->e64.e_type);
			}
	}
	return (buf);
}

/**
 * print_type - prints the ELF type
 * @header: pointer to header struct
 */
void print_type(header *header)
{
	printf("  Type:                              %s\n",
			get_e_type(header));
}
