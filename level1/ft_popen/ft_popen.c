#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./get_next_line/get_next_line.h"

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	fds[2];
	int	pid;

	if (!file || !argv || (type != 'w' && type != 'r'))
		return (-1);
	if (pipe(fds) < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (type == 'w')
		{
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			close(fds[1]);
		}
		else
		{
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			close(fds[0]);
		}
		execvp(file, argv);
		// exit (1);
	}
	if (type == 'w')
	{
		close(fds[0]);
		return (fds[1]);
	}
	else
	{
		close(fds[1]);
		return (fds[0]);		
	}
}

int main()
{
    char *line;

  char *argv[] = {"echo", "hh", NULL};
int fd = ft_popen("ls", NULL, 'r');

    while ((line = get_next_line(fd)))
        printf("%s", line);
    return (0);
}

