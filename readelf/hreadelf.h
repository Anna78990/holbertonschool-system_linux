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
#include <stddef.h>


#define KEY_FLAG \
	"Key to Flags:\n" \
	"  W (write), A (alloc), X (execute), M (merge), S (strings)%s\n" \
	"  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n" \
	"  O (extra OS processing required) o (OS specific), p (processor specific)\n"

#define TITLE_32 \
	"  [Nr] Name              Type            Addr" \
	"     Off    Size   ES Flg Lk Inf Al\n"
#define TITLE_64 \
	"  [Nr] Name              Type            Address" \
	"          Off    Size   ES Flg Lk Inf Al\n"

#define GETE(x) \
	((h->e64.e_ident[EI_CLASS] == ELFCLASS32) ? h->e32.x : h->e64.x)

#define GETS(i, x) \
	((h->e64.e_ident[EI_CLASS] == ELFCLASS32) ? h->s32[i].x : h->s64[i].x)

/**
 * struct header - struct containing 32 and 64 bit ELF header information
 * @e32: 32-bit ELF header
 * @e64: 64-bit ELF header
 * @s32: 32-bit ELF section header
 * @s64: 64-bit ELF section header
 */
typedef struct header
{
	Elf32_Ehdr e32;
	Elf64_Ehdr e64;
	Elf32_Shdr *s32;
	Elf64_Shdr *s64;
} header;


int print_version(header *header);
void print_flags(header *header);
void print_machine(header *header);
void print_type(header *header);
int print_header(header *header);

void switch_endians(header *header);
void switch_end_sec(header *header, size_t i);

void print_section32(header *header, char *strings);
void print_section64(header *header, char *strings);

int print_section_headers(header *h, int fd);

#endif
