#include <signal.h>
#include <stddef.h>

/**
 * signals_unblock - Unblock a set of signals
 * @signals: Array of signal numbers to unblock, terminated with a 0
 *
 * Return: 0 on success, -1 on error
 */
int signals_unblock(int *signals)
{
	sigset_t set;
	int i;

	if (sigemptyset(&set) == -1)
		return (-1);

	for (i = 0; signals[i] != 0; i++)
		if (sigaddset(&set, signals[i]) == -1)
			return (-1);

	return (sigprocmask(SIG_UNBLOCK, &set, NULL) == -1 ? -1 : 0);
}
