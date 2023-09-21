#include "hreadelf.h"



/**
 * print_flags - prints the flags
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
void print_flags(header *header)
{
	printf("  Flags:                             0x");
	/* endianness */
	if (header->e64.e_ident[EI_CLASS] == ELFCLASS32)
		printf("%lx", (unsigned long)header->e32.e_flags);
	else
		printf("%lx", (unsigned long)header->e64.e_flags);
	printf("\n");

	printf("  Size of this header:               %ld (bytes)\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		(long)header->e32.e_ehsize : (long)header->e64.e_ehsize);

	printf("  Size of program headers:           %ld (bytes)\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		(long)header->e32.e_phentsize
		: (long)header->e64.e_phentsize);

	printf("  Number of program headers:         %ld\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		(long)header->e32.e_phnum : (long)header->e64.e_phnum);
	printf("  Size of section headers:           %ld (bytes)\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		(long)header->e32.e_shentsize
		: (long)header->e64.e_shentsize);
	printf("  Number of section headers:         %ld\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		(long)header->e32.e_shnum : (long)header->e64.e_shnum);
	printf("  Section header string table index: %ld\n",
		(header->e64.e_ident[EI_CLASS] == ELFCLASS32) ?
		(long)header->e32.e_shstrndx : (long)header->e64.e_shstrndx);
}

void print_machine3(header *header)
{
        switch (header->e64.e_machine)
	{
		case EM_PRISM: printf("Vitesse Prism");
		case EM_X86_64: printf("Advanced Micro Devices X86-64");
		case EM_S390: printf("IBM S/390");
		case EM_XTENSA: printf("Tensilica Xtensa Processor");
		default: printf("<unknown>: 0x%x", header->e64.e_machine);
	}
}

/**
 * get_machine2 - gets the target machine type string
 * @elf_header: address of elf header struct
 * Return: the string or NULL
 */
void print_machine2(header *header)
{
	switch (header->e64.e_machine)
	{
		case EM_ALPHA: printf("Alpha");
		case EM_D10V: printf("d10v");
		case EM_D30V: printf("d30v");
		case EM_M32R: printf("Renesas M32R (formerly Mitsubishi M32r)");
		case EM_V800: printf("Renesas V850 (using RH850 ABI)");
		case EM_V850: printf("Renesas V850");
		case EM_MN10300: printf("mn10300");
		case EM_MN10200: printf("mn10200");
		case EM_FR30: printf("Fujitsu FR30");
		case EM_PJ: printf("picoJava");
		case EM_MMA: printf("Fujitsu Multimedia Accelerator");
		case EM_PCP: printf("Siemens PCP");
		case EM_NCPU: printf("Sony nCPU embedded RISC processor");
		case EM_NDR1: printf("Denso NDR1 microprocesspr");
		case EM_STARCORE: printf("Motorola Star*Core processor");
		case EM_ME16: printf("Toyota ME16 processor");
		case EM_ST100: printf("STMicroelectronics ST100 processor");
		case EM_TINYJ: printf("Advanced Logic Corp. TinyJ embedded processor");
		case EM_PDSP: printf("Sony DSP processor");
		case EM_FX66: printf("Siemens FX66 microcontroller");
		case EM_ST9PLUS: printf("STMicroelectronics ST9+ 8/16 bit microcontroller");
		case EM_ST7: printf("STMicroelectronics ST7 8-bit microcontroller");
		case EM_68HC16: printf("Motorola MC68HC16 Microcontroller");
		case EM_68HC12: printf("Motorola MC68HC12 Microcontroller");
		case EM_68HC11: printf("Motorola MC68HC11 Microcontroller");
		case EM_68HC08: printf("Motorola MC68HC08 Microcontroller");
		case EM_68HC05: printf("Motorola MC68HC05 Microcontroller");
		case EM_SVX: printf("Silicon Graphics SVx");
		case EM_ST19: printf("STMicroelectronics ST19 8-bit microcontroller");
		case EM_VAX: printf("Digital VAX");
		case EM_AVR: printf("Atmel AVR 8-bit microcontroller");
		case EM_CRIS: printf("Axis Communications 32-bit embedded processor");
		case EM_JAVELIN: printf("Infineon Technologies 32-bit embedded cpu");
		case EM_FIREPATH: printf("Element 14 64-bit DSP processor");
		case EM_ZSP: printf("LSI Logic's 16-bit DSP processor");
		case EM_MMIX: printf("Donald Knuth's educational 64-bit processor");
		case EM_HUANY:
			printf("Harvard Universitys's machine-independent object format");
		default: print_machine3(header);
	}
}

/**
 * get_machine - gets the target machine type string
 * @elf_header: address of elf header struct
 * Return: the string or NULL
 */
void print_machine(header *header)
{
	printf("  Machine:                           ");
	switch (header->e64.e_machine)
	{
		case EM_NONE: printf("None");
		case EM_AARCH64: printf("AArch64");
		case EM_M32: printf("WE32100");
		case EM_SPARC: printf("Sparc");
		case EM_386: printf("Intel 80386");
		case EM_68K: printf("MC68000");
		case EM_88K: printf("MC88000");
		case EM_860: printf("Intel 80860");
		case EM_MIPS: printf("MIPS R3000");
		case EM_S370: printf("IBM System/370");
		case EM_MIPS_RS3_LE: printf("MIPS R4000 big-endian");
		case EM_PARISC: printf("HPPA");
		case EM_SPARC32PLUS: printf("Sparc v8+");
		case EM_960: printf("Intel 90860");
		case EM_PPC: printf("PowerPC");
		case EM_PPC64: printf("PowerPC64");
		case EM_FR20: printf("Fujitsu FR20");
		case EM_RH32: printf("TRW RH32");
		case EM_ARM: printf("ARM");
		case EM_SH: printf("Renesas / SuperH SH");
		case EM_SPARCV9: printf("Sparc v9");
		case EM_TRICORE: printf("Siemens Tricore");
		case EM_ARC: printf("ARC");
		case EM_H8_300: printf("Renesas H8/300");
		case EM_H8_300H: printf("Renesas H8/300H");
		case EM_H8S: printf("Renesas H8S");
		case EM_H8_500: printf("Renesas H8/500");
		case EM_IA_64: printf("Intel IA-64");
		case EM_MIPS_X: printf("Stanford MIPS-X");
		case EM_COLDFIRE: printf("Motorola Coldfire");
		default: print_machine2(header);
	}
	printf("\n");
}



/**
 * get_type - gets the ELF file type
 * @elf_header: the internal header
 * Return: string file type
 */
void print_type(header *header)
{
	printf("  Type:                              ");
	switch ((header->e64.e_ident[EI_CLASS] == ELFCLASS64) ?
			header->e32.e_type : header->e64.e_type)
	{
		case ET_NONE:
			printf("NONE (None)");
			break;
		case ET_REL:
			printf("REL (Relocatable file)");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)");
                        break;
		case ET_DYN:
			printf("DYN (Shared object file)");
                        break;
		case ET_CORE:
			printf("CORE (Core file)");
                        break;
		default:
			printf("<unknown>: %x",
				(header->e64.e_ident[EI_CLASS] == ELFCLASS64) ?
				header->e32.e_type : header->e64.e_type);
	}
	printf("\n");
}
