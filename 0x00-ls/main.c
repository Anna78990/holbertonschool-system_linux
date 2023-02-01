#include "ls.h"


/**
 * main - entry function
 * @argc: number of argument
 * @argv: arguments
 *
 * Return: Succes = 0, Error = 2
 */
int main(int argc, char **argv)
{
	int i, n_option = 0, status = 0;
	char *path;
	ops_t options = {0, 0, 0, 0, 1};

	for (i = argc - 1; i > 0; i--)
	{
		if (argv[i][0] == '-')
		{
			define_options(argv[i], &options);/**/
			n_option++;
		}
	}
	if (argc < 2 || n_option == argc - 1)
		_ls("./", options);
	else
		for (i = argc - 1; i > 0; i--)
		{
			if (argv[i][0] == '-')
				continue;
			path = set_pathname(argv[i], argv[0]);/**/
			/* if it failed by error errono is more than 0 */
			if (errno > status)
				status = errno;

			if (argc >= 3 && path)
				printf("%s:\n", argv[i]);

			_ls(path, options);/**/

			if (argc >= 3 && i > 1 && path)
				printf("\n");
			free(path);
		}
	return (status);
}
