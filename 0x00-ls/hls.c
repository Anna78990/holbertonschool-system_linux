#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>

/**
 * word_check - check if it is hidden file or filename
 * @str: filename to check
 * Return: 0 if it succeeds, otherwise 1
 */

int word_check(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '.')
			i++;
		else
			return (1);
	}
	return (0);
}

/**
 * _strcat - concatenate two strings with '/'
 * @fst: concatenating string
 * @scd: string concatenated after '/'
 * Return: concataneted string
 */

char *_strcat(const char *fst, const char *scd)
{
	int i = 0, j = 0, ctr;
	char *buf;

	while (fst[i] != '\0')
		i++;
	while (scd[j] != '\0')
		j++;
	j += i;
	buf = (char *)malloc((j + 2) * sizeof(char));
	for (ctr = 0; ctr <= j; ctr++)
	{
		if (ctr == i)
			buf[ctr] = '/';
		else if (ctr > i)
			buf[ctr] = scd[ctr - i - 1];
		else
			buf[ctr] = fst[ctr];
	}
	buf[ctr] = '\0';
	return (buf);
}

/**
 * list - some parts of a list
 * @stat: filestate
 * Return: Nothing
 */

void list(const struct stat *stat)
{
        struct passwd *username, *groupname;

	printf((S_ISDIR(stat->st_mode))  ? "d" : "-");
	printf((stat->st_mode & S_IRUSR) ? "r" : "-");
	printf((stat->st_mode & S_IWUSR) ? "w" : "-");
	printf((stat->st_mode & S_IXUSR) ? "x" : "-");
	printf((stat->st_mode & S_IRGRP) ? "r" : "-");
	printf((stat->st_mode & S_IWGRP) ? "w" : "-");
	printf((stat->st_mode & S_IXGRP) ? "x" : "-");
	printf((stat->st_mode & S_IROTH) ? "r" : "-");
	printf((stat->st_mode & S_IWOTH) ? "w" : "-");
	printf((stat->st_mode & S_IXOTH) ? "x" : "-");
	printf(" %ld", stat->st_nlink);
	username = getpwuid(stat->st_uid);
	groupname = getpwuid(stat->st_gid);
	printf(" %s %s", username->pw_name, groupname->pw_name);
	printf(" %ld ", stat->st_size);
}

/**
 * _ls - function of ls
 * @dir: pointer to directory
 * @op_a: variable for check if a option exists and if it is upper/lower case
 * @op_l: variable for check if l option exists
 * Return: Nothing
 */

void _ls(const char *dir, int op_a, int op_l)
{
	struct dirent *d;
	DIR *dh = opendir(dir);
	struct stat fileStat;
	char *filename;

	if (!dh)
	{
		if (errno == ENOENT)
			perror("Directory doesn't exist");
		else
			perror("Unable to read directory");
		exit(EXIT_FAILURE);
	}
	while ((d = readdir(dh)) != NULL)
	{
		if (!op_a && d->d_name[0] == '.')
			continue;
		else if (op_a == 2 && !word_check(d->d_name))
			continue;
		else if (op_l)
		{
			filename = _strcat(dir, d->d_name);
			if (!lstat(filename, &fileStat))
				list(&fileStat);
			else
				perror("Error in stat");
		}
		printf("%s  ", d->d_name);
		if (op_l)
			printf("\n");
	}
	if (!op_l)
		printf("\n");
}


/**
 * main - function to give the arguments to _ls function
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: always 0
 */
int main(int argc, const char *argv[])
{
	if (argc == 1)
		_ls(".", 0, 0);
	else if (argc >= 2)
	{
		if (argv[1][0] == '-')
		{
			int op_a = 0, op_l = 0;
			char *p = (char *)(argv[1] + 1);

			while (*p)
			{
				if (*p == 'a')
					op_a = 1;
				else if (*p == 'A')
					op_a = 2;
				else if (*p == 'l')
					op_l = 1;
				else
				{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			if (argc == 2)
				_ls(".", op_a, op_l);
			else
				_ls(argv[2], op_a, op_l);
		}
		else
			_ls(argv[1], 0, 0);
	}
	return (0);
}
