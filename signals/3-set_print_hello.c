#include "signals.h"


/**
 * print_hello - receives signal
 * @sig: the signal number received
 */
void print_hello(int sig)
{
	printf("Gotcha! [%d]\n", sig);
}

/**
 * set_print_hello - signal handler helper
 * Return: 0 on success else -1 on error
 */
void set_print_hello(void)
{
	signal(SIGINT, print_hello);
}
