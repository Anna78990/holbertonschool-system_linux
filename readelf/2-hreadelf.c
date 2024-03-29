#include "hreadelf.h"

#define NO_HEADER "\nThere are no program headers in this file.\n"

/**
 * check_magic - checks if header matches magic bytes
 * @header: elf header
 * Return: 0 if it is ELF else 1
 */
int check_magic(char *header)
{
	if (header[0] == 0x7f && header[1] == 0x45 &&
		header[2] == 0x4c && header[3] == 0x46)
		return (0);
	return (1);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success or 1+ on error
 */
int main(int argc, char **argv)
{
	int fd;
	size_t r;
	header h;

	memset(&h, 0, sizeof(h));
	if (argc != 2)
		return (EXIT_FAILURE);
	fd = open(argv[1], 0);
	if (fd == -1)
		return (EXIT_FAILURE);
	r = read(fd, &h.e64, sizeof(h.e64));
	if (r != sizeof(h.e64))
	{
		return (EXIT_FAILURE);
	}
	else
	{
		if (h.e64.e_ident[EI_CLASS] == ELFCLASS32)
		{
			lseek(fd, 0, SEEK_SET);
			r = read(fd, &h.e32, sizeof(h.e32));
			if (r != sizeof(h.e32) || check_magic((char *)&h.e32))
				return (EXIT_FAILURE);
		}
		if ((h.e64.e_ident[EI_CLASS] == ELFCLASS32) ?
			h.e32.e_phoff == 0 :
			h.e64.e_phoff == 0)
		{
			printf(NO_HEADER);
			return (0);
		}
		switch_endians(&h);
		print_program(&h, fd);
	}
	free(h.s32);
	free(h.s64);
	free(h.p32);
	free(h.p64);
	close(fd);
	return (0);
}
