#ifndef SOCKET_H
#define SOCKET_H

/**
 * struct todo_t - todo linked list structure
 * @id: id of current todo item
 * @title: title of current todo item
 * @description: description of current todo item
 * @next: next todo item in the linked lists
 */
typedef struct todo_t
{
	int id;
	char *title;
	char *description;
	struct todo_t *next;
} todo_s;

void res_check(char *res);
char *trim(char *str);
char *check_id(char *path);
void print_m_p(char *method, char *path);

#endif
