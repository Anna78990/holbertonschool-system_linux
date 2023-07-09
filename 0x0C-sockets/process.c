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
