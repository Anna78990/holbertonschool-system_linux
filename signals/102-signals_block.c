#include <signal.h>
#include <stddef.h>

/**
 * signals_block - Blocks multiple signals
 * @signals: Array of signal numbers to block, terminated with a 0
 *
 * Return: 0 on success, -1 on error
 */
int signals_block(int *signals)
{
	sigset_t set;
	int i;

	if (sigemptyset(&set) == -1)
		return (-1);

	for (i = 0; signals[i] != 0; i++)
		if (sigaddset(&set, signals[i]) == -1)
			return (-1);

	return (sigprocmask(SIG_BLOCK, &set, NULL) == -1 ? -1 : 0);
}
