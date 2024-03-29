#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"

/**
 * res_check - check resp and print correct resp
 * @res: resp to check
 */
void res_check(char *res)
{
	char *code;

	code = strchr(res, ' ');
	if (strncmp(code + 1, "404", 3) == 0)
		printf(" -> 404 Not Found\r\n");
	else if (strncmp(code + 1, "411", 3) == 0)
		printf(" -> 411 Length Required\r\n");
	else if (strncmp(code + 1, "422", 3) == 0)
		printf(" -> 422 Unprocessable Entity\r\n");
	else if (strncmp(code + 1, "201", 3) == 0)
		printf(" -> 201 Created\r\n");
	else if (strncmp(code + 1, "200", 3) == 0)
		printf(" -> 200 OK\r\n");
}
