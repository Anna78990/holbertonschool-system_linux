#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signum)
{
    puts("Stop this process");
    exit(1);
}

int main(void)
{

    signal(SIGINT, signal_handler);

    while (1)
    {
        printf("Wait for SIGINT ...\n");
        sleep(1);
    }

    return (0);
}
