#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int i;
    char **strace_args = malloc((argc + 3) * sizeof(char *));

    if (argc < 2)
    {
        printf("Usage: ./strace_0 command [args...]\n");
        return 1;
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        strace_args[0] = "strace";
        strace_args[1] = "-f";
        for (i = 1; i < argc; i++)
        {
            strace_args[i + 1] = argv[i];
        }
        strace_args[argc + 1] = NULL;

        execvp("strace", strace_args);
        perror("execvp");
        exit(1);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
