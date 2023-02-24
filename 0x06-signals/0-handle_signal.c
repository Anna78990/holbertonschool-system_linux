#include <signal.h>
#include <stdio.h>

/**
 * print_gotcha - print "Gotcha!"
 * @signum: signal number
 */
void print_gotcha(int signum)
{
	printf("Gotcha! [%d]\n", signum);
}

/**
 * handle_signal - set signal handler
 * Return: If it succeed 0, otherwise -1
 */
int handle_signal(void)
{
	if (signal(SIGINT, print_gotcha) == SIG_ERR)
		return (-1);
	else
		return (0);
}
