#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/**
 * sigint_handler - print "Caughut <signum>"
 * @signum: signal number
 */
void sigint_handler(int signum)
{
	printf("Caught %d\n", signum);
}

/**
 * main - sets a handler for the signal SIGINT, and exits right
 *	  after the signal is received and handled
 * Return: Exit status
 */
int main(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}

	pause();
	printf("Signal received\n");
	return (0);
}
