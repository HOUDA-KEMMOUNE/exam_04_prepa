#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		int	code = WEXITSTATUS(status);
		if (code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		else
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", code);
			return (0);
		}
	}
	if (WIFSIGNALED(status))
	{
		int	sig = WTERMSIG(status);
		if (sig == SIGALRM)
		{
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		else
		{
			if (verbose)
				printf("Bad function: %d\n", strsignal(sig));
			return (0);
		}
	}
	return (-1);
}
