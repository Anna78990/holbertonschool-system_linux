#include "_ls.h"

/**
 * error_hundle - print error when it occurs
 * @dirname: directory name to check if it has error
 */
void error_hundle(char *dirname)
{
	struct stat buf;
	char er[1024];

	if (lstat(dirname, &buf) == 0)
	{
		if (errno == 13)
		{
			sprintf(er, "./hls: cannot open directory %s: ",
					dirname);
			perror(er);
		}
	}
	else
	{
		sprintf(er, "./hls: cannot access %s: ", dirname);
		perror(er);
	}
}

/**
 * _ls - list the files under given directory
 * @bit: bit value which contains information about option
 * @dirname: directory name to use
 */
void _ls(int bit, char *dirname)
{
	DIR *dir;
	char c = ' ';
	struct dirent *read;

	dir = opendir(dirname);
	if (dir)
	{
		if (_strcmp(dirname, "./"))
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
		printf("\n");
		closedir(dir);
	}
	else
		error_hundle(dirname);
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
	int i, bit = 0, op_idx;

	op_idx = op_index(argv);
	if (op_idx != argc)
		bit = parse_options(argv[op_idx]);
	for (i = 0; argv[i]; i++)
	{
		if (argc == 1 || (argc == 2 && op_idx == i))
			_ls(bit, cur_dir);
		else if (i != 0 && i != op_idx)
			_ls(bit, argv[i]);
	}
	return (0);
}

