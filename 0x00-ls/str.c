#include "str.h"

/**
 * _strcpy - copy string
 * @dst: First string
 * @src: Second string
 *
 * Return: dest
 */
char *_strcpy(char *dst, const char *src)
{
	unsigned int i = 0;

	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


/**
 * _strcat - concat string
 * @s1: First string
 * @s2: Second string
 *
 * Return: s2
 */
char *_strcat(char *s1, char *s2)
{
	unsigned int i = 0, j = 0;

	while (s1[i])
		i++;

	while (s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}


/**
 * _strlen - mesure the length of string
 * @str: string
 *
 * Return: size of string
 */
unsigned int _strlen(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * _memset - write the charatcters for a specified number
 * @s: void ptr
 * @c: value set
 * @n: number of bytes set
 *
 * Return: dest
 */
void *_memset(void *s, int c, unsigned int n)
{
	unsigned char *bytes = s;
	unsigned int i;

	for (i = 0; i < n; i++)
		bytes[i] = c;
	return (bytes);
}

/**
 * _strcmp- compare two strings
 * @f: First string
 * @s: Second string
 *
 * Return: value of compare
 */
int _strcmp(char *f, char *s)
{
	int i;
	int size_f = _strlen(f);
	int size_s = _strlen(s);

	if (!f || !s)
		return (0);

	i = 0;
	while (f[i] && s[i])
	{
		if (f[i] > s[i] || f[i] < s[i])
			return (f[i] - s[i]);
		i++;
	}
	if (size_f > size_s)
		return (f[size_f] - s[i]);
	if (size_s > size_f)
		return (f[i] - s[size_s]);
	return (0);
}
