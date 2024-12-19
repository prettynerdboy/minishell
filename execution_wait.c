#include "minishell.h"
#include <errno.h>

int	wait_process(pid_t last_pid)
{
	int		status;
	pid_t	child_pid;
	int		child_status;

	status = 0;
	child_status = 0;
	signal(SIGINT, SIG_IGN);
	while ((child_pid = wait(&child_status)) > 0)
	{
		if (child_pid == last_pid)
			status = WEXITSTATUS(child_status);
	}
	if (child_pid == -1 && errno != ECHILD)
	{
		perror("wait");
		printf("\n");
	}
	if (WTERMSIG(child_status) == SIGQUIT)
	{
		printf("core dump\n");
		status = SIGQUIT_STATUS;
	}
	else if (WTERMSIG(child_status) == SIGINT)
	{
		printf("\n");
		status = SIGINT_STATUS;
	}
	signal(SIGINT, &signal_handler);
	return (status);
}
