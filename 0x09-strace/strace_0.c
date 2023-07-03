#include "strace.h"

#include "strace.h"

/**
 * trace_syscall - Start or stop the process at the next entry or exit from a system call.
 * @pid: Process ID to trace.
 *
 * Return: 1 if the process is stopped by a signal, 0 if the process has exited.
 */
int trace_syscall(pid_t pid)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		waitpid(pid, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return 1;
		if (WIFEXITED(status))
			return 0;
	}
}

/**
 * validate_args - Check for usage errors.
 * @argc: Number of command-line arguments.
 * @argv: Pointer to an array of character strings that contain the arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int validate_args(int argc, char *argv[])
{
	struct stat sb;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", *argv);
		return 1;
	}
	if (stat(argv[1], &sb) == -1)
	{
		fprintf(stderr, "%s: Can't stat '%s': No such file or directory\n",
				*argv, argv[1]);
		return 1;
	}
	return 0;
}


/**
 * main - Entry point.
 * @argc: Number of command-line arguments.
 * @argv: Pointer to an array of character strings that contain the arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
    pid_t child_pid, parent_pid;

    if (validate_args(argc, argv))
        return 1;

    parent_pid = getpid();
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (child_pid == 0)
    {
        if (ptrace(PTRACE_TRACEME) == -1)
        {
            perror("ptrace");
            return 1;
        }

        kill(parent_pid, SIGSTOP);

        return execvp(argv[1], argv + 1);
    }
    else
    {
	    int status;
 
 	    setbuf(stdout, NULL);
            waitpid(child_pid, &status, 0);
            ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
            while (1)
            {
                 if (!trace_syscall(child_pid))
                     break;
                 printf("%li\n", ptrace(PTRACE_PEEKUSER, child_pid, sizeof(long) * ORIG_RAX));
                 if (!trace_syscall(child_pid))
                     break;
            }
        return 0;
    }
}
