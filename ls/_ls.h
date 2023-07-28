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

/**
 * struct File - file info object
 * @name: name of file
 * @next: next
 */
typedef struct File
{
	char *name;
	struct File *next;
} File;

/**
 * struct File_list - file list
 * @file: pointer to file
 * @next: pointer to next file list
 */
typedef struct File_list
{
	File file;
	struct File_list *next;
} File_list;

int parse_arg(char **argv);
int op_check(char *argv);
int *op_index(char **argv);
int file_check(char *name);
int parse_options(char *arg, int bit);
int _strcmp(char *f, char *s);
char *_strdup(const char *str);
void *add_file(char *name, File *ptr);
void free_files(File *ptr);
File_list *add_filelist(File_list *ptr);
void free_file_list(File_list *ptr);
unsigned int _strlen(char *str);
void check_length(int *s_list, char *dirname);
int len_int(int n);
void lprint(int *size, char *dirname);

#endif
