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


#define ERR_PREFIX "%s: "
#define ERR_NO_ENTRY ERR_PREFIX \
	"'%s': No such file\n"
#define ERR_NO_ACCESS ERR_PREFIX \
	"%s: Permission denied\n"
#define ERR_NOT_MAGIC ERR_PREFIX \
	"File format not recognized\n"

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

/* print_header_1.c */
int print_header(header *h);
int print_magic(Elf64_Ehdr *h);
int print_class(Elf64_Ehdr *h);
int print_data(Elf64_Ehdr *h);
int print_version(Elf64_Ehdr *h);

/* print_header_2.c */
int print_osabi(Elf64_Ehdr *h);
int print_osabi_more(Elf64_Ehdr *h);
int print_abiversion(Elf64_Ehdr *h);
int print_type(header *h);
int print_entry(header *h);

/* print_header_3.c */
int print_machine(Elf64_Ehdr *h);
int print_e_version(header *h);
int print_program_headers(header *h);
char *get_machine(Elf64_Ehdr *h);
char *get_machine2(Elf64_Ehdr *h);

/* print_header_4.c */
int print_section_headers(header *h);
int print_flags(header *h);

/* print_sections_1.c */
void read_section_headers(header *h, int fd);
char *read_string_table(header *h, int fd);
char *get_section_type(unsigned int sh_type);


int print_program_headers_full(header *h, int fd);
void read_program_headers(header *h, int fd);
char *get_segment_type(unsigned long p_type);

/* print_programs2.c */
int print_section_to_segment_mapping(header *h, char *string_table);

/* print_symbols1.c */
int print_all_symbol_tables(header *h, int fd, size_t *num_printed);
size_t print_symbol_table(header *h, int fd, size_t i,
	char *string_table);
size_t print_symbol_table32(header *elf_header, char *string_table,
	char *sym_string_table, int section);
size_t print_symbol_table64(header *elf_header, char *string_table,
	char *sym_string_table, int section);
/* print_symbols2.c */
void read_symbol_table(header *h, int fd, int i);
char *read_symbol_string_table(header *h, int fd, int i);
size_t find_verneed_index(Elf64_Verneed *verneed, size_t verneed_size,
	size_t index);
void print_verneed_table(header *h, int fd, int i,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed);
void *read_data(header *h, int fd, unsigned long offset, long size);

/* print_symbols3.c */
char *get_sym_type(header *h, size_t i);
char *get_sym_bind(header *h, size_t i);
char *get_sym_visibility(header *h, size_t i);
char get_nm_type32(Elf32_Sym sym, Elf32_Shdr *shdr);
char get_nm_type64(Elf64_Sym sym, Elf64_Shdr *shdr);


/* hobjdump_1.c */
int dump_all_sections(header *h, int fd, size_t *num_printed);
size_t dump_section(header *h, int fd, size_t i,
	char *string_table);

/* hobjdump_2.c */
char *get_file_format(header *h);
void print_f_header(header *h, char *string_table);
int has_section(header *h, char *string_table, char *section_name);
void print_f_flags(unsigned long flags);

#endif
