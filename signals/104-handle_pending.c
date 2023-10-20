#include <signal.h>

/**
 * handle_pending - Set a handler for all pending signals
 * @handler: Pointer to the handler function
 *
 * Return: 0 on success, -1 on error
 */
int handle_pending(void (*handler)(int))
{
	sigset_t set;
	int signum;

	if (sigpending(&set) == -1)
		return (-1);

	for (signum = 1; signum < NSIG; signum++)
	{
		if (sigismember(&set, signum))
			if (signal(signum, handler) == SIG_ERR)
				return (-1);
	}

	return (0);
}

