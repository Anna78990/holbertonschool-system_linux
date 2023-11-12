#include "hreadelf.h"

/**
 * check_magic - checks if header matches magic bytes
 * @h: 16 byte buffer holding elf header
 * Return: 0 if ELF else 1
 */
int check_magic(char *h)
{
	if (h[0] == 0x7f && h[1] == 0x45 &&
		h[2] == 0x4c && h[3] == 0x46)
		return (0);
	return (1);
}

/**
 * hnm - displays symbols of the given file
 * @filename: name of file to process
 * @argv: the argument
 * Return: 0 on success else 1 on failure
 */
int hnm(char *filename, char *argv)
{
	int fd, exit_status = 0;
	size_t r, num = 0;
	header h;

	memset(&h, 0, sizeof(h));

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);

	r = read(fd, &h.e64, sizeof(h.e64));
	if (r != sizeof(h.e64) || check_magic((char *)&h.e64))
	{
		fprintf(stderr, "%s: %s: File format not recognized\n",
				argv, filename);
		exit_status = EXIT_FAILURE;
	}
	else
	{
		if (h.e64.e_ident[EI_CLASS] == ELFCLASS32)
		{
			lseek(fd, 0, SEEK_SET);
			r = read(fd, &h.e32, sizeof(h.e32));
			if (r != sizeof(h.e32) || check_magic((char *)&h.e32))
			{
				exit_status = fprintf(stderr,
					"%s: File format not recognized\n",
					argv);
				return (EXIT_FAILURE);
			}
		}
		switch_endians(&h);
		exit_status = print_all_symbol_tables(&h, fd, &num);
		if (!num)
			fprintf(stderr, "%s: %s: no symbols\n", argv, filename);
	}
	free(h.s32), free(h.s64), free(h.p32), free(h.p64);
	close(fd);
	return (exit_status);
}

/**
 * main - entry point
 * @ac: argument count
 * @argv: argument vector
 * Return: 0 on success or 1+ on error
 */
int main(int ac, char **argv)
{
	int ret = EXIT_SUCCESS;

	if (ac < 2)
	{
		fprintf(stderr, "hnm elf_filename\n");
		return (EXIT_FAILURE);
	}
	if (ac == 2)
		return (hnm(argv[1], argv[0]));
	return (ret);
}
