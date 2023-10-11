#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	if (handle_sigaction() == -1)
	{
		printf("Failure\n");
		return (EXIT_FAILURE);
	}
	while (98)
	{
		sleep(2);
	}
	return (EXIT_SUCCESS);
}
