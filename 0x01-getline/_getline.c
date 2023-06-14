#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define READ_SIZE 1024

char *_getline(const int fd)
{
    static char buffer[READ_SIZE];
    static ssize_t bytes_read = 0;
    static ssize_t current_pos = 0;
    static ssize_t line_length = 0;

    char *line = NULL;
    ssize_t i = 0;

    if (fd < 0 || bytes_read == -1)
        return NULL;

    while (1)
    {
        if (current_pos >= bytes_read)
        {
            current_pos = 0;
            bytes_read = read(fd, buffer, READ_SIZE);
            if (bytes_read == 0)
                return line;
            if (bytes_read == -1)
                return NULL;
        }

        if (i >= line_length)
        {
            char *temp = realloc(line, (line_length + READ_SIZE) * sizeof(char));
            if (temp == NULL)
            {
                free(line);
                return NULL;
            }
            line = temp;
            line_length += READ_SIZE;
        }

        if (buffer[current_pos] == '\n')
        {
            line[i] = '\0';
            current_pos++;
            return line;
        }

        line[i] = buffer[current_pos];
        i++;
        current_pos++;
    }
}
