#include <stdio.h>
#include <string.h>

int main(void) {
    char str[] = "apple,banana,cherry=grape";
    char *token, *rest;

    token = strtok(str, ",");

    while (token != NULL) {
        printf("%s\n", token);

        token = strtok(NULL, ",");
        printf("rest is now, %s\n", token);
    }

    return 0;
}

