#ifndef _LINE_LS_H
#define _LINE_LS_H

#include "ls.h"

/**
 * struct line_hls_s- node of file
 * @perm: permision of file
 * @usrname: user file
 * @grpname: group file
 * @size: size of file
 * @name: name of file
 * @next: next file of the list
 * @time: date of the last modification of file
 * @hlnk: number of hardlink
 *
 * Description: node of file list  with different section
 */
typedef struct line_ls_s
{
	char *perm;
	char *usrname;
	char *grpname;
	unsigned int hlnk;
	unsigned int size;
	char *time; /*ctime() format string*/
	char *name;
	struct line_ls_s *next;
} line_ls_t;

/**
 * diren - Typedef for struct dirent
 */
typedef struct dirent dirent;

void print_list(line_ls_t *node, ops_t flag);
void add_line(line_ls_t **node);
void clean(line_ls_t *node);
void format_str(line_ls_t *node, ops_t flag, int digit);
int number_digit(unsigned int nb);
#endif /* _LINE_HLS_H */
