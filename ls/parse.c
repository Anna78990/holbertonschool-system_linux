#include "_ls.h"


/**
 * op_index - search index which contans option
 * @argv: array of argv to search
 * Return: found index or length + 1 if not found
 */
int *op_index(char **argv)
{
	int i, ctr = 0;
	int *op_arr;

	for (i = 0; argv[i]; i++)
	{
		if (argv[i][0] == '-')
			ctr++;
	}
	if (ctr == 0)
	{
		return (NULL);
	}
	else
		op_arr = (int *)malloc(sizeof(int) * ctr);
	ctr = 0;
	for (i = 0; argv[i]; i++)
	{
		if (argv[i][0] == '-')
		{
			op_arr[ctr] = i;
			ctr++;
		}
	}
	return (op_arr);
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
 * @bit: bit to refer
 * Return: option bit
 */
int parse_options(char *arg, int bit)
{

	while (*++arg)
	{
		switch (*arg)
		{
			case '1':
				bit |= OPTION_1;
				break;
			case 'a':
				bit |= OPTION_a;
				break;
			case 'A':
				bit |= OPTION_A;
				break;
			case 'l':
				bit |= OPTION_l;
				break;
			default:
				exit(2);
				break;
		}
	}
	return (bit);
}
