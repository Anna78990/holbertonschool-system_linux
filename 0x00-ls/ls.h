#ifndef _LS_H
#define _LS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include "str.h"
#include <errno.h>


/**
 * struct typefile_s - show type of files on command hls
 * @mask: st_mode of file
 * @symbole: symbole show on command hls
 *
 * Description: define the first symbole of string, determine if
 * is a regular file '-', or is directory 'd', or a socket 's', or (...)
 */
typedef struct typefile_s
{
	unsigned int mask;
	char symbole;
} typefile_t;


/**
 * struct permfile_s - show permision of files on hls
 * @mask: st_mode of file
 * @symbole: Second member
 *
 * Description: define is the owner group and other can do with the file,
 * read, write, execute
 */
typedef struct permfile_s
{
	unsigned int mask;
	char symbole;
} permfile_t;

/**
 * struct op_s - options
 * @long_list: for option l
 * @op_a: option a
 * @op_auc: option A
 * @per_file: for option l
 * @def: default option
 * Description: define option of command
 */
typedef struct ops_s
{
	unsigned char long_list;
	unsigned char op_a;
	unsigned char op_auc;
	unsigned char per_file;
	unsigned char def;
} ops_t;


/* function */
int _ls(char *name, ops_t flag);
char *check_filetype(mode_t mode, char *perm);
char *set_pathname(char *name, char *program_name);
void define_options(char *option, ops_t *flag);

#endif /* _HLS_H */
