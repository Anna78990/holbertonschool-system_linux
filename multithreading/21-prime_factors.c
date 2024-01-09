#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * p_factorize - make the chain of list prime number to factorize
 * @n: number to analyze
 * @factors: the head of list
 */
void p_factorize(unsigned long n, list_t *factors)
{
	unsigned long i, *prime = NULL;

	for (i = 2; i < n; i++)
	{
		if (i * i > n)
			break;
		if (n % i != 0)
			continue;
		while (n % i == 0)
		{
			prime = calloc(1, sizeof(unsigned long));
			*prime = i;
			list_add(factors, prime);
			n /= i;
		}
	}
	if (n > 2)
	{
		prime = calloc(1, sizeof(unsigned long));
		*prime = n;
		list_add(factors, prime);
	}
}

/**
 * prime_factors - Calculates the prime factors of
 * a number and stores them in a list
 *
 * @s: string representation of the number to factorize
 * Return: list of prime factors
 */
list_t *prime_factors(char const *s)
{
	list_t *factors = list_init(malloc(sizeof(list_t)));
	unsigned long n = 0;
	int i = 0;

	while (s[i])
	{
		n = (n * 10) + (s[i] - '0');
		i++;
	}

	p_factorize(n, factors);
	return (factors);
}
