#include "_ls.h"

/**
 * error_hundle - print error when it occurs
 * @dirname: directory name to check if it has error
 * @command: command name
 * @files: pointer to count file
 * @size: size array
 */
void error_hundle(char *dirname, char *command, int *files, int *size)
{
	struct stat buf;
	char er[1024];

	if (lstat(dirname, &buf) == 0)
	{
		if (errno == 13)
		{
			sprintf(er, "%s: cannot open directory %s",
					command, dirname);
			perror(er);
		}
		if (S_ISDIR(buf.st_mode))
			check_length(size, dirname);
		else
		{
			printf("%s\n", dirname);
			*files += 1;
		}
	}
	else
	{
		sprintf(er, "%s: cannot access %s", command,
				dirname);
		perror(er);
	}
}

/**
 * _ls - list the files under given directory
 * @bit: bit value which contains information about option
 * @dirname: directory name to use
 * @n_dir: number of directories
 * @ctr: times when the function counted
 * @size: size array
 */
void _ls(int bit, char *dirname, int n_dir, int ctr, int *size)
{
	DIR *dir;
	char c = ' ';
	struct dirent *read;

	dir = opendir(dirname);
	if (dir)
	{
		if (_strcmp(dirname, "./") && n_dir > 1)
			printf("%s:\n", dirname);
		if (bit & OPTION_1)
			c = '\n';
		while ((read = readdir(dir)) != NULL)
		{
			if (read->d_name[0] == '.')
			{
				if (bit & OPTION_a || (bit & OPTION_A &&
							file_check(read->d_name)))
				{
					if (bit & OPTION_l)
						lprint(size, read->d_name);
					else
						printf("%s%c", read->d_name, c);
				}
			}
			else
			{
				if (bit & OPTION_l)
					lprint(size, read->d_name);
				else
					printf("%s%c", read->d_name, c);
			}
		}
		if (c != 10 && !(bit & OPTION_l))
			printf("\n");
		if (n_dir > ctr)
			printf("\n");
		closedir(dir);
	}
}

/**
 * main - ls program
 * @argc: the number of arguments on the command line
 * @argv: argv
 * Return: content of the current diractory
*/
int main(int argc, char *argv[])
{
	char *cur_dir = "./";
	int j = 0, i = 0, ctr = 0, files = 0;
	int bit = 0, n_dir = argc - 1, size[4] = {0};

	while (argv[i])
	{
		if (i == 0)
			i += 1;
		else if (op_check(argv[i]))
			bit = parse_options(argv[i++], bit), n_dir -= 1;
		else
			error_hundle(argv[i++], argv[0], &files, size);
	}
	if (n_dir == 0)
		error_hundle(cur_dir, argv[0], &files, size);
	if (files > 0)
		printf("\n");
	for (j = 0; argv[j]; j++)
	{
		if (n_dir == 0)
		{
			_ls(bit, cur_dir, n_dir, ctr, size);
			break;
		}
		else if (j == 0 || op_check(argv[j]))
			continue;
		else
			_ls(bit, argv[j], n_dir, ++ctr, size);
	}
	return (0);
}
