#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>


/**
 * tprintf - print thread id and format
 * @format: string to print
 *
 * Return: result
 */

int tprintf(char const *format, ...)
{
	va_list args;
	int result;
	pthread_t tid = pthread_self();

	va_start(args, format);
	printf("[%lu] ", (unsigned long) tid);
	result = vprintf(format, args);

	va_end(args);
	return (result);
}
