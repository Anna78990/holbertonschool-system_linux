#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * check_id - check if it has id or not
 * @path: path to check
 * Return: id, if it does not exist -1
 */
int check_id(char *path)
{
	char *check, *num;
	int n = -1;

	check = strchr(path, '?');
	if (check == NULL)
	{
		return (-1);
	}
	else
	{
		if (strncmp(check, "?id=", 4) == 0)
		{
			num = strtok(check, "=");
			n = atoi(num);
		}
	}
	return (n);
}

/**
 * print_m_p - print method and path
 * @method: method
 * @path: path
 */
void print_m_p(char *method, char *path)
{
	char p[60] = {0}, *c;
	int i, d;

	c = strchr(path, '?');
	if (c == NULL)
		printf("%s %s", method, path);
	else
	{
		d = c - path;
		for (i = 0; i < d ; i++)
			p[i] = path[i];
		printf("%s %s", method, p);
	}
}
