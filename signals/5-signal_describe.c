#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

/**
 * main - It prints a description of a given signal by argv
 * @argc: argc
 * @argv: argv
 * Return: Exit status
 */
int main(int argc, char *argv[])
{
	int signum = atoi(argv[1]);
	const char *signal_description = strsignal(signum);

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (signal_description == NULL)
		printf("%d: Unknown signal %d\n", signum, signum);
	else
		printf("%d: %s\n", signum, signal_description);
	return (EXIT_SUCCESS);
}
