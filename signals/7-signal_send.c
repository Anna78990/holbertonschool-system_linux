#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/**
 * main - it sends the signal SIGINT to a process, given its PID
 * @argc: argc
 * @argv: argv
 * Return: Exit status
 */
int main(int argc, char *argv[])
{
	pid_t target_pid;

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	target_pid = atoi(argv[1]);
	if (kill(target_pid, SIGINT) == 0)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("kill");
		return (EXIT_FAILURE);
	}
}
