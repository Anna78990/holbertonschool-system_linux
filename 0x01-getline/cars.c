why I could not get expected out put on following code?:

laps.c:
#include <stdio.h>
#include <stddef.h>
#include "laps.h"

/**
 * race_state - update race state
 * @id: array of id
 * @size: size or the array
 * Return: always Nothing.
 */
void race_state(int *id, size_t size)
{
	static listcars_t *cars;
	listcars_t *head = cars;

	if (!id)
		return;
	if (((int)size == 0) && cars)
	{
		while (cars)
		{
			head = cars->next;
			free(cars);
			cars = head;
		}
	}
	else
	{
		if (!cars || !search_carslist(&cars, id, size))
		{
			cars = add_car(&cars, id, size);
			head = cars;
		}
		cars = change_state(&cars, id, size);
		printf("Race state:\n");
		while (cars)
		{
			printf("Car %d [%d laps]\n", cars->id, cars->laps);
			cars = cars->next;
		}
		cars = head;
	}
}


/**
 * add_car - add_car
 * @cars: car's linked list
 * @list: array of the id list
 * @size: size or the array
 * Return: always Nothing.
 */

listcars_t *add_car(listcars_t **cars, int *list, size_t size)
{
	int i;
	listcars_t *new, *tmp, *head = *cars;

	for (i = 0; i < (int)size; i++)
	{
		new = malloc(sizeof(listcars_t));
		new->id = list[i], new->laps = -1, new->next = NULL;
		if (*cars == NULL)
		{
			*cars = new;
			head = new;
		}
		else
		{
			tmp = *cars;
			while (*cars)
			{
				if ((*cars)->id > list[i])
				{
					if ((*cars) == tmp)
					{
						new->next = *cars;
						tmp = head = *cars = new;
					}
					else
					{
						tmp->next = new;
						new->next = *cars;
					}
				}
				tmp = *cars;
				*cars = (*cars)->next;
			}
			if ((*cars) == NULL)
				tmp->next = new;
		}
		printf("Car %d joined the race\n", new->id);
	}
	return (head);
}

/**
 * change_state - update race state
 * @cars: cars list
 * @list: array of car id
 * @size: size or the array
 * Return: always Nothing.
 */

listcars_t *change_state(listcars_t **cars, int *list, size_t size)
{
	int i;
	listcars_t *head = *cars;

	for (i = 0; i < (int)size; i++)
	{
		while (*cars)
		{
			if ((*cars)->id == list[i])
			{
				(*cars)->laps += 1;
				break;
			}
			*cars = (*cars)->next;
		}
		*cars = head;
	}
	return (head);
}

/**
 * search_carslist - search if the car already exist or not
 * @cars: cars list
 * @list: array of car id
 * @size: size or the array
 * Return: 1 or 0
 */

int search_carslist(listcars_t **cars, int *list, size_t size)
{
	int i;
	listcars_t *head = *cars;

	if (!list)
		return (1);
	for (i = 0; i < (int)size; i++)
	{
		while (*cars)
		{
			if ((*cars)->id == list[i])
			{
				*cars = head;
				return (1);
			}
			else
				*cars = (*cars)->next;
		}
		*cars = head;
	}
	return (0);
}


0-main2.c: 
#include "laps.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main()
{

    int ids[3] = {89, 2, 102};
    int i;
    
    for (i = 0 ; i < 10 ; i ++) 
    {
      race_state(ids, 3);
    }
    race_state(NULL, 0);
    return (0);
}


laps.h:
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

compile command:
vagrant@vagrant:~/holbertonschool-system_linux/0x01-getline$ gcc -Wall -Wextra -Werror -pedantic 0-main2.c laps.c  -o laps

[got]
laps
vagrant@vagrant:~/holbertonschool-system_linux/0x01-getline$ ./laps 
Car 89 joined the race
Car 2 joined the race
Car 102 joined the race
Race state:
Car 102 [0 laps]
Race state:
Car 102 [1 laps]
Race state:
Car 102 [2 laps]
Race state:
Car 102 [3 laps]
Race state:
Car 102 [4 laps]
Race state:
Car 102 [5 laps]
Race state:
Car 102 [6 laps]
Race state:
Car 102 [7 laps]
Race state:
Car 102 [8 laps]
Race state:
Car 102 [9 laps]

[Expected]
Car 89 joined the race
Car 2 joined the race
Car 102 joined the race
Race state:
Car 2 [0 laps]
Car 89 [0 laps]
Car 102 [0 laps]
Race state:
Car 2 [1 laps]
Car 89 [1 laps]
Car 102 [1 laps]
Race state:
Car 2 [2 laps]
Car 89 [2 laps]
Car 102 [2 laps]
Race state:
Car 2 [3 laps]
Car 89 [3 laps]
Car 102 [3 laps]
Race state:
Car 2 [4 laps]
Car 89 [4 laps]
Car 102 [4 laps]
Race state:
Car 2 [5 laps]
Car 89 [5 laps]
Car 102 [5 laps]
Race state:
Car 2 [6 laps]
Car 89 [6 laps]
Car 102 [6 laps]
Race state:
Car 2 [7 laps]
Car 89 [7 laps]
Car 102 [7 laps]
Race state:
Car 2 [8 laps]
Car 89 [8 laps]
Car 102 [8 laps]
Race state:
Car 2 [9 laps]
Car 89 [9 laps]
Car 102 [9 laps]
