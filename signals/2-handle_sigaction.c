#define _POSIX_C_SOURCE 200809L
#include "signals.h"

/**
 * sigint_handler - print Gotcha! [<signum>]
 * @signum: signal number
 */
void sigint_handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
}

/**
 * handle_sigaction - handler for the signal SIGINT
 * Return: 0 on success, or -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);

	return (0);
}
