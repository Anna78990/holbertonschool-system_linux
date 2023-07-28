#include "_ls.h"

/**
 * len_int - length of integer
 * @n: integer to mesure
 * Return: length
 */
int len_int(int n)
{
	int count = 0;

	do {
		n /= 10;
		count++;
	} while (n != 0);
	return (count);
}

/**
 * find_max - compare two integer
 * @max: actual max value
 * @cmp: value to compare
 * Return: greater value
 */
int find_max(int max, int cmp)
{
	if (max < cmp)
		max = cmp;
	return (max);
}

/**
 * check_length - mesure the maximum valeu of each elements
 * @s_list: size list
 * @dirname: directory name to do loop
 */
void check_length(int *s_list, char *dirname)
{
	DIR *dir;
	struct dirent *read;
	struct stat file;
	struct passwd *usr;
	struct group *grp;

	dir = opendir(dirname);
	while ((read = readdir(dir)) != NULL)
	{
		usr = getpwuid(file.st_uid);
		grp = getgrgid(file.st_gid);
		lstat(read->d_name, &file);
		s_list[0] = find_max(s_list[0], len_int(file.st_nlink));
		if (usr)
			s_list[1] = find_max(s_list[1], _strlen(usr->pw_name));
		else
			s_list[1] = find_max(s_list[1], len_int((int)file.st_uid));
		if (grp)
			s_list[2] = find_max(s_list[2], _strlen(grp->gr_name));
		else
			s_list[2] = find_max(s_list[2], len_int((int)file.st_gid));
		s_list[3] = find_max(s_list[3], len_int((int)file.st_size));
	}
	closedir(dir);
}
