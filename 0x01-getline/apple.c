#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *apple = (char *)malloc(sizeof(char) * 5);

	memcpy(apple, "apple", 3);
	printf("apple is %s, apple[0] is %c\n", apple, apple[0]);
}
