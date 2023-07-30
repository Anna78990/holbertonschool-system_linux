#ifndef _LS_H
#define _LS_H

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define OPTION_1 1
#define OPTION_a 2
#define OPTION_A 4
#define OPTION_l 8


#define RUSR (file.st_mode & S_IRUSR ? 'r' : '-')
#define WUSR (file.st_mode & S_IWUSR ? 'w' : '-')
#define XUSR (file.st_mode & S_IXUSR ? 'x' : '-')
#define RGRP (file.st_mode & S_IRGRP ? 'r' : '-')
#define WGRP (file.st_mode & S_IWGRP ? 'w' : '-')
#define XGRP (file.st_mode & S_IXGRP ? 'x' : '-')
#define ROTH (file.st_mode & S_IROTH ? 'r' : '-')
#define WOTH (file.st_mode & S_IWOTH ? 'w' : '-')
#define XOTH (file.st_mode & S_IXOTH ? 'x' : '-')


int parse_arg(char **argv);
int op_check(char *argv);
int *op_index(char **argv);
int file_check(char *name);
int parse_options(char *arg, int bit);
int _strcmp(char *f, char *s);
char *_strdup(const char *str);
unsigned int _strlen(char *str);
void lprint(char *dirname);

#endif
