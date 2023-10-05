#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include "libasm.h"

#define S1  "Holberton Socool"
#define S2  " S"
#define S3  "Holberton"

char * my_strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack; // needle が空の場合、haystack の先頭を返す
    }

    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        // マッチする部分文字列が見つかるまで needle を haystack と比較
        while (*h == *n && *n) {
            h++;
            n++;
        }

        // needle の終端に到達した場合、マッチする部分文字列が見つかった
        if (!*n) {
            return (char *)haystack;
        }

        haystack++;
    }

    return NULL; // 部分文字列が見つからなかった場合
}

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	printf("%s\n", my_strstr(S1, S2));
	printf("%s\n", my_strstr(S1, S3));
	printf("%s\n", my_strstr(S1, S1));
}
