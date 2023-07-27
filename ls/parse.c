#include "_ls.h"

/**
 * op_check - if it is option or not
 * @argv: string to check
 * Return: 1 if found, 0 if not found
 */
int op_check(char *argv)
{
	if (argv[0] == '-')
		return (1);
	else
		return (0);
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
