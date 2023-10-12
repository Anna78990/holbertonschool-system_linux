#include "signals.h"

/**
 * sigquit_handler - print SIGQUIT sent by <pid>
 * @sig: signal number
 * @info: siginfo
 * @context: context
 */
void sigquit_handler(int sig, siginfo_t *info, void *context)
{
	pid_t sender_pid;

	(void)sig;
	(void)context;

	sender_pid = info->si_pid;
	printf("SIGQUIT sent by %d\n", sender_pid);
}

/**
 * trace_signal_sender - print SIGQUIT sent by <pid> each time
 *			 a SIGQUIT (and only a SIGQUIT) is caught
 * Return: 0 on success, or -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigquit_handler;
	sa.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);

	return (0);
}
