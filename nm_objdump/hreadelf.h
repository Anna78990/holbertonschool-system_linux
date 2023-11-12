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

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define USAGE "hnm elf_filename\n"

#define ERR_PREFIX "%s: "
#define ERR_NO_ENTRY ERR_PREFIX \
	"'%s': No such file\n"
#define ERR_NO_ACCESS ERR_PREFIX \
	"%s: Permission denied\n"
#define ERR_NOT_MAGIC ERR_PREFIX \
	"File format not recognized\n"

#define IS_32(x) ((x).e_ident[EI_CLASS] == ELFCLASS32)
#define IS_64 ((elf_header->e64).e_ident[EI_CLASS] == ELFCLASS64)
#define IS_BE(x) ((x).e_ident[EI_DATA] == ELFDATA2MSB)
#define EGET(x) \
	(IS_32(elf_header->e64) ? elf_header->e32.x : elf_header->e64.x)
#define SGET(i, x) \
	(IS_32(elf_header->e64) ? elf_header->s32[i].x : elf_header->s64[i].x)
#define PGET(i, x) \
	(IS_32(elf_header->e64) ? elf_header->p32[i].x : elf_header->p64[i].x)
#define YGET(i, x) \
	(IS_32(elf_header->e64) ? elf_header->sym32[i].x : elf_header->sym64[i].x)

#define BFD_NO_FLAGS	0x00
#define HAS_RELOC	0x01
#define EXEC_P		0x02
#define HAS_LINENO	0x04
#define HAS_DEBUG	0x08
#define HAS_SYMS	0x10
#define HAS_LOCALS	0x20
#define DYNAMIC		0x40
#define WP_TEXT		0x80
#define D_PAGED		0x100

/**
 * struct Elf - stores 32/64 structs and other data
 * @e64: the 64 bit struct
 * @e32: the 32 bit struct
 * @s64: the 64 bit struct section array
 * @s32: the 32 bit struct section array
 * @p64: the 64 bit struct program array
 * @p32: the 32 bit struct program array
 * @sym64: the 64 bit struct symbol array
 * @sym32: the 32 bit struct symbol array
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
void switch_endians(header *elf_header);
void switch_end_sec(header *h, size_t i);

void switch_endians_symbol(header *h, size_t i);

/* print_header_1.c */
int print_header(header *elf_header);
int print_magic(Elf64_Ehdr *elf_header);
int print_class(Elf64_Ehdr *elf_header);
int print_data(Elf64_Ehdr *elf_header);
int print_version(Elf64_Ehdr *elf_header);

/* print_header_2.c */
int print_osabi(Elf64_Ehdr *elf_header);
int print_osabi_more(Elf64_Ehdr *elf_header);
int print_abiversion(Elf64_Ehdr *elf_header);
int print_type(header *elf_header);
int print_entry(header *elf_header);

/* print_header_3.c */
int print_machine(Elf64_Ehdr *elf_header);
int print_e_version(header *elf_header);
int print_program_headers(header *elf_header);
char *get_machine(Elf64_Ehdr *elf_header);
char *get_machine2(Elf64_Ehdr *elf_header);

/* print_header_4.c */
int print_section_headers(header *elf_header);
int print_flags(header *elf_header);

/* print_sections_1.c */
int print_section_headers_full(header *elf_header, int fd);
void read_section_headers(header *elf_header, int fd);
char *read_string_table(header *elf_header, int fd);
char *get_section_type(unsigned int sh_type);


/* print_programs1.c */
int print_program_headers_full(header *elf_header, int fd);
void print_program_headers32(header *elf_header, char *string_table, int fd);
void print_program_headers64(header *elf_header, char *string_table, int fd);
void read_program_headers(header *elf_header, int fd);
char *get_segment_type(unsigned long p_type);

/* print_programs2.c */
int print_section_to_segment_mapping(header *elf_header, char *string_table);

/* print_symbols1.c */
int print_all_symbol_tables(header *elf_header, int fd, size_t *num_printed);
size_t print_symbol_table(header *elf_header, int fd, size_t i,
	char *string_table);
size_t print_symbol_table32(header *elf_header,
	char *sym_string_table, int section);
size_t print_symbol_table64(header *elf_header, char *string_table,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed,
	size_t verneed_size, int section);
void print_verneed_info(header *elf_header, char *sym_string_table,
	uint16_t *versym, Elf64_Verneed *verneed, size_t verneed_size, size_t i,
	size_t size, int section);

/* print_symbols2.c */
void read_symbol_table(header *elf_header, int fd, int i);
char *read_symbol_string_table(header *elf_header, int fd, int i);
size_t find_verneed_index(Elf64_Verneed *verneed, size_t verneed_size,
	size_t index);
void print_verneed_table(header *elf_header, int fd, int i,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed);
void *read_data(header *elf_header, int fd, unsigned long offset, long size);

/* print_symbols3.c */
char *get_sym_type(header *elf_header, size_t i);
char *get_sym_bind(header *elf_header, size_t i);
char *get_sym_visibility(header *elf_header, size_t i);
char get_nm_type32(Elf32_Sym sym, Elf32_Shdr *shdr);
char get_nm_type64(Elf64_Sym sym, Elf64_Shdr *shdr);

/* hnm.c */
int process_file(char *file_name, int multiple, char **argv);

/* hobjdump_1.c */
int dump_all_sections(header *elf_header, int fd, size_t *num_printed);
size_t dump_section(header *elf_header, int fd, size_t i,
	char *string_table);

/* hobjdump_2.c */
char *get_file_format(header *elf_header);
void print_f_header(header *elf_header, char *string_table);
int has_section(header *elf_header, char *string_table, char *section_name);
void print_f_flags(unsigned long flags);

#endif
