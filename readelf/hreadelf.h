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

#define GETP(i, x) \
	((h->e64.e_ident[EI_CLASS] == ELFCLASS32) ? h->p32[i].x : h->p64[i].x)

#define TITLE_P32 \
	"  Type           Offset   VirtAddr   PhysAddr   FileSiz" \
	" MemSiz  Flg Align\n"

#define TITLE_P64 \
	"  Type           Offset   VirtAddr           PhysAddr " \
	"          FileSiz  MemSiz   Flg Align\n"

#define ELF_SECTION_SIZE(sec_hdr, segment)			\
	(((sec_hdr->sh_flags & SHF_TLS) == 0				\
	|| sec_hdr->sh_type != SHT_NOBITS				\
	|| segment->p_type == PT_TLS) ? sec_hdr->sh_size : 0)

#define IS_IN_SEG(sec_hdr, segment)			\
	(((((sec_hdr->sh_flags & SHF_TLS) != 0)				\
	&& (segment->p_type == PT_TLS					\
	 || segment->p_type == PT_LOAD))				\
	|| ((sec_hdr->sh_flags & SHF_TLS) == 0				\
	&& segment->p_type != PT_TLS))					\
	&& (sec_hdr->sh_type == SHT_NOBITS					\
	|| (sec_hdr->sh_offset >= segment->p_offset		\
	   && (sec_hdr->sh_offset + ELF_SECTION_SIZE(sec_hdr, segment)	\
	       <= segment->p_offset + segment->p_filesz)))		\
	&& ((sec_hdr->sh_flags & SHF_ALLOC) == 0				\
	|| (sec_hdr->sh_addr >= segment->p_vaddr				\
	   && (sec_hdr->sh_addr + ELF_SECTION_SIZE(sec_hdr, segment)	\
	       <= segment->p_vaddr + segment->p_memsz))))

#define IS_IN_SEG_MEM(sec_hdr, segment)	\
	(ELF_SECTION_SIZE(sec_hdr, segment) > 0			\
	&& IS_IN_SEG(sec_hdr, segment))

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
	Elf64_Phdr *p64;
	Elf32_Phdr *p32;
} header;

char *get_e_type(header *h);

int print_version(header *header);
void print_flags(header *header);
void print_machine(header *header);
void print_type(header *header);
int print_header(header *header);

unsigned short switch_2bt_end(unsigned short n);
unsigned int switch_4bt_end(unsigned int n);
unsigned long switch_8bt_end(unsigned long n);

void switch_endians(header *header);
void switch_end_sec(header *header, size_t i);

void print_section32(header *header, char *strings);
void print_section64(header *header, char *strings);

void read_section_headers(header *h, int fd);
int print_section_headers(header *h, int fd);

int print_sec_to_seg(header *h, char *str);
char *read_strings(header *h, int fd);
int print_program(header *h, int fd);


#endif
