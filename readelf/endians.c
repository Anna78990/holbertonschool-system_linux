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
 * switch_8bt_end - switches endianness on 8 bytes
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
 * switch_endians - switches endians
 * @header: ELF headerb to switch
 */
void switch_endians(header *header)
{
	if (header->e64.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		header->e64.e_machine = switch_2bt_end(header->e64.e_machine);
		header->e64.e_version = switch_4bt_end(header->e64.e_version);
		header->e64.e_type = switch_2bt_end(header->e64.e_type);
		header->e64.e_flags = switch_4bt_end(header->e64.e_flags);
		header->e64.e_ehsize = switch_2bt_end(header->e64.e_ehsize);
		header->e64.e_phentsize = switch_2bt_end(header->e64.e_phentsize);
		header->e64.e_phnum = switch_2bt_end(header->e64.e_phnum);
		header->e64.e_shentsize = switch_2bt_end(header->e64.e_shentsize);
		header->e64.e_shnum = switch_2bt_end(header->e64.e_shnum);
		header->e64.e_shoff = switch_8bt_end(header->e64.e_shoff);
		header->e64.e_phoff = switch_8bt_end(header->e64.e_phoff);
		header->e64.e_entry = switch_8bt_end(header->e64.e_entry);
		header->e64.e_shstrndx = switch_2bt_end(header->e64.e_shstrndx);
	}
	if ((header->e64.e_ident[EI_DATA] == ELFDATA2MSB) &&
			(header->e64.e_ident[EI_CLASS] == ELFCLASS32))
	{
		header->e32.e_machine = switch_2bt_end(header->e32.e_machine);
		header->e32.e_version = switch_4bt_end(header->e32.e_version);
		header->e32.e_type = switch_2bt_end(header->e32.e_type);
		header->e32.e_flags = switch_4bt_end(header->e32.e_flags);
		header->e32.e_ehsize = switch_2bt_end(header->e32.e_ehsize);
		header->e32.e_phentsize = switch_2bt_end(header->e32.e_phentsize);
		header->e32.e_phnum = switch_2bt_end(header->e32.e_phnum);
		header->e32.e_shentsize = switch_2bt_end(header->e32.e_shentsize);
		header->e32.e_shnum = switch_2bt_end(header->e32.e_shnum);
		header->e32.e_shoff = switch_4bt_end(header->e32.e_shoff);
		header->e32.e_phoff = switch_4bt_end(header->e32.e_phoff);
		header->e32.e_entry = switch_4bt_end(header->e32.e_entry);
		header->e32.e_shstrndx = switch_2bt_end(header->e32.e_shstrndx);
	}
}


/**
 * switch_end_sec - switches all endians
 * @header: pointer to struct header
 * @i: index of the section
 */
void switch_end_sec(header *header, size_t i)
{
	if (header->e64.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		header->s64[i].sh_name = switch_4bt_end(header->s64[i].sh_name);
		header->s64[i].sh_type = switch_4bt_end(header->s64[i].sh_type);
		header->s64[i].sh_flags =
			switch_8bt_end(header->s64[i].sh_flags);
		header->s64[i].sh_addr = switch_8bt_end(header->s64[i].sh_addr);
		header->s64[i].sh_offset =
			switch_8bt_end(header->s64[i].sh_offset);
		header->s64[i].sh_size = switch_8bt_end(header->s64[i].sh_size);
		header->s64[i].sh_link = switch_4bt_end(header->s64[i].sh_link);
		header->s64[i].sh_info = switch_4bt_end(header->s64[i].sh_info);
		header->s64[i].sh_addralign =
			switch_8bt_end(header->s64[i].sh_addralign);
		header->s64[i].sh_entsize =
			switch_8bt_end(header->s64[i].sh_entsize);
	}
	if ((header->e64.e_ident[EI_DATA] == ELFDATA2MSB) &&
			(header->e64.e_ident[EI_CLASS] == ELFCLASS32))
	{
		header->s32[i].sh_name = switch_4bt_end(header->s32[i].sh_name);
		header->s32[i].sh_type = switch_4bt_end(header->s32[i].sh_type);
		header->s32[i].sh_flags =
			switch_4bt_end(header->s32[i].sh_flags);
		header->s32[i].sh_addr = switch_4bt_end(header->s32[i].sh_addr);
		header->s32[i].sh_offset =
			switch_4bt_end(header->s32[i].sh_offset);
		header->s32[i].sh_size = switch_4bt_end(header->s32[i].sh_size);
		header->s32[i].sh_link = switch_4bt_end(header->s32[i].sh_link);
		header->s32[i].sh_info = switch_4bt_end(header->s32[i].sh_info);
		header->s32[i].sh_addralign =
			switch_4bt_end(header->s32[i].sh_addralign);
		header->s32[i].sh_entsize =
			switch_4bt_end(header->s32[i].sh_entsize);
	}
}
