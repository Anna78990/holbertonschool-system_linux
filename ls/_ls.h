#ifndef _LS_H
#define _LS_H

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define OPTION_1 1
#define OPTION_a 2
#define OPTION_A 4
#define OPTION_l 8

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


#endif
