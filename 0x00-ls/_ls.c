#include "ls.h"
#include "line_ls.h"

/**
 * error_message - call error message
 * @name: path
 * @program: name of program
 *
 * Return: error message
 */
char *error_message(char *name, char *program)
{
	char *error_msg;
	unsigned int size_p = _strlen(program);

	error_msg = (char *)malloc(sizeof(char) * 1024 + size_p);
	if (!error_msg)
		return (NULL);
	_strcpy(error_msg, program);
	_strcat(error_msg, ": ");
	_strcat(error_msg, "cannot access ");
	_strcat(error_msg, name);
	return (error_msg);
}

/**
 * set_pathname - check path of lstat()
 * @name: string argv
 * @program_name: name of programme
 *
 * Return: pathname
 */
char *set_pathname(char *name, char *program_name)
{
	unsigned int size = _strlen(name);
	char *path;
	struct stat buf;
	char *err_msg;

	path = (char *)malloc(sizeof(char) * size + 4);

	if (!path)
		exit(EXIT_FAILURE);

	_strcpy(path, name);

	if ((lstat(name, &buf)) == -1)
	{
		err_msg = error_message(path, program_name);
		perror(err_msg);
		free(err_msg);
		free(path);
		errno = 2;
		return (NULL);
	}
	/* check if it is directory */
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		_strcat(path, "/");
	return (path);
}

/**
 * set_filelist - set file node
 * @head: head of nodes
 * @name: name of file
 * @read: stream directory
 */
void set_filelist(line_ls_t ***head, char *name,
dirent *read)
{
	struct stat buf;
	struct passwd *user;
	struct group *group;
	char datetime[256];
	line_ls_t **lines = *head;

	lstat(name, &buf);

	user = getpwuid(buf.st_uid);
	group = getgrgid(buf.st_gid);

	add_line(lines);

	check_filetype(buf.st_mode, (*lines)->perm);

	_strcpy((*lines)->usrname, user->pw_name);
	_strcpy((*lines)->grpname, group->gr_name);

	(*lines)->size = buf.st_size;

	_strcpy(datetime, ctime(&(buf.st_mtime)));
	/* to cut the part of seconds */
	datetime[_strlen(datetime) - 9] = '\0';
	/* to cut the part of day of week */
	_strcpy((*lines)->time, (datetime + 4));

	(*lines)->hlnk = buf.st_nlink;

	if (read)
		_strcpy((*lines)->name, read->d_name);
	else
		_strcpy((*lines)->name, name);
	**head = *lines;
}

/**
 * set_dirlist - set list of directory
 * @head: head of nodes
 * @name: pathname directory
 */
void set_dirlist(line_ls_t **head, char *name)
{
	DIR *dir;
	struct dirent *read;
	char pathname[1024];
	line_ls_t **lines = head;

	dir = opendir(name);
	if (dir == NULL)
	{
		set_filelist(&lines, name, NULL);
		return;
	}
	while ((read = readdir(dir)))
	{
		_strcpy(pathname, name);
		_strcat(pathname, read->d_name);

		set_filelist(&lines, pathname, read);
	}
	closedir(dir);
}

/**
 * _ls - command hls
 * @name: pathname
 * @option: option command
 * Return: error handling
 */
int _ls(char *name, ops_t options)
{
	line_ls_t *lines = NULL;

	if (!name)
		return (-1);

	set_dirlist(&lines, name);
	print_list(lines, options);
	clean(lines);
	return (0);
}
