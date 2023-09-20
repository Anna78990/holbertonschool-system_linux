#include "hreadelf.h"

/**
 * switch_2bt_end - switches endianness on 2 byte
 * @n: number to switch
 * Return: switched bytes
 */
unsigned short switch_2bt_end(unsigned short n)
{
	return (((n >> 8)  & 0x00ff) | ((n << 8)  & 0xff00));
}

/**
 * switch_4bt_end - switches endianness on 4 byte
 * @n: number to switch
 * Return: switched bytes
 */
unsigned int switch_4bt_end(unsigned int n)
{
	return (((n >> 24) & 0x000000ff) | ((n >> 8)  & 0x0000ff00) |
		((n << 8)  & 0x00ff0000) | ((n << 24) & 0xff000000));
}

/**
 * switch_4bt_end - switches endianness on 8 bytes
 * @n: number to switch
 * Return: switched bytes
 */
unsigned long switch_8bt_end(unsigned long n)
{
	return (((n >> 56) & 0x00000000000000ff) |
		((n >> 40) & 0x000000000000ff00) |
		((n >> 24) & 0x0000000000ff0000) |
		((n >> 8)  & 0x00000000ff000000) |
		((n << 8)  & 0x000000ff00000000) |
		((n << 24) & 0x0000ff0000000000) |
		((n << 40) & 0x00ff000000000000) |
		((n << 56) & 0xff00000000000000));
}

/**
 * switch_endians_32 - switches endians
 * @header: ELF headerb to switch
 */
void switch_all_endians_32(Elf32_Ehdr *header)
{
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		header.e_machine = switch_2bt_end(header.e_machine);
		header.e_version = switch_4bt_end(header.e_version);
		header.e_type = switch_2bt_end(header.e_type);
		header.e_flags = switch_4bt_end(header.e_flags);
		header.e_ehsize = switch_2bt_end(header.e_ehsize);
		header.e_phentsize = switch_2bt_end(header.e_phentsize);
		header.e_phnum = switch_2bt_end(header.e_phnum);
		header.e_shentsize = switch_2bt_end(header.e_shentsize);
		header.e_shnum = switch_2bt_end(header.e_shnum);
		header.e_shoff = switch_4bt_end(header.e_shoff);
		header.e_phoff = switch_4bt_end(header.e_phoff);
		header.e_entry = switch_4bt_end(header.e_entry);
		header.e_shstrndx = switch_2bt_end(header.e_shstrndx);
	}
}


/**
 * switch_endians_64 - switches endians
 * @header: ELF headerb to switch
 */
void switch_all_endians_64(Elf64_Ehdr *header)
{
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		header.e_machine = switch_2bt_end(header.e_machine);
		header.e_version = switch_4bt_end(header.e_version);
		header.e_type = switch_2bt_end(header.e_type);
		header.e_flags = switch_4bt_end(header.e_flags);
		header.e_ehsize = switch_2bt_end(header.e_ehsize);
		header.e_phentsize = switch_2bt_end(header.e_phentsize);
		header.e_phnum = switch_2bt_end(header.e_phnum);
		header.e_shentsize = switch_2bt_end(header.e_shentsize);
		header.e_shnum = switch_2bt_end(header.e_shnum);
		header.e_shoff = switch_8bt_end(header.e_shoff);
		header.e_phoff = switch_8bt_end(header.e_phoff);
		header.e_entry = switch_8bt_end(header.e_entry);
		header.e_shstrndx = switch_2bt_end(header.e_shstrndx);
	}
}
