#include <stdio.h>
#include <pthread.h>


/**
 * thread_entry -make the entry point of a thread
 * @arg: address to the string
 *
 * Return: always NULL
 */

void *thread_entry(void *arg)
{
	char *message = (char *) arg;

	printf("%s\n", message);
	pthread_exit(NULL);
}
