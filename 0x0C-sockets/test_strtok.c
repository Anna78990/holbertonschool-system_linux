#include <stdio.h>
#include <string.h>

int main(void) {
    char str[] = "Hello,World|How,Are|You";
    char *token;
    char *rest = str;

    token = strtok_r(rest, "l,|", &rest);

    while (token != NULL) {
        printf("%s\n", token);

        token = strtok_r(rest, "l,|", &rest);
    }

    return 0;
}
