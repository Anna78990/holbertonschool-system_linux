#include <stdio.h>
#include <signal.h>
#include "signals.h"

/**
 * current_handler_signal - retrieves the current handler of the signal SIGINT
 * @void: void
 * Return: nothing
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = signal(SIGINT, SIG_DFL);

	signal(SIGINT, handler);
	return (handler);
}
