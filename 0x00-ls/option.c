#include "line_ls.h"
#include "ls.h"


/**
 * define_option - set option
 * @option: string option discribe
 * @flag: option command
 * Return: fotmat string
 */

void define_options(char *option, ops_t *flag)
{
	int i;

	for (i = 0; option[i]; i++)
	{
		switch (option[i])
		{
			case '1':
				flag->per_file = 1;
				break;
			case 'a':
				flag->op_a = 1;
				flag->op_auc = 0;
				break;
			case 'A':
				flag->op_a = 1;
				flag->op_auc = 1;
				break;
			case 'l':
				flag->long_list = 1;
				flag->per_file = 1;
				break;
		}
	}
}

/**
 * check_filetype - setup permision of file
 * @mode: mask permission of file
 * @perm: string perm
 *
 * Return: perm of file
 */
char *check_filetype(mode_t mode, char *perm)
{
	int i;
	typefile_t types[7] = {
		{S_IFREG, '-'}, {S_IFDIR, 'd'}, {S_IFCHR, 'c'},
		{S_IFBLK, 'b'}, {S_IFIFO, 'P'}, {S_IFLNK, 'l'},
		{S_IFSOCK, 's'},
	};

	permfile_t perm_t[9] = {
		{S_IRUSR, 'r'}, {S_IWUSR, 'w'}, {S_IXUSR, 'x'}, {S_IRGRP, 'r'},
		{S_IWGRP, 'w'}, {S_IXGRP, 'x'}, {S_IROTH, 'r'}, {S_IWOTH, 'w'},
		{S_IXOTH, 'x'},
	};

	_memset(perm, 0, 12);

	for (i = 0; i < 7; i++)
	{
		if ((mode & S_IFMT) == types[i].mask)
		{
			perm[0] = types[i].symbole;
			break;
		}
	}

	for (i = 0; i < 9; i++)
	{
		if (perm_t[i].mask & mode)
			perm[i + 1] = perm_t[i].symbole;
		else
			perm[i + 1] = '-';
	}
	return (perm);
}

/**
 * number_digit - count number of digit
 * @n: number
 *
 * Return: digit of number
 */

int number_digit(unsigned int n)
{
	int i;
	unsigned int digit = 1;

	for (i = 0; digit < n; i++)
		digit *= 10;

	return (i);
}

/**
 * str_format - list name of file
 * @node: head of node
 * @flag: option command
 * @digit: print with the good digit for option -l
 * Return: fotmat string
 */
void format_str(line_ls_t *node, ops_t op, int digit)
{
	if (_strlen(node->name) == 2 || _strlen(node->name) == 1)
	{
		if (op.op_auc &&
			(_strcmp(node->name, ".") == 0 || _strcmp(node->name, "..") == 0))
		{
			if (node->next == NULL)
				printf("\n");
			return;
		}
	}

	if (!(op.op_a) && node->name[0] == '.')
	{
		if (node->next == NULL && !op.per_file)
			printf("\n");
		return;
	}

	if (op.long_list)
	{
		printf("%s %u %s %s %*u %s %s\n", node->perm, node->hlnk,
				node->usrname, node->grpname, digit, node->size,
				node->time, node->name);
		return;
	}

	if (op.per_file)
	{
		printf("%s\n", node->name);
		return;
	}

	if (node->next == NULL)
		printf("%s\n", node->name);
	else
		printf("%s ", node->name);
}
