#ifndef _LS_H
#define _LS_H

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

int op_index(char **argv);
int file_check(char *name);
int parse_options(char *arg);
int _strcmp(char *f, char *s);

#endif
