#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>

static pthread_mutex_t mutex;

/**
 * tprintf - Thread-safe printf using a mutex
 * @format: Format string
 *
 * Return: Number of characters printed
 */
int tprintf(char const *format, ...)
{
	va_list args;
	int ret;

	pthread_mutex_lock(&mutex);

	printf("[%lu] ", pthread_self());

	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);

	pthread_mutex_unlock(&mutex);

	return (ret);
}

void __attribute__((constructor)) init_mutex(void)
{
	pthread_mutex_init(&mutex, NULL);
}

void __attribute__((destructor)) destroy_mutex(void)
{
	pthread_mutex_destroy(&mutex);
}

