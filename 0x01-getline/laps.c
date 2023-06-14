#include <stdio.h>
#include <stdlib.h>
#include "laps.h"

/**
 * race_state - keeps track of the number of laps
 *		made by several cars in a race
 * @id: id of car
 * @size: size of car
 */
void race_state(int *id, size_t size)
{
	static Car *cars;
	static size_t car_count;
	size_t i, j;
	int found;

	if (size == 0)
	{
		free(cars);
		cars = NULL;
		car_count = 0;
		return;
	}
	cars = NULL;
	car_count = 0;

	for (i = 0; i < size; i++)
	{
		found = 0;
		for (j = 0; j < car_count; j++)
		{
			if (cars[j].id == id[i])
			{
				cars[j].laps++;
				found = 1;
				break;
			}
		}
		if (!found)
		{
			car_count++;
			cars = realloc(cars, sizeof(Car) * car_count);
			cars[car_count - 1].id = id[i];
			cars[car_count - 1].laps = 0;
			printf("Car %d joined the race\n", id[i]);
		}
	}
	printf("Race state:\n");
	for (i = 0; i < car_count; i++)
		printf("Car %d [%d laps]\n", cars[i].id, cars[i].laps);
}
