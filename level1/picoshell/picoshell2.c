#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{
	int	status;
	int	pid;
	int	prev_fd;
	int	fds[2];
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	prev_fd = -1;
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(fds))
			return (1);
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(fds[0]);
				close(fds[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) < 0)
					exit (1);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				close(fds[0]);
				if (dup2(fds[1], STDOUT_FILENO) < 0)
					exit (1);
				close(fds[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		if (prev_fd != -1)
		{
			close (prev_fd);
		}
		if (cmds[i + 1])
		{
			prev_fd = fds[0];
			close (fds[1]);
		}
		i++;
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_code = 1;
	}
	return (exit_code);
}

int	main()
{
	char *ls[] = {"ls", "-l", NULL};
	char *grep[] = {"grep", ".c", NULL};
	char *wc[] = {"wc", "-l", NULL};
	char **cmds[] = {ls, grep, wc, NULL};

	picoshell(cmds);
}
