#include "_ls.h"

/**
 * op_index - search index which contans option
 * @argv: array of argv to search
 * Return: found index or length + 1 if not found
 */
int op_index(char **argv)
{
	int i;

	for (i = 0; argv[i]; i++)
	{
		if (argv[i][0] == '-')
			return (i);
	}
	return (i);
}

/**
 * file_check - check if file name is file like '.', '..'
 * @name: file name
 * Return: 1 if the other char is found, otherwise 0
 */
int file_check(char *name)
{
	while (*++name)
	{
		if (*name != '.')
			return (1);
	}
	return (0);
}
/**
 * parse_options - parses options from args
 * @arg: the option arg string
 * Return: option bit
 */
int parse_options(char *arg)
{
	int i = 0;

	while (*++arg)
	{
		switch (*arg)
		{
			case '1':
				i |= OPTION_1;
				break;
			case 'a':
				i |= OPTION_a;
				break;
			case 'A':
				i |= OPTION_A;
				break;
			case 'l':
				i |= OPTION_l;
				break;
			default:
				exit(2);
				break;
		}
	}
	return (i);
}
