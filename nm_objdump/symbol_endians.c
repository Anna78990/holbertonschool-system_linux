#include "hreadelf.h"

/**
 * switch_endians_symbol - switches all endians if need be
 * @header: address of our internal struct
 * @i: index of this section
 */
void switch_endians_symbol(header *header, size_t i)
{
	if ((header->e64.e_ident[EI_DATA] == ELFDATA2MSB) &&
			(header->e64.e_ident[EI_CLASS] != ELFCLASS32))
	{
		header->sym64[i].st_name = switch_4bt_end(header->sym64[i].st_name);
		header->sym64[i].st_shndx = switch_2bt_end(header->sym64[i].st_shndx);
		header->sym64[i].st_value = switch_8bt_end(header->sym64[i].st_value);
		header->sym64[i].st_size = switch_8bt_end(header->sym64[i].st_size);
	}
	if ((header->e64.e_ident[EI_DATA] == ELFDATA2MSB) &&
			(header->e64.e_ident[EI_CLASS] == ELFCLASS32))
	{
		header->sym32[i].st_name = switch_4bt_end(header->sym32[i].st_name);
		header->sym32[i].st_shndx = switch_2bt_end(header->sym32[i].st_shndx);
		header->sym32[i].st_value = switch_4bt_end(header->sym32[i].st_value);
		header->sym32[i].st_size = switch_4bt_end(header->sym32[i].st_size);
	}
}
