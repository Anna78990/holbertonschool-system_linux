#include <stdio.h>
#include <stddef.h>
#include "laps.h"


/**
 * _sort - sort given array
 * @arr: array to sort
 * @size: size of array
 */
void _sort(int *arr, int size)
{
	int i, j, swap, swapped;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap = arr[j];
				swapped = arr[j + 1];
				arr[j] = swapped;
				arr[j + 1] = swap;
			}
		}
	}
}

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
	_sort(id, size);
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
	listcars_t *new, *tmp, *head = tmp = *cars;

	for (i = 0; i < (int)size; i++)
	{
		new = malloc(sizeof(listcars_t));
		new->id = list[i];
		new->laps = -1;
		new->next = NULL;
		if (*cars == NULL)
			*cars = head = new;
		else
		{
			while ((*cars)->next)
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
						break;
					}
				}
				tmp = *cars;
				*cars = (*cars)->next;
			}
			if (!((*cars)->next) && ((*cars)->id < list[i]))
				(*cars)->next = new;
			*cars = head;
		}
		printf("Car %d joined the race\n", new->id);
	}
	return (*cars);
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
