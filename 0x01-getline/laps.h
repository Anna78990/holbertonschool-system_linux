#ifndef LAPS_H
#define LAPS_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * struct listcars_s - singly linked list
 * @id: id
 * @laps: laps
 * @next: points to the next node
 * Description: singly linked list node structure
 *
 */
typedef struct listcars_s
{
	int id;
	int laps;
	struct listcars_s *next;
} listcars_t;


void race_state(int *id, size_t size);
listcars_t *add_car(listcars_t **cars, int *list, size_t size);
listcars_t *change_state(listcars_t **cars, int *list, size_t size);
int search_carslist(listcars_t **cars, int *list, size_t size);

#endif
