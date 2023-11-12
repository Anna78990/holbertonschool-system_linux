#include "hreadelf.h"

/**
 * check_elf - checks if header matches magic bytes
 * @elf_header: 16 byte buffer holding elf header
 * Return: 0 if ELF else 1
 */
int check_elf(char *elf_header)
{
	if (elf_header[0] == 0x7f && elf_header[1] == 0x45 &&
		elf_header[2] == 0x4c && elf_header[3] == 0x46)
		return (0);
	return (1);
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
	char **_argv = argv;

	if (ac < 2)
		return (fprintf(stderr, USAGE), EXIT_FAILURE);
	if (ac == 2)
		return (process_file(argv[1], 0, argv));
	while (*++_argv)
		ret += process_file(*_argv, 1, argv);
	return (ret);
}

/**
 * process_file - displays symbols for 1 file
 * @file_name: name of file to process
 * @multiple: 1 if there are multiple files else 0
 * @argv: the argument vector
 * Return: 0 on success else 1 on error
 */
int process_file(char *file_name, int multiple, char **argv)
{
	int fd, exit_status = 0;
	size_t r, num_printed = 0;
	elf_t elf_header;
	(void)multiple;

	memset(&elf_header, 0, sizeof(elf_header));

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);

	r = read(fd, &elf_header.e64, sizeof(elf_header.e64));
	if (r != sizeof(elf_header.e64) || check_elf((char *)&elf_header.e64))
	{
		fprintf(stderr, "%s: %s: File format not recognized\n", argv[0], file_name);
		exit_status = EXIT_FAILURE;
	}
	else
	{
		if (IS_32(elf_header.e64))
		{
			lseek(fd, 0, SEEK_SET);
			r = read(fd, &elf_header.e32, sizeof(elf_header.e32));
			if (r != sizeof(elf_header.e32) || check_elf((char *)&elf_header.e32))
			{
				exit_status = fprintf(stderr, ERR_NOT_MAGIC, argv[0]);
				EXIT_FAILURE;
			}
		}
		/*if (multiple)
			printf("\n%s:\n", file_name);
		*/
		switch_all_endian(&elf_header);
		exit_status = print_all_symbol_tables(&elf_header, fd, &num_printed);
		if (!num_printed)
			fprintf(stderr, "%s: %s: no symbols\n", argv[0], file_name);
	}
	free(elf_header.s32);
	free(elf_header.s64);
	free(elf_header.p32);
	free(elf_header.p64);
	close(fd); /* if error? */
	return (exit_status);
}
