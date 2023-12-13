#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "strace.h"

/**
 * print_params - print parameters of a given syscall in hexadecimal
 * @reg: register of the syscall
 */
void print_params(struct user_regs_struct *reg)
{
	size_t i;

	printf("(");
	for (i = 0; i < syscalls_64_g[reg->orig_rax].nb_params; i++)
	{
		if (i > 0)
			printf(", ");
		if (syscalls_64_g[reg->orig_rax].params[i] != VARARGS)
		{
			if (syscalls_64_g[reg->orig_rax].params[i] == VOID)
				break;
			if (i == 0)
				printf("%#lx", (long)reg->rdi);
			else if (i == 1)
				printf("%#lx", (long)reg->rsi);
			else if (i == 2)
				printf("%#lx", (long)reg->rdx);
			else if (i == 3)
				printf("%#lx", (long)reg->r10);
			else if (i == 4)
				printf("%#lx", (long)reg->r8);
			else if (i == 5)
				printf("%#lx", (long)reg->r9);
		}
		else
			printf("...");
	}
}

/**
 * syscall_await - waits for a syscall
 * @child: pid of child process to await
 * Return: 0 if child stopped, 1 if exited
 */
int syscall_await(pid_t child)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return (0);
		if (WIFEXITED(status))
			return (1);
	}
}


/**
 * main - executes and traces a given command
 * @argc: number of args
 * @argv: arguments
 * Return: 0 if succeed, otherwise exit status
 */
int main(int argc, char *argv[], char **envp)
{
	int status;
	pid_t child;
	struct user_regs_struct regs;

	setbuf(stdout, NULL);
	if (argc < 2)
		exit(EXIT_FAILURE);
	child = fork();
	if (child == -1)
		exit(-1);
	else if (!child)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		kill(getpid(), SIGSTOP);
		if (execve(argv[1], argv + 1, envp) == -1)
			exit(-1);
	}
	else
	{
		waitpid(child, &status, 0);
		ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
		while (1)
		{
			if (syscall_await(child))
				break;
			memset(&regs, 0, sizeof(regs));
			ptrace(PTRACE_GETREGS, child, 0, &regs);
			printf("%s", syscalls_64_g[regs.orig_rax].name);
			print_params(&regs);
			if (syscall_await(child))
			{
				printf(") = ?\n");
				break;
			}
			memset(&regs, 0, sizeof(regs));
			ptrace(PTRACE_GETREGS, child, 0, &regs);
			printf(") = %#lx\n", (long)regs.rax);
		}
	}
	return (0);
}
