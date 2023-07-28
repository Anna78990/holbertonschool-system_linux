#include "_ls.h"

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
 * @size: array of sizes which contains maximum length
 * @dirname: directory/file name
 */
void lprint(int *size, char *dirname)
{
	struct stat file;
	struct passwd *usr;
	struct group *grp;

	lstat(dirname, &file);
	usr = getpwuid(file.st_uid), grp = getgrgid(file.st_gid);

	printf("%c%c%c%c%c%c%c%c%c%c %*lu ",
		is_dir(file) ? 'd' : S_ISLNK(file.st_mode) ? 'l' : '-',
		RUSR, WUSR, XUSR, RGRP, WGRP, XGRP, ROTH, WOTH, XOTH,
		size[0] - len_int(file.st_nlink), file.st_nlink);

	if (usr)
		printf("%*s ", size[1], usr->pw_name);
	else
		printf("%*u ", size[1], file.st_uid);

	if (grp)
		printf("%*s ", size[2], grp->gr_name);
	else
		printf("%*u ", size[2], file.st_gid);
	printf("%*lu %s %s", size[3],
			file.st_size, format_time(file), raw_name(dirname));
	if (S_ISLNK(file.st_mode))
	{
		char buf[256] = {0};

		readlink(dirname, buf, 256);
		printf(" -> %s", buf);
	}
	printf("\n");
}
