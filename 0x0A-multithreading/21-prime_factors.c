#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * Checks if a number is prime
 * Returns 1 if the number is prime, 0 otherwise
 */
int is_prime(unsigned long n)
{
	if (n < 2)
		return 0;

	for (unsigned long i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
			return 0;
	}

	return (1);
}

/**
 * Calculates the prime factors of a number and stores them in a list
 */
list_t *prime_factors(char const *s)
{
	unsigned long num = strtoul(s, NULL, 10);
	list_t *factors = list_init(malloc(sizeof(list_t)));

	if (num < 2)
		return factors;

	unsigned long divisor = 2;

	while (num > 1)
	{
		if (num % divisor == 0)
		{
			if (is_prime(divisor))
			{
				unsigned long *factor = malloc(sizeof(unsigned long));
				*factor = divisor;
				list_add(factors, factor);
				num /= divisor;
			}
			else
			{
				divisor++;
			}
		}
		else
			divisor++;
	}

	return (factors);
}
