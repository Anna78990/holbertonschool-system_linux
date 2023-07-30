#include "_ls.h"

/**
 * convert_number - convert int to string
 * @num: number to convert
 * Return: string of given number
 */
char *convert_number(long int num)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % 10];
		n /= 10;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * raw_name - advance pointer just after slash
 * @fullpath: path which may contain slash
 * Return: correct path
 */
char *raw_name(char *fullpath)
{
	char *ptr;

	if (!fullpath)
		return (NULL);
	if (!*fullpath)
		return (fullpath);
	ptr = fullpath + _strlen(fullpath) - 1;
	for (; ptr >= fullpath; ptr--)
	{
		if (*ptr == '/')
		{
			if (*(ptr + 1))
				return (ptr + 1);
			return (ptr);
		}
	}
	return (fullpath);
}


/**
 * format_time - print the time correctly
 * @file: stat object to refer
 * Return: correct format time
 */
char *format_time(struct stat file)
{
	char *p = ctime(&(file.st_mtime));

	if (_strlen(p) >= 16)
	{
		p += 4;
		p[12] = 0;
	}
	return (p);
}

/**
 * is_dir - check if its directory
 * @file: stat object to refer
 * Return: 'd' if directory, 'l' if link, '-' othewise
 */
char is_dir(struct stat file)
{
	return (S_ISDIR(file.st_mode));
}

/**
 * lprint - print with option l
 * @dirname: directory/file name
 */
void lprint(char *dirname)
{
	struct stat file = {0};
	struct passwd *usr = NULL;
	struct group *grp = NULL;
	char buf[256] = {0};

	lstat(dirname, &file);
	usr = getpwuid(file.st_uid);
	grp = getgrgid(file.st_gid);

	printf("%c%c%c%c%c%c%c%c%c%c %lu ",
		is_dir(file) ? 'd' : S_ISLNK(file.st_mode) ? 'l' : '-',
		RUSR, WUSR, XUSR, RGRP, WGRP, XGRP, ROTH, WOTH, XOTH,
		file.st_nlink);

	if (usr)
		printf("%s ", usr->pw_name);
	else
		printf("%s ", convert_number(file.st_uid));

	if (grp)
		printf("%s ", grp->gr_name);
	else
		printf("%s ", convert_number(file.st_gid));
	printf("%lu %s %s",
			file.st_size, format_time(file), raw_name(dirname));
	if (S_ISLNK(file.st_mode))
	{
		readlink(dirname, buf, 256);
		printf(" -> %s", buf);
	}
	printf("\n");
}
