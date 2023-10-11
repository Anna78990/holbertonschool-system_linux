#include "signals.h"

/**
 * current_handler_sigaction - retrieves the current handler of the SIGINT
 * @void: void
 *
 * Return: pointer to the current handler of SIGINT, or NULL on failure
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
		return (NULL);
	return (sa.sa_handler);
}
