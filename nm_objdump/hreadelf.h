#ifndef HREADELF_H
#define HREADELF_H

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


#define GETE(x) \
	(h->e64.e_ident[EI_CLASS] == ELFCLASS32  ? h->e32.x : h->e64.x)
#define GETS(i, x) \
	(h->e64.e_ident[EI_CLASS] == ELFCLASS32 ? h->s32[i].x : h->s64[i].x)
#define GETP(i, x) \
	(h->e64.e_ident[EI_CLASS] == ELFCLASS32 ? h->p32[i].x : h->p64[i].x)

/**
 * struct header - struct containing 32 and 64 bit ELF header information
 * @e32: 32-bit ELF header
 * @e64: 64-bit ELF header
 * @s32: 32-bit ELF section header
 * @s64: 64-bit ELF section header
 * @p64: 64-bit ELF program array
 * @p32: 32-bit ELF program array
 * @sym64: 64-bit struct symbol array
 * @sym32: 32-bit struct symbol array
 */
typedef struct header
{
	Elf64_Ehdr e64;
	Elf32_Ehdr e32;
	Elf64_Shdr *s64;
	Elf32_Shdr *s32;
	Elf64_Phdr *p64;
	Elf32_Phdr *p32;
	Elf64_Sym *sym64;
	Elf32_Sym *sym32;

} header;


unsigned short switch_2bt_end(unsigned short n);
unsigned int switch_4bt_end(unsigned int n);
unsigned long switch_8bt_end(unsigned long n);
void switch_endians(header *h);
void switch_end_sec(header *h, size_t i);

void switch_endians_symbol(header *h, size_t i);

void *read_data(header *h, int fd, unsigned long offset, long size);

char *get_file_format(header *h);

int print_all_symbol_tables(header *h, int fd, size_t *num_printed);
size_t print_symbol_table(header *h, int fd, size_t i,
	char *string_table);
size_t print_symbol_table32(header *h, char *string_table,
	char *sym_string_table, int section);
size_t print_symbol_table64(header *h, char *string_table,
	char *sym_string_table, int section);

char *read_string_table(header *h, int fd);
void read_section_headers(header *h, int fd);
void read_symbol_table(header *h, int fd, int i);
char *read_symbol_string_table(header *h, int fd, int i);
void *read_data(header *h, int fd, unsigned long offset, long size);
void header_print(header *h, char *string_table);

char symbol_type2(Elf32_Sym sym, Elf32_Shdr *shdr);
char symbol_type4(Elf64_Sym sym, Elf64_Shdr *shdr);



#endif
