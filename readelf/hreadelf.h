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


void switch_all_endians_32(Elf32_Ehdr *header);
void switch_all_endians_64(Elf64_Ehdr *header);

#endif
