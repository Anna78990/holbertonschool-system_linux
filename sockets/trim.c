#include <ctype.h>
#include <stddef.h>
#include <string.h>

/**
 * trim - trimming given string
 * @str: string to trim
 * Return: trimed string
 */
char *trim(char *str)
{
	size_t len = strlen(str);
	char *end;

	if (len == 0)
		return (str);

	end = str + len - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';

	while (*str && isspace((unsigned char)*str))
		str++;

	return (str);
}
