#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * check_id - check if it has id or not
 * @path: path to check
 * Return: string of id
 */
char *check_id(char *path)
{
	char *check;

	check = strchr(path, '?');
	if (check == NULL)
	{
		return (NULL);
	}
	else
	{
		if (strncmp(check, "?id=", 4) == 0)
			return (strtok(check, "="));
	}
	return (NULL);
}

/**
 * print_m_p - print method and path
 * @method: method
 * @path: path
 */
void print_m_p(char *method, char *path)
{
	char *p;

	if (strchr(path, '?') == NULL)
		printf("%s %s", method, path);
	else
	{
		p = strtok(path, "?");
		printf("%s %s", method, p);
	}
}
