#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton Socool"
#define S2  ""
#define S3  "Holberton School"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int a = 0;

	a = strcmp(S1, S3);
	printf("%d \n", a);
	a = strcmp(S1, S2);
	printf("%d", a);
}
