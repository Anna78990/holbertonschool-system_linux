#include "signals.h"
#include <string.h>

/**
 * signal_handler - signal hundler
 * @signum: signal number
 * @siginfo: pointer to struct signal info
 * @ucontext: pointer to struct ucontext
 */
void signal_handler(__attribute__((unused)) int signum,
		siginfo_t *siginfo, __attribute__((unused))void *ucontext)
{
	psiginfo(siginfo, "Caught!");
}

/**
 * all_in_one - sets up a single handler for all the signals
 */
void all_in_one(void)
{
	struct sigaction sa;
	int signum;

	memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;

	for (signum = 0; signum < 64; signum++)
		sigaction(signum, &sa, NULL);
}
