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
		else
			printf("%s\n", dirname);
	}
	else
	{
		sprintf(er, "./hls: cannot access %s: ", dirname);
		perror(er);
	}
	return (0);
}

/**
 * main - ls program
 * @argc: the number of arguments on the command line
 * @argv: argv
 * Return: content of the current diractory
*/
int main(int argc, char *argv[])
{
	DIR *dir;
	char *cur_dir = "./", c = ' ';
	struct dirent *read;
	int  bit, op_idx;

	if (argc == 1)
	{
		dir = opendir(cur_dir);
    		while ((read = readdir(dir)) != NULL)
		{
			if (read->d_name[0] != '.')
        			printf("%s  ", read->d_name);
		}
		printf("\n");
		closedir(dir);
		return (0);
	}
	op_idx = op_index(argv);
	if (op_idx != argc)
		bit = parse_options(argv[op_idx]);
	if (argc == 2 && argv[1][0] == '-')
		dir = opendir(cur_dir);
	else
	{
		dir = opendir(argv[1]);
		cur_dir = argv[1];
	}
	if (dir)
	{
		if (!(argc == 2 && argv[1][0] == '-'))
			printf("%s:\n", argv[1]);
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
	return (0);
}

