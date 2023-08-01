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
	static listcars_t *cars_list;
	static listcars_t *cars;
	listcars_t *head = cars;

	if ((int)size == 0)
	{
		cars = cars_list;
		while (cars_list)
		{
			head = cars_list->next;
			free(cars_list);
			cars_list = head;
		}
		return;
	}
	else
	{
		if (!cars || !search_carslist(&cars, id, size))
		{
			cars_list = cars = add_car(&cars, id, size);
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
			*cars = head = new;
		else
		{
			tmp = head = *cars;
			while (*cars)
			{
				if ((*cars)->id > list[i])
				{
					if ((*cars) == tmp)
					{
						new->next = *cars;
						tmp = head = *cars = new;
						break;
					}
					else
					{
						tmp->next = new;
						new->next = *cars;
						*cars = head;
						break;
					}
				}
				tmp = *cars, *cars = (*cars)->next;
			}
			if ((*cars) == NULL)
			{
				tmp->next = new;
			}
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
