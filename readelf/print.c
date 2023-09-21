#include "hreadelf.h"

/**
 * print_osabi_more - prints ELF osabi more
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_osabi_more(header *header)
{
	switch (header->e64.e_ident[EI_OSABI])
	{
		case ELFOSABI_MODESTO:
			printf("Novell - Modesto");
			break;
		case ELFOSABI_OPENBSD:
			printf("UNIX - OpenBSD");
			break;
		case ELFOSABI_STANDALONE:
			printf("Standalone App");
			break;
		case ELFOSABI_ARM:
			printf("ARM");
			break;
		default:
			printf("<unknown: %x>",
				header->e64.e_ident[EI_OSABI]);
			break;
	}
	printf("\n");
	return (0);
}


/**
 * print_osabi - prints to OS ABI version
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_osabi(header *header)
{
	printf("  OS/ABI:                            ");
	switch (header->e64.e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("UNIX - System V");
			break;
		case ELFOSABI_HPUX:
			printf("UNIX - HP-UX");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD");
			break;
		case ELFOSABI_LINUX:
			printf("UNIX - Linux");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris");
			break;
		case ELFOSABI_AIX:
			printf("UNIX - AIX");
			break;
		case ELFOSABI_IRIX:
			printf("UNIX - IRIX");
			break;
		case ELFOSABI_FREEBSD:
			printf("UNIX - FreeBSD");
			break;
		case ELFOSABI_TRU64:
			printf("UNIX - TRU64");
			break;
		default:
			return (print_osabi_more(header));
		break;
	}
	printf("\n");
	return (0);
}


/**
 * print_class - prints the byte architecture class
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_class(header *header)
{
	printf("  Class:                             ");
	switch (header->e64.e_ident[EI_CLASS])
	{
		case ELFCLASS64:
			printf("ELF64");
		break;
		case ELFCLASS32:
			printf("ELF32");
		break;
		case ELFCLASSNONE:
			printf("none");
		break;
		default:
			printf("<unknown: %x>", header->e64.e_ident[EI_CLASS]);
		break;
	}
	printf("\n");
	return (0);
}

/**
 * print_data - prints the endianness type
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_data(header *header)
{
	printf("  Data:                              ");
	switch (header->e64.e_ident[EI_DATA])
	{
		case ELFDATA2LSB:
			printf("2's complement, little endian");
		break;
		case ELFDATA2MSB:
			printf("2's complement, big endian");
		break;
		case ELFDATANONE:
			printf("none");
		break;
		default:
			printf("<unknown: %x>", header->e64.e_ident[EI_DATA]);
		break;
	}
	printf("\n");
	return (0);
}

/**
 * print_version - prints the ELF version
 * @elf_header: address of elf header struct
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
 * print_header - calls all the print functions
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_header(header *header)
{
	size_t i;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%.2x ", header->e64.e_ident[i]);
	printf("\n");
	print_class(header);
	print_data(header);
	printf("  Version:                           %d ",
		header->e64.e_ident[EI_VERSION]);
	if (header->e64.e_ident[EI_VERSION] == EV_CURRENT)
		printf("(current)");
	else if (header->e64.e_ident[EI_VERSION] != EV_NONE)
		printf("<unknown: %x", header->e64.e_ident[EI_VERSION]);
	printf("\n");
	print_osabi(&header);
	printf("  ABI Version:                       %d\n",
			header->e64.e_ident[EI_ABIVERSION]);
	print_type(header);
	print_machine(header);
	printf("  Version:                           0x%lx\n",
			(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
			(unsigned long)header->e32.e_version
			: (unsigned long)header->e64.e_version);
	printf("  Entry point address:               0x%lx\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		header->e32.e_entry : header->e64.e_entry);
	printf("  Start of program headers:          %lu (bytes into file)\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		header->e32.e_phoff : header->e64.e_phoff);	
	printf("  Start of section headers:          %lu (bytes into file)\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		header->e32.e_shoff : header->e64.e_shoff);
	print_flags(header);
	return (0);
}
