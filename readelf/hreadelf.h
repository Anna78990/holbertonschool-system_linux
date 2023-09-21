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
	Elf32_Shdr s32;
	Elf64_Shdr s64;
} header;


int print_version(header *header);
void print_flags(header *header);
void print_machine(header *header);
void print_type(header *header);
int print_header(header *header);

void switch_endians(header *header);

#endif
