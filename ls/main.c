#include "_ls.h"

/**
 * error_hundle - print error when it occurs
 * @dirname: directory name to check if it has error
 * @command: command name
 */
void error_hundle(char *dirname, char *command)
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
		else
			printf("%s\n", dirname);
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
 * @command: command name
 */
void _ls(int bit, char *dirname, int n_dir, int ctr, char *command)
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
				if (bit & OPTION_a || (bit & OPTION_A
						&& file_check(read->d_name)))
					printf("%s%c", read->d_name, c);
			}
			else
				printf("%s%c", read->d_name, c);

		}
		if (c != 10)
			printf("\n");
		if (bit)
			ctr -= 1;
		if (n_dir > ctr)
			printf("\n");
		closedir(dir);
	}
	else
		error_hundle(dirname, command);
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
	int i, bit = 0, op_idx, n_dir = 0;

	op_idx = op_index(argv);
	if (op_idx != argc)
		n_dir = argc - 2;
	else
		n_dir = argc - 1;
	if (op_idx != argc)
		bit = parse_options(argv[op_idx]);
	for (i = 0; argv[i]; i++)
	{
		if (argc == 1 || (argc == 2 && op_idx == i))
			_ls(bit, cur_dir, n_dir, i, argv[0]);
		else if (i != 0 && i != op_idx)
			_ls(bit, argv[i], n_dir, i, argv[0]);
	}
	return (0);
}

